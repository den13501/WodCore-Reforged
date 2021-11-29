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

#ifndef TRINITYCORE_ERRORS_H
#define TRINITYCORE_ERRORS_H

#include "Define.h"

#include "Common.h"
#include "Log.h"
#include <ace/Stack_Trace.h>
#include <ace/OS_NS_unistd.h>

namespace Trinity
{

    DECLSPEC_NORETURN void Assert(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Fatal(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Error(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    void Warning(char const* file, int line, char const* function, char const* message);

} // namespace Trinity

#define WPAssert(assertion) { if (!(assertion)) { sLog->outAshran("\n%s:%i in %s ASSERTION FAILED:\n  %s\n%", __FILE__, __LINE__, __FUNCTION__, #assertion); } }
#define WPError(assertion, errmsg) { if (!(assertion)) { TC_LOG_ERROR(LOG_FILTER_GENERAL, "%\n%s:%i in %s ERROR:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg); } }
#define WPWarning(assertion, errmsg) { if (!(assertion)) { TC_LOG_ERROR(LOG_FILTER_GENERAL, "\n%s:%i in %s WARNING:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg); } }
#define WPFatal(assertion, errmsg) { if (!(assertion)) { TC_LOG_ERROR(LOG_FILTER_GENERAL, "\n%s:%i in %s FATAL ERROR:\n  %s\n", __FILE__, __LINE__, __FUNCTION__, (char *)errmsg); ACE_OS::sleep(10); } }

#define ASSERT WPAssert
#endif

