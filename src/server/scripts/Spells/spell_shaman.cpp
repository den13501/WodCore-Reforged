/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/*
 * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by shaman players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_sha_".
 */

#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"
#include "GridNotifiers.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum ShamanSpells
{
    SHAMAN_SPELL_SATED                      = 57724,
    SHAMAN_SPELL_EXHAUSTION                 = 57723,
    HUNTER_SPELL_INSANITY                   = 95809,
    MAGE_SPELL_TEMPORAL_DISPLACEMENT        = 80354,
    SPELL_SHA_LIGHTNING_SHIELD_AURA         = 324,
    SPELL_SHA_ASCENDANCE_ELEMENTAL          = 114050,
    SPELL_SHA_ASCENDANCE_RESTORATION        = 114052,
    SPELL_SHA_ASCENDANCE_ENHANCED           = 114051,
    SPELL_SHA_ASCENDANCE                    = 114049,
    SPELL_SHA_HEALING_RAIN                  = 142923,
    SPELL_SHA_HEALING_RAIN_TICK             = 73921,
    SPELL_SHA_HEALING_RAIN_AURA             = 73920,
    SPELL_SHA_EARTHQUAKE                    = 61882,
    SPELL_SHA_EARTHQUAKE_TICK               = 77478,
    SPELL_SHA_EARTHQUAKE_KNOCKING_DOWN      = 77505,
    SPELL_SHA_ELEMENTAL_BLAST               = 117014,
    SPELL_SHA_ELEMENTAL_BLAST_RATING_BONUS  = 118522,
    SPELL_SHA_ELEMENTAL_BLAST_NATURE_VISUAL = 118517,
    SPELL_SHA_ELEMENTAL_BLAST_FROST_VISUAL  = 118515,
    SPELL_SHA_LAVA_LASH                     = 60103,
    SPELL_SHA_FLAME_SHOCK                   = 8050,
    SPELL_SHA_STORMSTRIKE                   = 17364,
    SPELL_SHA_LIGHTNING_SHIELD_ORB_DAMAGE   = 26364,
    SPELL_SHA_HEALING_STREAM                = 52042,
    SPELL_SHA_GLYPH_OF_HEALING_STREAM       = 119523,
    SPELL_SHA_LAVA_SURGE_CAST_TIME          = 77762,
    SPELL_SHA_FULMINATION                   = 88766,
    SPELL_SHA_FULMINATION_TRIGGERED         = 88767,
    SPELL_SHA_FULMINATION_INFO              = 95774,
    SPELL_SHA_ROLLING_THUNDER_AURA          = 88764,
    SPELL_SHA_ROLLING_THUNDER_ENERGIZE      = 88765,
    SPELL_SHA_UNLEASH_ELEMENTS              = 73680,
    SPELL_SHA_SEARING_FLAMES_DAMAGE_DONE    = 77661,
    SPELL_SHA_FIRE_NOVA                     = 1535,
    SPELL_SHA_FIRE_NOVA_TRIGGERED           = 8349,
    SPELL_SHA_TIDAL_WAVES                   = 51564,
    SPELL_SHA_TIDAL_WAVES_PROC              = 53390,
    SPELL_SHA_MANA_TIDE                     = 16191,
    SPELL_SHA_FROST_SHOCK_FREEZE            = 63685,
    SPELL_SHA_FROZEN_POWER                  = 63374,
    SPELL_SHA_MAIL_SPECIALIZATION_AGI       = 86099,
    SPELL_SHA_MAIL_SPECIALISATION_INT       = 86100,
    SPELL_SHA_UNLEASHED_FURY_TALENT         = 117012,
    SPELL_SHA_UNLEASHED_FURY_FLAMETONGUE    = 118470,
    SPELL_SHA_UNLEASHED_FURY_WINDFURY       = 118472,
    SPELL_SHA_UNLEASHED_FURY_EARTHLIVING    = 118473,
    SPELL_SHA_UNLEASHED_FURY_FROSTBRAND     = 118474,
    SPELL_SHA_UNLEASHED_FURY_ROCKBITER      = 118475,
    SPELL_SHA_STONE_BULWARK_ABSORB          = 114893,
    SPELL_SHA_EARTHGRAB_IMMUNITY            = 116946,
    SPELL_SHA_EARTHBIND_FOR_EARTHGRAB_TOTEM = 116947,
    SPELL_SHA_EARTHGRAB                     = 64695,
    SPELL_SHA_ECHO_OF_THE_ELEMENTS          = 108283,
    SPELL_SHA_ANCESTRAL_GUIDANCE            = 114911,
    SPELL_SHA_CONDUCTIVITY_TALENT           = 108282,
    SPELL_SHA_CONDUCTIVITY_HEAL             = 118800,
    SPELL_SHA_GLYPH_OF_LAKESTRIDER          = 55448,
    SPELL_SHA_WATER_WALKING                 = 546,
    SPELL_SHA_GLYPH_OF_SHAMANISTIC_RAGE     = 63280,
    SPELL_SHA_SOLAR_BEAM                    = 113286,
    SPELL_SHA_SOLAR_BEAM_SILENCE            = 113288,
    SPELL_SHA_GHOST_WOLF                    = 2645,
    SPELL_SHA_ITEM_T14_4P                   = 123124,
    SPELL_SHA_GLYPH_OF_HEALING_STREAM_TOTEM = 55456,
    SPELL_SHA_ITEM_S12_4P_ENHANCEMENT_BONUS = 131554,
    SPELL_SHA_RESTORATIVE_MISTS             = 114083,
    SPELL_SHA_FROST_SHOCK                   = 8056,
    SPELL_SHA_LAVA_SURGE_AURA               = 77756,
    SPELL_SHA_LAVA_BURST                    = 51505,
    SPELL_SPIRIT_HUNT_HEAL                  = 58879,
    SPELL_SHA_WINDFURY_ATTACK               = 25504,
    SPELL_SHA_LAMETONGUE_ATTACK             = 10444,
    SPELL_SHA_PVP_BONUS_WOD_2               = 166103,
    SPELL_SHA_PVP_BONUS_WOD_4               = 171121,
    SPELL_SHA_LIGHTNING_SHIELD              = 324,
    SPELL_SHA_IMPROVED_CHAIN_LIGHTNING      = 157766,
    SPELL_SHA_MOLTEN_EARTH_DAMAGE           = 170379,
    SPELL_SHA_MOLTEN_EARTH                  = 170374,
    SPELL_SHA_MOLTEN_EARTH_PERIODICAL       = 170377,
    SPELL_SHA_ECHO_OF_THE_ELEMENTS_ELEMENTAL   = 159101,
    SPELL_SHA_ECHO_OF_THE_ELEMENTS_ENHANCEMENT = 159103,
    SPELL_SHA_ECHO_OF_THE_ELEMENTS_RESTORATION = 159105,
    SPELL_SHA_LAVA_LASH_SPREAD              = 105792,
    SPELL_SHA_LIQUID_MAGMA_DAMAGE           = 177601
};

// Totemic Projection - 108287
class spell_sha_totemic_projection : public SpellScriptLoader
{
    public:
        spell_sha_totemic_projection() : SpellScriptLoader("spell_sha_totemic_projection") { }

        class spell_sha_totemic_projection_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_totemic_projection_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Creature*> leapList;
                    Unit* leapTarget = NULL;

                    caster->GetCreatureListWithEntryInGrid(leapList, 47319, 45.0f);

                    for (auto itr : leapList)
                    {
                        if (!itr->ToUnit() || !itr->ToTempSummon())
                            continue;

                        if (!itr->ToTempSummon()->GetSummoner())
                            continue;

                        if (itr->ToTempSummon()->GetSummoner()->GetGUID() != caster->GetGUID())
                            continue;

                        leapTarget = itr->ToUnit();
                        break;
                    }

                    if (!leapTarget)
                        return;

                    for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                    {
                        if ((*itr)->isTotem())
                        {
                            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo((*itr)->GetUInt32Value(UNIT_FIELD_CREATED_BY_SPELL));
                            if (!spellInfo)
                                continue;

                            float objSize = caster->GetObjectSize();
                            float angle = spellInfo->Effects[0].TargetA.CalcDirectionAngle();
                            float dist = spellInfo->Effects[0].CalcRadius(caster);

                            if (dist < objSize)
                                dist = objSize;

                            Position pos;
                            leapTarget->GetPosition(&pos);

                            angle += (*itr)->GetOrientation();
                            float destx, desty, destz, ground, floor;
                            destx = pos.m_positionX + dist * std::cos(angle);
                            desty = pos.m_positionY + dist * std::sin(angle);
                            ground = (*itr)->GetMap()->GetHeight((*itr)->GetPhaseMask(), destx, desty, MAX_HEIGHT, true);
                            floor = (*itr)->GetMap()->GetHeight((*itr)->GetPhaseMask(), destx, desty, pos.m_positionZ, true);
                            destz = fabs(ground - pos.m_positionZ) <= fabs(floor - pos.m_positionZ) ? ground : floor;

                            (*itr)->NearTeleportTo(destx, desty, destz, (*itr)->GetOrientation());
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_totemic_projection_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_totemic_projection_SpellScript();
        }
};

// Hex - 51514
class spell_sha_hex : public SpellScriptLoader
{
    public:
        spell_sha_hex() : SpellScriptLoader("spell_sha_hex") { }

        class spell_sha_hex_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_hex_AuraScript);

            void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* target = GetTarget())
                {
                    if (target->IsMounted())
                    {
                        target->Dismount();
                        target->RemoveAurasByType(SPELL_AURA_MOUNTED);
                    }

                    if (target->HasUnitState(UNIT_STATE_CASTING))
                    {
                        target->InterruptSpell(CURRENT_GENERIC_SPELL);
                        target->InterruptSpell(CURRENT_CHANNELED_SPELL);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sha_hex_AuraScript::OnApply, EFFECT_0, SPELL_AURA_TRANSFORM, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_hex_AuraScript();
        }
};

// Water Ascendant - 114052
class spell_sha_water_ascendant : public SpellScriptLoader
{
    public:
        spell_sha_water_ascendant() : SpellScriptLoader("spell_sha_water_ascendant") { }

        class spell_sha_water_ascendant_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_water_ascendant_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                Player* _player = GetCaster()->ToPlayer();
                if (!_player)
                    return;

                if (_player->HasSpellCooldown(SPELL_SHA_RESTORATIVE_MISTS))
                    return;

                if (eventInfo.GetActor()->GetGUID() != _player->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetSpellInfo())
                    return;

                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_SHA_RESTORATIVE_MISTS)
                    return;

                if (!(eventInfo.GetHealInfo()->GetHeal()))
                    return;

                if (!(eventInfo.GetDamageInfo()->GetSpellInfo()->IsPositive()))
                    return;

                if (Unit* target = eventInfo.GetActionTarget())
                {
                    std::list<Unit*> tempList;
                    std::list<Unit*> alliesList;
                    target->GetAttackableUnitListInRange(tempList, 15.0f);

                    for (auto itr : tempList)
                    {
                        if (!_player->IsWithinLOSInMap(itr))
                            continue;

                        if (itr->IsHostileTo(_player))
                            continue;

                        alliesList.push_back(itr);
                    }

                    if (!alliesList.empty())
                    {
                        // Heal amount distribued for all allies, caster included
                        int32 bp = eventInfo.GetHealInfo()->GetHeal() / alliesList.size();

                        if (bp > 0)
                            _player->CastCustomSpell((*alliesList.begin()), SPELL_SHA_RESTORATIVE_MISTS, &bp, NULL, NULL, true);   // Restorative Mists

                        _player->AddSpellCooldown(SPELL_SHA_RESTORATIVE_MISTS, 0, 1 * IN_MILLISECONDS);               // This prevent from multiple procs
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_water_ascendant_AuraScript::OnProc, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_water_ascendant_AuraScript();
        }
};

// Called by Shamanistic Rage - 30823
// Glyph of Shamanistic Rage - 63280
class spell_sha_glyph_of_shamanistic_rage : public SpellScriptLoader
{
    public:
        spell_sha_glyph_of_shamanistic_rage() : SpellScriptLoader("spell_sha_glyph_of_shamanistic_rage") { }

        class spell_sha_glyph_of_shamanistic_rage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_glyph_of_shamanistic_rage_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(SPELL_SHA_GLYPH_OF_SHAMANISTIC_RAGE))
                    {
                        DispelChargesList dispelList;
                        caster->GetDispellableAuraList(caster, DISPEL_ALL_MASK, dispelList);

                        for (auto itr : dispelList)
                            caster->RemoveAura(itr.first);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_glyph_of_shamanistic_rage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_glyph_of_shamanistic_rage_SpellScript();
        }
};

// Called by Ghost Wolf - 2645
// Glyph of Lakestrider - 55448
class spell_sha_glyph_of_lakestrider : public SpellScriptLoader
{
    public:
        spell_sha_glyph_of_lakestrider() : SpellScriptLoader("spell_sha_glyph_of_lakestrider") { }

        class spell_sha_glyph_of_lakestrider_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_glyph_of_lakestrider_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(SPELL_SHA_GLYPH_OF_LAKESTRIDER))
                        caster->CastSpell(caster, SPELL_SHA_WATER_WALKING, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_glyph_of_lakestrider_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_glyph_of_lakestrider_SpellScript();
        }
};

uint32 g_resetTotemCdSpells[] =
{
    108269, // Capacitor Totem
    2484,   // Earthbind Totem
    8177,   // Grounding Totem
    5394,   // Healing Stream Totem
    8143,   // Tremor Totem
    108270, // Stone Bulwark Totem
    51485,  // Earthgrab Totem
    108273  // Windwalk Totem
};

// 108285 - Call of the Elements
class spell_sha_call_of_the_elements : public SpellScriptLoader
{
    public:
        spell_sha_call_of_the_elements() : SpellScriptLoader("spell_sha_call_of_the_elements") { }

        class spell_sha_call_of_the_elements_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_call_of_the_elements_SpellScript);

            void OnSpellHit()
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (!l_Player)
                    return;

                for (int l_I = 0; l_I < sizeof(g_resetTotemCdSpells) / sizeof(uint32); l_I++)
                    l_Player->RemoveSpellCooldown(g_resetTotemCdSpells[l_I], true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_call_of_the_elements_SpellScript::OnSpellHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_call_of_the_elements_SpellScript();
        }
};

// Called by Healing Wave - 331, Greater Healing Wave - 77472 and Healing Surge - 8004
// Called by Lightning Bolt - 403, Chain Lightning - 421, Earth Shock - 8042 and Stormstrike - 17364
// Called by Lightning Bolt - 45284, Chain Lightning - 45297
// Conductivity - 108282
class spell_sha_conductivity : public SpellScriptLoader
{
    public:
        spell_sha_conductivity() : SpellScriptLoader("spell_sha_conductivity") { }

        class spell_sha_conductivity_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_conductivity_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (AuraPtr conductivity = _player->GetAura(SPELL_SHA_CONDUCTIVITY_TALENT))
                        {
                            if (DynamicObject* dynObj = _player->GetDynObject(SPELL_SHA_HEALING_RAIN))
                            {
                                int32 remainingDuration = conductivity->GetEffect(EFFECT_0)->GetAmount() * 100;
                                uint32 addDuration = std::min(remainingDuration, 4000);

                                dynObj->SetDuration(dynObj->GetDuration() + addDuration);
                                conductivity->GetEffect(EFFECT_0)->SetAmount((remainingDuration - addDuration) / 100);

                                if (AuraPtr healingRain = _player->GetAura(SPELL_SHA_HEALING_RAIN_AURA))
                                {
                                    healingRain->SetDuration(healingRain->GetDuration() + addDuration);
                                    healingRain->SetMaxDuration(healingRain->GetMaxDuration() + addDuration);
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_sha_conductivity_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_conductivity_SpellScript();
        }
};

// Ancestral Guidance - 108281
class spell_sha_ancestral_guidance : public SpellScriptLoader
{
    public:
        spell_sha_ancestral_guidance() : SpellScriptLoader("spell_sha_ancestral_guidance") { }

        class spell_sha_ancestral_guidance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_ancestral_guidance_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                // Prevent inifinite loop
                if (eventInfo.GetDamageInfo()->GetSpellInfo() &&
                    (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == GetSpellInfo()->Id ||
                    eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_SHA_RESTORATIVE_MISTS ||
                    eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_SHA_ANCESTRAL_GUIDANCE))
                    return;

                Player* _player = GetCaster()->ToPlayer();
                if (!_player)
                    return;

                if (Unit* target = eventInfo.GetActionTarget())
                {
                    int32 bp = eventInfo.GetDamageInfo()->GetDamage() > eventInfo.GetHealInfo()->GetHeal() ? eventInfo.GetDamageInfo()->GetDamage() : eventInfo.GetHealInfo()->GetHeal();
                    if (!bp)
                        return;

                    bp = int32(bp * aurEff->GetAmount() / 100);

                    _player->CastCustomSpell(target, SPELL_SHA_ANCESTRAL_GUIDANCE, &bp, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_ancestral_guidance_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_ancestral_guidance_AuraScript();
        }
};

// 64695 - Earthgrab
class spell_sha_earthgrab : public SpellScriptLoader
{
    public:
        spell_sha_earthgrab() : SpellScriptLoader("spell_sha_earthgrab") { }

        class spell_sha_earthgrab_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_earthgrab_SpellScript);

            void HitTarget(SpellEffIndex)
            {
                Unit* target = GetHitUnit();

                if (target->HasAura(SPELL_SHA_EARTHGRAB_IMMUNITY))
                {
                    GetCaster()->CastSpell(target, SPELL_SHA_EARTHBIND_FOR_EARTHGRAB_TOTEM, true);
                    PreventHitAura();
                    return;
                }

                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, SPELL_SHA_EARTHGRAB_IMMUNITY, true);
            }

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                for (std::list<WorldObject*>::iterator iter = unitList.begin(); iter != unitList.end();)
                    if (Unit* target = (*iter)->ToUnit())
                        if (target->HasAura(SPELL_SHA_EARTHGRAB))
                            iter = unitList.erase(iter);
                        else
                            iter++;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_earthgrab_SpellScript::HitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_earthgrab_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_earthgrab_SpellScript();
        }
};

// Stone Bulwark - 114889
class spell_sha_stone_bulwark : public SpellScriptLoader
{
    public:
        spell_sha_stone_bulwark() : SpellScriptLoader("spell_sha_stone_bulwark") { }

        class spell_sha_stone_bulwark_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_stone_bulwark_AuraScript);

            void OnTick(constAuraEffectPtr p_AurEff)
            {
                if (Unit* l_Caster = GetCaster())
                {
                    if (Unit* l_Owner = l_Caster->GetOwner())
                    {
                        float spellPower = spellPower = l_Owner->ToPlayer()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_ALL);
                        int32 l_Amount = 0.875f * spellPower;

                        if (AuraPtr aura = l_Owner->GetAura(SPELL_SHA_STONE_BULWARK_ABSORB))
                            l_Amount += aura->GetEffect(EFFECT_0)->GetAmount();
                        else if (p_AurEff->GetTickNumber() == 1)
                            l_Amount *= 4.f;

                        if (AuraPtr aura = l_Caster->AddAura(SPELL_SHA_STONE_BULWARK_ABSORB, l_Owner))
                            aura->GetEffect(EFFECT_0)->SetAmount(l_Amount);

                        PreventDefaultAction();
                    }
                }

            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_stone_bulwark_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_stone_bulwark_AuraScript();
        }
};

// Frost Shock - 8056
class spell_sha_frozen_power : public SpellScriptLoader
{
    public:
        spell_sha_frozen_power() : SpellScriptLoader("spell_sha_frozen_power") { }

        class spell_sha_frozen_power_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_frozen_power_SpellScript);

            bool Validate(SpellEntry const * spellEntry)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHA_FROST_SHOCK))
                    return false;
                return true;
            }

            void HandleAfterHit()
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitUnit())
                        if (caster->HasAura(SPELL_SHA_FROZEN_POWER))
                            caster->CastSpell(target, SPELL_SHA_FROST_SHOCK_FREEZE, true);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_sha_frozen_power_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_frozen_power_SpellScript();
        }
};

// Spirit Link - 98020 : triggered by 98017
// Spirit Link Totem
class spell_sha_spirit_link : public SpellScriptLoader
{
    public:
        spell_sha_spirit_link() : SpellScriptLoader("spell_sha_spirit_link") { }

        class spell_sha_spirit_link_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_spirit_link_SpellScript);

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                {
                    // Check against totem caster - WTF ?
                    if (caster->GetEntry() == 53006)
                    {
                        if (caster->GetOwner())
                        {
                            if (Player* _player = caster->GetOwner()->ToPlayer())
                            {
                                std::list<Unit*> memberList;
                                _player->GetPartyMembers(memberList);

                                float totalRaidHealthPct = 0;

                                for (auto itr : memberList)
                                    totalRaidHealthPct += itr->GetHealthPct();

                                totalRaidHealthPct /= memberList.size() * 100.0f;

                                for (auto itr : memberList)
                                    itr->SetHealth(uint32(totalRaidHealthPct * itr->GetMaxHealth()));
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_sha_spirit_link_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_spirit_link_SpellScript();
        }
};

// Fire Nova - 1535
class spell_sha_fire_nova : public SpellScriptLoader
{
    public:
        spell_sha_fire_nova() : SpellScriptLoader("spell_sha_fire_nova") { }

        class spell_sha_fire_nova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_fire_nova_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    if (target->HasAura(SPELL_SHA_FLAME_SHOCK))
                        caster->CastSpell(target, SPELL_SHA_FIRE_NOVA_TRIGGERED, true);
            }

            SpellCastResult HandleCheckCast()
            {
                UnitList targets;
                JadeCore::AnyUnitHavingBuffInObjectRangeCheck u_check(GetCaster(), GetCaster(), 100, SPELL_SHA_FLAME_SHOCK, false);
                JadeCore::UnitListSearcher<JadeCore::AnyUnitHavingBuffInObjectRangeCheck> searcher(GetCaster(), targets, u_check);
                GetCaster()->VisitNearbyObject(100, searcher);

                return targets.size() == 0 ? SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW : SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sha_fire_nova_SpellScript::HandleCheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_fire_nova_SpellScript();
        }
};

// 88766 Fulmination handled in 8042 Earth Shock
class spell_sha_fulmination : public SpellScriptLoader
{
    public:
        spell_sha_fulmination() : SpellScriptLoader("spell_sha_fulmination") { }

        class spell_sha_fulmination_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_fulmination_SpellScript)

            void HandleAfterHit()
            {
                if (Unit* _player = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        AuraPtr lightningShield = _player->GetAura(SPELL_SHA_LIGHTNING_SHIELD_AURA);
                        if (!lightningShield)
                            return;

                        uint8 charges = lightningShield->GetCharges() - 1;
                        if (!charges)
                            return;

                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_SHA_LIGHTNING_SHIELD_ORB_DAMAGE);
                        if (!spellInfo)
                            return;

                        int32 basePoints = _player->CalculateSpellDamage(target, spellInfo, EFFECT_0);
                        uint32 damage = charges * _player->SpellDamageBonusDone(target, spellInfo, basePoints, EFFECT_0, SPELL_DIRECT_DAMAGE);

                        _player->CastCustomSpell(SPELL_SHA_FULMINATION_TRIGGERED, SPELLVALUE_BASE_POINT0, damage, target, true);
                        lightningShield->SetCharges(1);

                        _player->RemoveAura(SPELL_SHA_FULMINATION_INFO);
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_sha_fulmination_SpellScript::HandleAfterHit);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_sha_fulmination_SpellScript();
        }
};

// 77762 Lava Surge
class spell_sha_lava_surge : public SpellScriptLoader
{
    public:
        spell_sha_lava_surge() : SpellScriptLoader("spell_sha_lava_surge") { }

        class spell_sha_lava_surge_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_lava_surge_AuraScript);

            void HandleAuraApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Player* l_Player = GetCaster()->ToPlayer();

                if (!l_Player)
                    return;

                if (l_Player->HasSpellCooldown(SPELL_SHA_LAVA_BURST))
                    l_Player->RemoveSpellCooldown(SPELL_SHA_LAVA_BURST, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sha_lava_surge_AuraScript::HandleAuraApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_lava_surge_AuraScript();
        }
};

// Healing Stream - 52042
class spell_sha_healing_stream : public SpellScriptLoader
{
    public:
        spell_sha_healing_stream() : SpellScriptLoader("spell_sha_healing_stream") { }

        class spell_sha_healing_stream_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_healing_stream_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHA_HEALING_STREAM))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (!GetCaster()->GetOwner())
                    return;

                if (Unit* _player = GetCaster()->GetOwner())
                    if (Unit* target = GetHitUnit())
                        // Glyph of Healing Stream Totem
                        if (target->GetGUID() != _player->GetGUID() && _player->HasAura(SPELL_SHA_GLYPH_OF_HEALING_STREAM_TOTEM))
                            _player->CastSpell(target, SPELL_SHA_GLYPH_OF_HEALING_STREAM, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_healing_stream_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_healing_stream_SpellScript();
        }
};

// Elemental Blast - 117014
class spell_sha_elemental_blast : public SpellScriptLoader
{
    public:
        spell_sha_elemental_blast() : SpellScriptLoader("spell_sha_elemental_blast") { }

        class spell_sha_elemental_blast_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_elemental_blast_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHA_ELEMENTAL_BLAST))
                    return false;
                return true;
            }

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetExplTargetUnit())
                    {
                        caster->CastSpell(target, SPELL_SHA_ELEMENTAL_BLAST_FROST_VISUAL, true);
                        caster->CastSpell(target, SPELL_SHA_ELEMENTAL_BLAST_NATURE_VISUAL, true);
                    }
                }
            }

            void HandleOnHit()
            {
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_sha_elemental_blast_SpellScript::HandleAfterCast);
                OnHit += SpellHitFn(spell_sha_elemental_blast_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_elemental_blast_SpellScript();
        }
};

// Earthquake : Ticks - 77478
class spell_sha_earthquake_tick : public SpellScriptLoader
{
    public:
        spell_sha_earthquake_tick() : SpellScriptLoader("spell_sha_earthquake_tick") { }

        class spell_sha_earthquake_tick_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_earthquake_tick_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHA_EARTHQUAKE_TICK))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                // With a 10% chance of knocking down affected targets
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetHitUnit())
                        if (roll_chance_i(GetSpellInfo()->Effects[EFFECT_1].BasePoints))
                            caster->CastSpell(target, SPELL_SHA_EARTHQUAKE_KNOCKING_DOWN, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_earthquake_tick_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_earthquake_tick_SpellScript();
        }
};

// Earthquake - 61882
class spell_sha_earthquake : public SpellScriptLoader
{
    public:
        spell_sha_earthquake() : SpellScriptLoader("spell_sha_earthquake") { }

        class spell_sha_earthquake_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_earthquake_AuraScript);

            void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                 m_PctBonus = 0.f;

                if (AuraPtr l_Aura = GetCaster()->GetAura(SPELL_SHA_IMPROVED_CHAIN_LIGHTNING))
                {
                    m_PctBonus = l_Aura->GetEffect(EFFECT_0)->GetAmount();
                    l_Aura->Remove();
                }

            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                int32 l_bp0 = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster()) * m_PctBonus / 100;

                if (Unit* caster = GetCaster())
                    if (DynamicObject* dynObj = caster->GetDynObject(SPELL_SHA_EARTHQUAKE))
                        caster->CastCustomSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_SHA_EARTHQUAKE_TICK, &l_bp0, nullptr, nullptr, true);
            }

            float m_PctBonus;

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthquake_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectApply += AuraEffectApplyFn(spell_sha_earthquake_AuraScript::OnApply, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_earthquake_AuraScript();
        }
};

// Healing Rain - 73920
class spell_sha_healing_rain : public SpellScriptLoader
{
    public:
        spell_sha_healing_rain() : SpellScriptLoader("spell_sha_healing_rain") { }

        class spell_sha_healing_rain_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_healing_rain_SpellScript);

            void HandleOnHit()
            {
                if (WorldLocation const* loc = GetExplTargetDest())
                {
                    if (Unit* caster = GetCaster())
                    {
                        // Casting a second healing rain after prolonging the previous one using conductivity
                        // will replace the old healing rain with base amount of duration (in other words, you will not have 2 healing rains).
                        if (DynamicObject* dynObj = caster->GetDynObject(SPELL_SHA_HEALING_RAIN))
                            caster->RemoveDynObject(SPELL_SHA_HEALING_RAIN);

                        caster->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_SHA_HEALING_RAIN, true);

                        if (AuraPtr conductivity = caster->GetAura(SPELL_SHA_CONDUCTIVITY_TALENT))
                            conductivity->GetEffect(EFFECT_0)->SetAmount(conductivity->GetSpellInfo()->Effects[EFFECT_0].BasePoints);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_sha_healing_rain_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_healing_rain_SpellScript();
        }

        class spell_sha_healing_rain_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_healing_rain_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (DynamicObject* dynObj = GetCaster()->GetDynObject(SPELL_SHA_HEALING_RAIN))
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), SPELL_SHA_HEALING_RAIN_TICK, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_healing_rain_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_healing_rain_AuraScript();
        }
};

// Ascendance - 114049
class spell_sha_ascendance : public SpellScriptLoader
{
    public:
        spell_sha_ascendance() : SpellScriptLoader("spell_sha_ascendance") { }

        class spell_sha_ascendance_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_ascendance_SpellScript);

            bool Validate(SpellInfo const* spellEntry)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SHA_ASCENDANCE))
                    return false;
                return true;
            }

            SpellCastResult CheckCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_NONE)
                    {
                        SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_SELECT_TALENT_SPECIAL);
                        return SPELL_FAILED_CUSTOM_ERROR;
                    }
                    else
                        return SPELL_CAST_OK;
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    switch(_player->GetSpecializationId(_player->GetActiveSpec()))
                    {
                        case SPEC_SHAMAN_ELEMENTAL:
                            _player->CastSpell(_player, SPELL_SHA_ASCENDANCE_ELEMENTAL, true);
                            break;
                        case SPEC_SHAMAN_ENHANCEMENT:
                            _player->CastSpell(_player, SPELL_SHA_ASCENDANCE_ENHANCED, true);

                            if (_player->HasSpellCooldown(SPELL_SHA_STORMSTRIKE))
                                _player->RemoveSpellCooldown(SPELL_SHA_STORMSTRIKE, true);
                            break;
                        case SPEC_SHAMAN_RESTORATION:
                            _player->CastSpell(_player, SPELL_SHA_ASCENDANCE_RESTORATION, true);
                            break;
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sha_ascendance_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_sha_ascendance_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_ascendance_SpellScript();
        }
};

class EarthenPowerTargetSelector
{
    public:
        EarthenPowerTargetSelector() { }

        bool operator() (WorldObject* target)
        {
            if (!target->ToUnit())
                return true;

            if (!target->ToUnit()->HasAuraWithMechanic(1 << MECHANIC_SNARE))
                return true;

            return false;
        }
};

class spell_sha_bloodlust : public SpellScriptLoader
{
    public:
        spell_sha_bloodlust() : SpellScriptLoader("spell_sha_bloodlust") { }

        class spell_sha_bloodlust_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_bloodlust_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_SATED))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(JadeCore::UnitAuraCheck(true, SHAMAN_SPELL_SATED));
                targets.remove_if(JadeCore::UnitAuraCheck(true, HUNTER_SPELL_INSANITY));
                targets.remove_if(JadeCore::UnitAuraCheck(true, MAGE_SPELL_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SHAMAN_SPELL_SATED, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_bloodlust_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_bloodlust_SpellScript();
        }
};

class spell_sha_heroism : public SpellScriptLoader
{
    public:
        spell_sha_heroism() : SpellScriptLoader("spell_sha_heroism") { }

        class spell_sha_heroism_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_heroism_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_EXHAUSTION))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(JadeCore::UnitAuraCheck(true, SHAMAN_SPELL_EXHAUSTION));
                targets.remove_if(JadeCore::UnitAuraCheck(true, HUNTER_SPELL_INSANITY));
                targets.remove_if(JadeCore::UnitAuraCheck(true, MAGE_SPELL_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, SHAMAN_SPELL_EXHAUSTION, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_heroism_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_heroism_SpellScript();
        }
};

// 58877 - Spirit Hunt
class spell_sha_spirit_hunt : public SpellScriptLoader
{
    public:
        spell_sha_spirit_hunt() : SpellScriptLoader("spell_sha_spirit_hunt") { }

        class spell_sha_spirit_hunt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_spirit_hunt_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                int32 bp0 = eventInfo.GetDamageInfo()->GetDamage();
                if (Unit* player = GetCaster()->GetOwner())
                    GetCaster()->CastCustomSpell(player, SPELL_SPIRIT_HUNT_HEAL, &bp0, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_spirit_hunt_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_spirit_hunt_AuraScript();
        }
};

// 105792 - Lava Shock Spread
class spell_sha_lava_lash_spread : public SpellScriptLoader
{
    public:
        spell_sha_lava_lash_spread() : SpellScriptLoader("spell_sha_lava_lash_spread") { }

        class spell_sha_lava_lash_spread_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_lava_lash_spread_SpellScript);

            void HitTarget(SpellEffIndex)
            {
                if (Unit* target = GetHitUnit())
                    GetCaster()->AddAura(SPELL_SHA_FLAME_SHOCK, target);
            }

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                uint32 maxTargets = sSpellMgr->GetSpellInfo(SPELL_SHA_LAVA_LASH)->Effects[EFFECT_3].BasePoints;
                std::list<WorldObject*> finalList;

                for (std::list<WorldObject*>::const_iterator iter = unitList.begin(); iter != unitList.end(); iter++)
                    if (Unit* target = (*iter)->ToUnit())
                        if (finalList.size() < maxTargets)
                            if (!target->HasAura(SPELL_SHA_FLAME_SHOCK))
                                finalList.push_back(*iter);

                for (std::list<WorldObject*>::const_iterator iter = unitList.begin(); iter != unitList.end(); iter++)
                    if (Unit* target = (*iter)->ToUnit())
                        if (finalList.size() < maxTargets)
                            if (target->HasAura(SPELL_SHA_FLAME_SHOCK))
                                finalList.push_back(*iter);

                unitList = finalList;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_lava_lash_spread_SpellScript::HitTarget, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_lava_lash_spread_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_lava_lash_spread_SpellScript();
        }
};

// 60103 - Lava Lash
class spell_sha_lava_lash : public SpellScriptLoader
{
    public:
        spell_sha_lava_lash() : SpellScriptLoader("spell_sha_lava_lash") { }

        class spell_sha_lava_lash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_lava_lash_SpellScript);

            void HitTarget(SpellEffIndex)
            {
                if (Unit* l_Target = GetHitUnit())
                    if (l_Target->HasAura(SPELL_SHA_FLAME_SHOCK))
                        GetCaster()->CastSpell(l_Target, SPELL_SHA_LAVA_LASH_SPREAD, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_lava_lash_SpellScript::HitTarget, EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_lava_lash_SpellScript();
        }
};

// 33757 - Windfury
class spell_sha_windfury : public SpellScriptLoader
{
    public:
        spell_sha_windfury() : SpellScriptLoader("spell_sha_windfury") { }

        class spell_sha_windfury_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_windfury_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                Player* caster = GetCaster()->ToPlayer();
                PreventDefaultAction();

                if (!caster->HasSpellCooldown(GetSpellInfo()->Id))
                {
                    if (Unit* victim = eventInfo.GetActionTarget())
                    {
                        if (!victim->IsFriendlyTo(caster))
                        {
                            caster->AddSpellCooldown(GetSpellInfo()->Id, 0, 5 * IN_MILLISECONDS);

                            int count = 3; // Blame blizz

                            if (AuraPtr bonus = GetCaster()->GetAura(SPELL_SHA_PVP_BONUS_WOD_4))
                                count += bonus->GetEffect(EFFECT_0)->GetAmount();

                            for (int i = 0; i < count; i++)
                                caster->CastSpell(victim, SPELL_SHA_WINDFURY_ATTACK, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_windfury_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_windfury_AuraScript();
        }
};

// 10400 - Flametongue
class spell_sha_flametongue : public SpellScriptLoader
{
    public:
        spell_sha_flametongue() : SpellScriptLoader("spell_sha_flametongue") { }

        class spell_sha_flametongue_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_flametongue_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                Unit* target = eventInfo.GetProcTarget();
                SpellInfo const* spellProto = GetSpellInfo();

                if (eventInfo.GetDamageInfo()->GetAttackType() == OFF_ATTACK || spellProto)
                    GetCaster()->CastSpell(target, SPELL_SHA_LAMETONGUE_ATTACK, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_flametongue_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_flametongue_AuraScript();
        }
};

// 157804 - Improved Flame Shock
class spell_sha_improoved_flame_shock : public SpellScriptLoader
{
    public:
        spell_sha_improoved_flame_shock() : SpellScriptLoader("spell_sha_improoved_flame_shock") { }

        class spell_sha_improoved_flame_shock_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_improoved_flame_shock_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (Unit* l_Caster = GetCaster())
                    if (Player* l_Player = l_Caster->ToPlayer())
                        l_Player->RemoveSpellCooldown(SPELL_SHA_LAVA_LASH, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_improoved_flame_shock_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_improoved_flame_shock_AuraScript();
        }
};

// 51533 - Feral Spirit
class spell_sha_feral_spirit : public SpellScriptLoader
{
    public:
        spell_sha_feral_spirit() : SpellScriptLoader("spell_sha_feral_spirit") { }

        class spell_sha_feral_spirit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_feral_spirit_SpellScript);

            void OnLaunch(SpellEffIndex effIndex)
            {
                // Broken spellproc
                if (Unit* caster = GetCaster())
                    if (AuraPtr aura = caster->GetAura(SPELL_SHA_PVP_BONUS_WOD_2))
                        caster->CastSpell(caster, aura->GetSpellInfo()->Effects[0].TriggerSpell);
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_sha_feral_spirit_SpellScript::OnLaunch, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_feral_spirit_SpellScript();
        }
};

// 88766 - Fulmination
class spell_sha_fulmination_proc : public SpellScriptLoader
{
    public:
        spell_sha_fulmination_proc() : SpellScriptLoader("spell_sha_fulmination_proc") { }

        class spell_sha_fulmination_proc_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_fulmination_proc_AuraScript);


            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                Unit* target = eventInfo.GetProcTarget();

                if (!target)
                    return;

                uint32 maxCharges = GetEffect(EFFECT_0)->CalculateAmount(GetCaster());
                if (AuraPtr aura = GetCaster()->GetAura(SPELL_SHA_LIGHTNING_SHIELD))
                {
                    if (aura->GetCharges() < maxCharges)
                        aura->SetCharges(aura->GetCharges() + 1);

                    if (aura->GetCharges() == maxCharges && !GetCaster()->HasAura(SPELL_SHA_FULMINATION_INFO))
                        GetCaster()->CastSpell(GetCaster(), SPELL_SHA_FULMINATION_INFO, true);
                }

            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_fulmination_proc_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_fulmination_proc_AuraScript();
        }
};

// 157765 Enhanced Chain Lightning
class spell_sha_enhanced_chain_lightning : public SpellScriptLoader
{
    public:
        spell_sha_enhanced_chain_lightning() : SpellScriptLoader("spell_sha_enhanced_chain_lightning") { }

        class spell_sha_enhanced_chain_lightning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_enhanced_chain_lightning_AuraScript);


            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                GetCaster()->CastSpell(GetCaster(), SPELL_SHA_IMPROVED_CHAIN_LIGHTNING, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_enhanced_chain_lightning_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_enhanced_chain_lightning_AuraScript();
        }
};

// 170374 - Molten Earth
class spell_sha_molten_earth : public SpellScriptLoader
{
    public:
        spell_sha_molten_earth() : SpellScriptLoader("spell_sha_molten_earth") { }

        class spell_sha_molten_earth_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_molten_earth_AuraScript);


            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_SHA_MOLTEN_EARTH_DAMAGE)
                    return;

                GetCaster()->AddAura(SPELL_SHA_MOLTEN_EARTH_PERIODICAL, eventInfo.GetDamageInfo()->GetVictim());
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_molten_earth_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_molten_earth_AuraScript();
        }
};

// 170377 - Molten Earth Periodic
class spell_sha_molten_earth_periodic : public SpellScriptLoader
{
    public:
        spell_sha_molten_earth_periodic() : SpellScriptLoader("spell_sha_molten_earth_periodic") { }

        class spell_sha_molten_earth_periodic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_molten_earth_periodic_AuraScript);

            void HandleEffectPeriodic(constAuraEffectPtr /*aurEff*/)
            {
                PreventDefaultAction();

                if (GetOwner() && GetOwner()->ToUnit() && GetCaster())
                {
                    int l_Count = irand(1, 2);

                    for (int l_I = 0; l_I < l_Count; l_I++)
                        GetCaster()->CastSpell(GetOwner()->ToUnit(), SPELL_SHA_MOLTEN_EARTH_DAMAGE, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_molten_earth_periodic_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_molten_earth_periodic_AuraScript();
        }
};

// 170379 - Molten Earth Damage
class spell_sha_molten_earth_damage : public SpellScriptLoader
{
    public:
        spell_sha_molten_earth_damage() : SpellScriptLoader("spell_sha_molten_earth_damage") { }

        class spell_sha_molten_earth_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_molten_earth_damage_SpellScript);

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                Unit* l_Target = GetHitUnit();

                if (!l_Target)
                    return;

                if (AuraPtr l_Aura = GetCaster()->GetAura(SPELL_SHA_MOLTEN_EARTH))
                    if (Player* l_Player = GetCaster()->ToPlayer())
                        SetHitDamage(GetHitDamage() * l_Player->GetFloatValue(PLAYER_FIELD_MASTERY) * l_Aura->GetSpellInfo()->Effects[EFFECT_0].BonusMultiplier / 100);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_molten_earth_damage_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_molten_earth_damage_SpellScript();
        }
};


// Echo of Elements - 108283
class spell_sha_echo_of_elements : public SpellScriptLoader
{
    public:
        spell_sha_echo_of_elements() : SpellScriptLoader("spell_sha_echo_of_elements") { }

        class spell_sha_echo_of_elements_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_echo_of_elements_AuraScript);

            void OnProc(constAuraEffectPtr /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();

                Player* l_Player = GetCaster()->ToPlayer();
                if (!l_Player)
                    return;

                switch (l_Player->GetSpecializationId(l_Player->GetActiveSpec()))
                {
                    case SPEC_SHAMAN_ELEMENTAL:
                        l_Player->CastSpell(l_Player, SPELL_SHA_ECHO_OF_THE_ELEMENTS_ELEMENTAL, true);
                        break;
                    case SPEC_SHAMAN_ENHANCEMENT:
                        l_Player->CastSpell(l_Player, SPELL_SHA_ECHO_OF_THE_ELEMENTS_ENHANCEMENT, true);
                        break;
                    case SPEC_SHAMAN_RESTORATION:
                        l_Player->CastSpell(l_Player, SPELL_SHA_ECHO_OF_THE_ELEMENTS_RESTORATION, true);
                        break;
                    default:
                        break;
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_sha_echo_of_elements_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_echo_of_elements_AuraScript();
        }
};

// 152255 Liquid Magma - a bit hacky, will do it properly later
class spell_sha_liquid_magma : public SpellScriptLoader
{
    public:
        spell_sha_liquid_magma() : SpellScriptLoader("spell_sha_liquid_magma") { }

        class spell_sha_liquid_magma_AuraScript: public AuraScript
        {
            PrepareAuraScript(spell_sha_liquid_magma_AuraScript);

            void OnTick(constAuraEffectPtr p_AurEff)
            {
                Unit* l_Caster = GetCaster();
                // hardcoded in the tooltip - no DBC data here
                Unit* l_Target = l_Caster->SelectNearbyTarget(nullptr, 40, 0, false);

                if (l_Target)
                    l_Caster->CastSpell(l_Target, GetSpellInfo()->Effects[p_AurEff->GetEffIndex()].TriggerSpell);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_liquid_magma_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }

        };

        class spell_sha_liquid_magma_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_liquid_magma_SpellScript);

            SpellCastResult HandleCheckCast()
            {
                if (Player* l_Player = GetCaster()->ToPlayer())
                    if (Creature* l_Totem = l_Player->GetMap()->GetCreature(l_Player->m_SummonSlot[SUMMON_SLOT_TOTEM]))
                        if (l_Totem && l_Totem->isTotem())
                            return SPELL_CAST_OK;

                if (GetCaster()->isTotem())
                    return SPELL_CAST_OK;

                SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM);
                return SPELL_FAILED_CUSTOM_ERROR;
            }

            void HandleApply(SpellEffIndex /*effIndex*/)
            {
                if (Player* l_Player = GetHitUnit()->ToPlayer())
                {
                    if (Creature* l_Totem = l_Player->GetMap()->GetCreature(l_Player->m_SummonSlot[SUMMON_SLOT_TOTEM]))
                    {
                        if (l_Totem && l_Totem->isTotem())
                        {
                            l_Totem->AddAura(GetSpellInfo()->Id, l_Totem);
                            PreventHitAura();
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_sha_liquid_magma_SpellScript::HandleCheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_sha_liquid_magma_SpellScript::HandleApply, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_liquid_magma_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_liquid_magma_AuraScript();
        }
};

// 157501 Liquid Magma
class spell_sha_liquid_magma_visual : public SpellScriptLoader
{
    public:
        spell_sha_liquid_magma_visual() : SpellScriptLoader("spell_sha_liquid_magma_visual") { }

        class spell_sha_liquid_magma_visual_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_liquid_magma_visual_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHA_LIQUID_MAGMA_DAMAGE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_liquid_magma_visual_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_liquid_magma_visual_SpellScript();
        }
};

void AddSC_shaman_spell_scripts()
{
    new spell_sha_totemic_projection();
    new spell_sha_hex();
    new spell_sha_water_ascendant();
    new spell_sha_glyph_of_shamanistic_rage();
    new spell_sha_glyph_of_lakestrider();
    new spell_sha_call_of_the_elements();
    new spell_sha_conductivity();
    new spell_sha_ancestral_guidance();
    new spell_sha_earthgrab();
    new spell_sha_stone_bulwark();
    new spell_sha_frozen_power();
    new spell_sha_spirit_link();
    new spell_sha_fire_nova();
    new spell_sha_fulmination();
    new spell_sha_lava_surge();
    new spell_sha_healing_stream();
    new spell_sha_elemental_blast();
    new spell_sha_earthquake_tick();
    new spell_sha_earthquake();
    new spell_sha_healing_rain();
    new spell_sha_ascendance();
    new spell_sha_bloodlust();
    new spell_sha_heroism();
    new spell_sha_spirit_hunt();
    new spell_sha_lava_lash_spread();
    new spell_sha_windfury();
    new spell_sha_flametongue();
    new spell_sha_improoved_flame_shock();
    new spell_sha_feral_spirit();
    new spell_sha_fulmination_proc();
    new spell_sha_enhanced_chain_lightning();
    new spell_sha_molten_earth();
    new spell_sha_molten_earth_periodic();
    new spell_sha_molten_earth_damage();
    new spell_sha_echo_of_elements();
    new spell_sha_lava_lash();
    new spell_sha_liquid_magma();
    new spell_sha_liquid_magma_visual();
}
