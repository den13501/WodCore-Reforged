/*
* Copyright (C) 2008-2020 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2021 WodCore Reforged
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

#ifndef _TCSOAP_H
#define _TCSOAP_H

#include "Common.h"
#include "World.h"
#include "AccountMgr.h"
#include "Log.h"

#include "soapH.h"
#include "soapStub.h"
#include "stdsoap2.h"

#include <ace/Semaphore.h>
#include <ace/Task.h>

class TCSoapRunnable : public ACE_Based::Runnable
{
    public:
        TCSoapRunnable() : _port(0) { }

        void run() override;

        void SetListenArguments(const std::string& host, uint16 port)
        {
            _host = host;
            _port = port;
        }
    private:
        void process_message(ACE_Message_Block* mb);

        std::string _host;
        uint16 _port;
};

class SOAPCommand
{
    public:
        SOAPCommand():
            pendingCommands(0, USYNC_THREAD, "pendingCommands"), m_success(false)
        {
        }

        ~SOAPCommand()
        {
        }

        void appendToPrintBuffer(const char* msg)
        {
            m_printBuffer += msg;
        }

        ACE_Semaphore pendingCommands;

        void setCommandSuccess(bool val)
        {
            m_success = val;
        }

        bool hasCommandSucceeded() const
        {
            return m_success;
        }

        static void print(void* callbackArg, const char* msg)
        {
            ((SOAPCommand*)callbackArg)->appendToPrintBuffer(msg);
        }

        static void commandFinished(void* callbackArg, bool success);

        bool m_success;
        std::string m_printBuffer;
};

#endif
