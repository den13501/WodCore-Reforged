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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "PetBattle.h"
#include "Common.h"

class PlayerScriptPetBattle : public PlayerScript
{
    public:
        /// Constructor
        PlayerScriptPetBattle()
            : PlayerScript("PlayerScriptPetBattle")
        {

        }

        /// Called when a spline step is done
        /// @p_Player   : Player instance
        /// @p_MoveType : Movement type
        /// @p_ID       : Movement ID
        void OnMovementInform(Player * p_Player, uint32 p_MoveType, uint32 p_ID) override
        {
            if (p_Player && p_MoveType == POINT_MOTION_TYPE && p_ID == PETBATTLE_ENTER_MOVE_SPLINE_ID)
            {
                m_Mutex.lock();
                m_DelayedPetBattleStart[p_Player->GetGUID()] = getMSTime() + 1000;
                m_Mutex.unlock();
            }
        }

        /// Called when a update() of a player is done
        /// @p_Player : Player instance
        /// @p_Diff : diff time
        void OnUpdate(Player* p_Player, uint32 /*p_Diff*/) override
        {
            m_Mutex.lock();

            if (m_DelayedPetBattleStart.find(p_Player->GetGUID()) != m_DelayedPetBattleStart.end())
            {
                if (m_DelayedPetBattleStart[p_Player->GetGUID()] > getMSTime())
                {
                    m_DelayedPetBattleStart.erase(m_DelayedPetBattleStart.find(p_Player->GetGUID()));

                    uint64 l_BattleID = p_Player->_petBattleId;
                    PetBattle * l_Battle = sPetBattleSystem->GetBattle(l_BattleID);

                    if (l_Battle)
                    {
                        p_Player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_IMMUNE_TO_NPC); // Immuned only to NPC
                        p_Player->SetRooted(true);

                        l_Battle->Begin();
                    }
                }
            }

            m_Mutex.unlock();
        }

        std::map<uint64, uint32> m_DelayedPetBattleStart;
        std::mutex m_Mutex;
};

#ifndef __clang_analyzer__
void AddSC_PetBattlePlayerScript()
{
    new PlayerScriptPetBattle;
}
#endif
