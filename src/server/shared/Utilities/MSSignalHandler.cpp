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

#include "MSSignalHandler.h"
#include "Log.h"
#include "ace/Stack_Trace.h"

namespace MS
{
    namespace SignalHandler
    {
        void EnableThrowExceptionAtFailure()
        {
            gThrowExceptionAtFailure = true;
        }

        void DisableThrowExceptionAtFailure()
        {
            gThrowExceptionAtFailure = false;
        }

        void OnSignalReceive(int p_Signal)
        {
            gFailureCounter++;

            if (gThrowExceptionAtFailure && gFailureCounter < gFailureCountLimit)
            {
                // Register the signal handler for the next signal
                signal(p_Signal, &MS::SignalHandler::OnSignalReceive);

                // Throw runtime exception to catch block and go back to execution context
                throw std::runtime_error("");
            }

            ACE_Stack_Trace l_Trace;
            TC_LOG_ERROR("server.worldserver", "MS::SignalHandler : can't rescue the thread, shutdown the server  StackTrace : %s", l_Trace.c_str());

#ifdef _MSC_VER
            /// Pause process execution on windows only to let time to the dev
            /// to see the call stack on crash.
            system("pause");
#endif

            // We can't rescue the thread, shutdown the server
            exit(SIGTERM);
        }
    }
}
