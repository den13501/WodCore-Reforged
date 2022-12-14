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

#ifndef SC_SCRIPTLOADER_H
#define SC_SCRIPTLOADER_H

void AddScripts();
void AddWorldScripts();
void AddSpellScripts();
#ifndef CROSS
void AddCommandScripts();
#endif /* not CROSS */
void AddWorldScripts();
#ifdef CROSS
void AddCommandScripts();
#endif /* CROSS */
void AddEasternKingdomsScripts();
void AddKalimdorScripts();
void AddOutlandScripts();
void AddNorthrendScripts();
void AddPandarieScripts();
void AddDraenorScripts();
void AddEventScripts();
void AddBattlegroundScripts();
void AddOutdoorPvPScripts();
void AddCustomScripts();
#ifndef CROSS
void AddBattlePayScripts();
#endif /* not CROSS */

#endif
