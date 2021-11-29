/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <ace/Dev_Poll_Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/ACE.h>
#include <ace/Sig_Handler.h>
#include <openssl/opensslv.h>
#include <openssl/crypto.h>
#include <thread>

//#include <Reporting/Reporter.hpp>

#include "Common.h"
#include "GitRevision.h"
#include "Database/DatabaseEnv.h"
#include "Configuration/Config.h"
#include "Log.h"
#include "Util.h"
#include "SignalHandler.h"
#include "RealmList.h"
#include "RealmAcceptor.h"
#include "Bnet2/WoWModules/PasswordAuth.hpp"
#include "Bnet2/WoWModules/RiskFingerprintAuth.hpp"
#include "Bnet2/WoWModules/ThumbprintAuth.hpp"
#include "Bnet2/WoWModules/SelectGameAccountAuth.hpp"
#include "Bnet2/Session.hpp"

#ifndef _TRINITY_REALM_CONFIG
# define _TRINITY_REALM_CONFIG  "authserver.conf"
#endif

bool StartDB();
void StopDB();

bool stopEvent = false;                                     // Setting it to true stops the server

LoginDatabaseWorkerPool LoginDatabase;                      // Accessor to the auth server database

// Handle authserver's termination signals
class AuthServerSignalHandler : public JadeCore::SignalHandler
{
public:
    virtual void HandleSignal(int SigNum)
    {
        switch (SigNum)
        {
        case SIGINT:
        case SIGTERM:
            stopEvent = true;
            break;
        }
    }
};

/// Print out the usage string for this program on the console.
void usage(const char *prog)
{
    sLog->outInfo(LOG_FILTER_AUTHSERVER, "Usage: \n %s [<options>]\n"
        "    -c config_file           use config_file as configuration file\n\r",
        prog);
}

void RegisterBNet2Components()
{
    BNet2::AuthComponentManager::GetSingleton()->Allow(37165, BNet2::BATTLENET2_PROGRAM_BNET, BNet2::BATTLENET2_PROGRAM_ALL, BNet2::BATTLENET2_LOCALE_NONE);

    QueryResult l_Result = LoginDatabase.PQuery("SELECT build, version FROM bnet_allowed_build");
    if (l_Result)
    {
        do
        {
            Field* l_Fields = l_Result->Fetch();
            uint32 l_AllowedBuild = l_Fields[0].GetUInt32();

            BNet2::g_VersionStrByBuild[l_AllowedBuild] = l_Fields[1].GetString();

            BNet2::AuthComponentManager::GetSingleton()->Allow(l_AllowedBuild, BNet2::BATTLENET2_PROGRAM_ALL_CLIENTS, BNet2::BATTLENET2_PLATFORM_ALL, BNet2::BATTLENET2_LOCALE_ALL);
        }
        while (l_Result->NextRow());
    }
}

void RegisterBNet2WoWModules()
{
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::PasswordAuthWin32));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::PasswordAuthWin64));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::PasswordAuthMac64));

    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::RiskFingerprintAuthWin32));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::RiskFingerprintAuthWin64));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::RiskFingerprintAuthMac64));

    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::ThumbprintAuthWin32));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::ThumbprintAuthWin64));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::ThumbprintAuthMac64));

    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::SelectGameAccountAuthWin32));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::SelectGameAccountAuthWin64));
    BNet2::ModuleManager::GetSingleton()->RegisterModule(BNet2::Module::Ptr(new BNet2::WoWModules::SelectGameAccountAuthMac64));
}

// Launch the auth server
extern int main(int argc, char **argv)
{
    ACE_Based::Thread::current()->setName("MainThread");

    // Command line parsing to get the configuration file name
    char const* cfg_file = _TRINITY_REALM_CONFIG;
    int c = 1;
    while (c < argc)
    {
        if (strcmp(argv[c], "-c") == 0)
        {
            if (++c >= argc)
            {
                printf("Runtime-Error: -c option requires an input argument");
                usage(argv[0]);
                return 1;
            }
            else
                cfg_file = argv[c];
        }
        ++c;
    }

    if (!sConfigMgr->LoadInitial(cfg_file))
    {
        printf("Invalid or missing configuration file : %s", cfg_file);
        printf("Verify that the file exists and has \'[authserver]\' written in the top of the file!");
        return 1;
    }

    sLog->outInfo(LOG_FILTER_AUTHSERVER, "%s (authserver)", GitRevision::GetFullVersion());
    sLog->outInfo(LOG_FILTER_AUTHSERVER, "<Ctrl-C> to stop.\n");
    sLog->outInfo(LOG_FILTER_AUTHSERVER, "Using configuration file %s.", cfg_file);

    sLog->outWarn(LOG_FILTER_AUTHSERVER, "%s (Library: %s)", OPENSSL_VERSION_TEXT, SSLeay_version(SSLEAY_VERSION));

#if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)
    ACE_Reactor::instance(new ACE_Reactor(new ACE_Dev_Poll_Reactor(ACE::max_handles(), 1), 1), true);
#else
    ACE_Reactor::instance(new ACE_Reactor(new ACE_TP_Reactor(), true), true);
#endif

    sLog->outDebug(LOG_FILTER_AUTHSERVER, "Max allowed open files is %d", ACE::max_handles());

    // authserver PID file creation
    std::string pidfile = sConfigMgr->GetStringDefault("PidFile", "");
    if (!pidfile.empty())
    {
        uint32 pid = CreatePIDFile(pidfile);
        if (!pid)
        {
            sLog->outError(LOG_FILTER_AUTHSERVER, "Cannot create PID file %s.\n", pidfile.c_str());
            return 1;
        }
        sLog->outInfo(LOG_FILTER_AUTHSERVER, "Daemon PID: %u\n", pid);
    }

    // Initialize the database connection
    if (!StartDB())
        return 1;

    RegisterBNet2Components();
    RegisterBNet2WoWModules();
	
    
    // Get the list of realms for the server
    sRealmList->Initialize(sConfigMgr->GetIntDefault("RealmsStateUpdateDelay", 20));
    if (sRealmList->size() == 0)
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "No valid realms specified.");
        return 1;
    }

    // Launch the listening network socket
    RealmAcceptor acceptor;

    int32 rmport = sConfigMgr->GetIntDefault("RealmServerPort", 3724);
    if (rmport < 0 || rmport > 0xFFFF)
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Specified port out of allowed range (1-65535)");
        return 1;
    }

    std::string bind_ip = sConfigMgr->GetStringDefault("BindIP", "0.0.0.0");

    ACE_INET_Addr bind_addr(uint16(rmport), bind_ip.c_str());

    if (acceptor.open(bind_addr, ACE_Reactor::instance(), ACE_NONBLOCK) == -1)
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Auth server can not bind to %s:%d", bind_ip.c_str(), rmport);
        return 1;
    }

    ///- Initializing the Reporter.
    //sLog->outInfo(LOG_FILTER_WORLDSERVER, "REPORTER: Creating instance.");
    //sReporter->SetAddresses({ ConfigMgr::GetStringDefault("ReporterAddress", "localhost:3000") });

    // Initialise the signal handlers
    AuthServerSignalHandler SignalINT, SignalTERM;

    // Register authservers's signal handlers
    ACE_Sig_Handler Handler;
    Handler.register_handler(SIGINT, &SignalINT);
    Handler.register_handler(SIGTERM, &SignalTERM);

    ///- Handle affinity for multiple processors and process priority on Windows
#ifdef _WIN32
    {
        HANDLE hProcess = GetCurrentProcess();

        uint32 Aff = sConfigMgr->GetIntDefault("UseProcessors", 0);
        if (Aff > 0)
        {
            ULONG_PTR appAff;
            ULONG_PTR sysAff;

            if (GetProcessAffinityMask(hProcess, &appAff, &sysAff))
            {
                ULONG_PTR curAff = Aff & appAff;            // remove non accessible processors

                if (!curAff)
                    sLog->outError(LOG_FILTER_AUTHSERVER, "Processors marked in UseProcessors bitmask (hex) %x not accessible for authserver. Accessible processors bitmask (hex): %x", Aff, appAff);
                else if (SetProcessAffinityMask(hProcess, curAff))
                    sLog->outInfo(LOG_FILTER_AUTHSERVER, "Using processors (bitmask, hex): %x", curAff);
                else
                    sLog->outError(LOG_FILTER_AUTHSERVER, "Can't set used processors (hex): %x", curAff);
            }

        }

        bool Prio = sConfigMgr->GetBoolDefault("ProcessPriority", false);

        if (Prio)
        {
            if (SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
                sLog->outInfo(LOG_FILTER_AUTHSERVER, "The auth server process priority class has been set to HIGH");
            else
                sLog->outError(LOG_FILTER_AUTHSERVER, "Can't set auth server process priority class.");

        }
    }
#endif

    // maximum counter for next ping
    uint32 numLoops = (sConfigMgr->GetIntDefault("MaxPingTime", 30) * (MINUTE * 1000000 / 100000));
    uint32 loopCounter = 0;

    // Wait for termination signal
    while (!stopEvent)
    {
        // dont move this outside the loop, the reactor will modify it
        ACE_Time_Value interval(0, 100000);

        if (ACE_Reactor::instance()->run_reactor_event_loop(interval) == -1)
            break;

        if ((++loopCounter) == numLoops)
        {
            loopCounter = 0;
            sLog->outInfo(LOG_FILTER_AUTHSERVER, "Ping MySQL to keep connection alive");
            LoginDatabase.KeepAlive();
        }
    }

    // Close the Database Pool and library
    StopDB();

    sLog->outInfo(LOG_FILTER_AUTHSERVER, "Halting process...");
    return 0;
}

// Initialize connection to the database
bool StartDB()
{
    MySQL::Library_Init();

    std::string dbstring = sConfigMgr->GetStringDefault("LoginDatabaseInfo", "");
    if (dbstring.empty())
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Database not specified");
        return false;
    }

    int32 worker_threads = sConfigMgr->GetIntDefault("LoginDatabase.WorkerThreads", 1);
    if (worker_threads < 1 || worker_threads > 32)
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Improper value specified for LoginDatabase.WorkerThreads, defaulting to 1.");
        worker_threads = 1;
    }

    int32 synch_threads = sConfigMgr->GetIntDefault("LoginDatabase.SynchThreads", 1);
    if (synch_threads < 1 || synch_threads > 32)
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Improper value specified for LoginDatabase.SynchThreads, defaulting to 1.");
        synch_threads = 1;
    }

    // NOTE: While authserver is singlethreaded you should keep synch_threads == 1. Increasing it is just silly since only 1 will be used ever.
    if (!LoginDatabase.Open(dbstring.c_str(), uint8(worker_threads), uint8(synch_threads)))
    {
        sLog->outError(LOG_FILTER_AUTHSERVER, "Cannot connect to database");
        return false;
    }

    sLog->outInfo(LOG_FILTER_AUTHSERVER, "Started auth database connection pool.");
    sLog->SetRealmId(0); // Enables DB appenders when realm is set.
    return true;
}

void StopDB()
{
    LoginDatabase.Close();
    MySQL::Library_End();
}
