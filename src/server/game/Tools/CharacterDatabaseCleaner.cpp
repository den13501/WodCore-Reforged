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

#ifndef CROSS
#include "Common.h"
#include "CharacterDatabaseCleaner.h"
#include "World.h"
#include "Database/DatabaseEnv.h"
#include "SpellMgr.h"
#include "DBCStores.h"

void CharacterDatabaseCleaner::CleanDatabase()
{
    // config to disable
    if (!sWorld->getBoolConfig(CONFIG_CLEAN_CHARACTER_DB))
        return;

    TC_LOG_INFO("misc", "Cleaning character database...");

    uint32 oldMSTime = getMSTime();

    // check flags which clean ups are necessary
    QueryResult result = CharacterDatabase.Query("SELECT value FROM worldstates WHERE entry = 20004");
    if (!result)
        return;

    uint32 flags = (*result)[0].GetUInt32();

    if (flags & CLEANING_FLAG_SKILLS)
        CleanCharacterSkills();

    if (flags & CLEANING_FLAG_SPELLS)
        CleanCharacterSpell();

    if (flags & CLEANING_FLAG_TALENTS)
        CleanCharacterTalent();

    if (flags & CLEANING_FLAG_QUESTSTATUS)
        CleanCharacterQuestStatus();

    if (flags & CLEANING_FLAG_AUTO_LEARNED_SPELLS)
        CleanCharacterAutoLearnedSpells();

    // NOTE: In order to have persistentFlags be set in worldstates for the next cleanup,
    // you need to define them at least once in worldstates.
    flags &= sWorld->getIntConfig(CONFIG_PERSISTENT_CHARACTER_CLEAN_FLAGS);
    CharacterDatabase.DirectPExecute("UPDATE worldstates SET value = %u WHERE entry = 20004", flags);

    sWorld->SetCleaningFlags(flags);

    TC_LOG_INFO("server.loading", ">> Cleaned character database in %u ms", GetMSTimeDiffToNow(oldMSTime));

}

void CharacterDatabaseCleaner::CheckUnique(const char* column, const char* table, bool (*check)(uint32))
{
    QueryResult result = CharacterDatabase.PQuery("SELECT DISTINCT %s FROM %s", column, table);
    if (!result)
    {
        TC_LOG_INFO("misc", "Table %s is empty.", table);
        return;
    }

    bool found = false;
    std::ostringstream ss;
    do
    {
        Field* fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();

        if (!check(id))
        {
            if (!found)
            {
                ss << "DELETE FROM " << table << " WHERE " << column << " IN (";
                found = true;
            }
            else
                ss << ',';

            ss << id;
        }
    }
    while (result->NextRow());

    if (found)
    {
        ss << ')';
        CharacterDatabase.Execute(ss.str().c_str());
    }
}

bool CharacterDatabaseCleaner::SkillCheck(uint32 skill)
{
    return sSkillLineStore.LookupEntry(skill);
}

void CharacterDatabaseCleaner::CleanCharacterSkills()
{
    CheckUnique("skill", "character_skills", &SkillCheck);
}

bool CharacterDatabaseCleaner::SpellCheck(uint32 spell_id)
{
    return sSpellMgr->GetSpellInfo(spell_id);// && !GetTalentSpellPos(spell_id);
}

void CharacterDatabaseCleaner::CleanCharacterSpell()
{
    CheckUnique("spell", "character_spell", &SpellCheck);
}

bool CharacterDatabaseCleaner::TalentCheck(uint32 /*talent_id*/)
{
    return false;
    /*
    TalentEntry const* talentInfo = sTalentStore.LookupEntry(talent_id);
    if (!talentInfo)
        return false;

    return sTalentTabStore.LookupEntry(talentInfo->TalentTab);*/
}

void CharacterDatabaseCleaner::CleanCharacterTalent()
{
    CharacterDatabase.DirectPExecute("DELETE FROM character_talent WHERE spec > %u", MAX_TALENT_SPECS);
    CheckUnique("spell", "character_talent", &TalentCheck);
}

void CharacterDatabaseCleaner::CleanCharacterQuestStatus()
{
    CharacterDatabase.DirectExecute("DELETE FROM character_queststatus WHERE status = 0");
}

bool CharacterDatabaseCleaner::NotAutoLearnedSpell(uint32 spell_id)
{
    const SpellInfo* info = sSpellMgr->GetSpellInfo(spell_id);
    // make sure the spell actually exists, if not also delete it
    if (!info)
        return false;

    if (info->IsAbilityOfSkillType(SKILL_BLACKSMITHING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_LEATHERWORKING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_ALCHEMY))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_HERBALISM))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_COOKING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_MINING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_TAILORING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_ENGINEERING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_ENCHANTING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_FISHING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_SKINNING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_JEWELCRAFTING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_INSCRIPTION))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_MOUNTS))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_COMPANIONS))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_ARCHAEOLOGY))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_ALL_GLYPHS))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_APPRENTICE_COOKING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_JOURNEYMAN_COOKBOOK))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_GARRENCHANTING))
        return true;

    if (info->IsAbilityOfSkillType(SKILL_LOGGING))
        return true;

    return false;
}

void CharacterDatabaseCleaner::CleanCharacterAutoLearnedSpells()
{
    CheckUnique("spell", "character_spell", &NotAutoLearnedSpell);
}

#endif
