#include "ScriptPCH.h"
#include "end_time.h"

enum ScriptTexts
{
    // Nozdormu
    SAY_INTRO_1 = 0, // Tyrande
    SAY_INTRO_2 = 1, // Baine
    SAY_INTRO_3 = 2, // Jaina
    SAY_INTRO_4 = 3, // Sylvanas
    SAY_INTRO_5 = 4, // Sylvanas
};

enum Spells
{
    // Infinite Warden
    SPELL_VOID_SHIELD       = 102599,
    SPELL_VOID_STRIKE       = 102598,

    // Infinite Suppressor
    SPELL_ARCANE_WAVE       = 102601,
    SPELL_TEMPORAL_VORTEX   = 102600,

    // Time-Twisted Breaker
    SPELL_RUPTURE_GROUND    = 102124,
    SPELL_BREAK_ARMOR       = 102132,

    // Time-Twisted Drake
    SPELL_ENRAGE            = 102134,
    SPELL_FLAME_BREATH      = 102135,

    // Time-Twisted Footman
    SPELL_SHIELD_BASH       = 101817,
    SPELL_SHIELD_WALL       = 101811,
    SPELL_THUNDERCLAP       = 101820,

    // Time-Twisted Geist
    SPELL_CADAVER_TOSS      = 109952,
    SPELL_FLESH_RIP         = 102066,
    SPELL_CANNIBALIZE_DUMMY = 109945,
    SPELL_CANNIBALIZE       = 109944,

    // Time-Twisted Priest
    SPELL_POWER_WORD_SHIELD = 102409,
    SPELL_FOUNTAIN_OF_LIGHT = 102405,
    SPELL_LIGHT_RAIN_AURA   = 102406,
    SPELL_LIGHT_RAIN_DMG    = 102407,

    // Time-Twisted Riffleman
    SPELL_MULTI_SHOT        = 102411,
    SPELL_SHOT              = 102410,

    // Time-Twisted Scourge
    SPELL_FACE_KICK         = 101888,
    SPELL_WAIL_OF_THE_DEAD  = 101891,
    SPELL_PUTRID_SPIT       = 102063,

    // Time-Twisted Seer
    SPELL_CALL_FLAMES       = 102156,
    SPELL_SEAR_FLESH        = 102158,

    // Time-Twisted Sorceress
    SPELL_BLINK             = 101812,
    SPELL_ARCANE_BLAST      = 101816
};

enum Events
{
    // Image of Nozdormu
    EVENT_TALK              = 1,
    EVENT_TALK_1            = 2,

    // Infinite Warden
    EVENT_VOID_SHIELD       = 3,
    EVENT_VOID_STRIKE       = 4,
    
    // Infinite Suppressor
    EVENT_ARCANE_WAVE       = 5,
    EVENT_TEMPORAL_VORTEX   = 6
};

enum Adds
{
    NPC_INFINITE_WARDEN         = 54923,
    NPC_INFINITE_SUPPRESSOR     = 54920,

    NPC_TIME_TWISTED_BREAKER    = 54552,
    NPC_RUPTURED_GROUND         = 54566, // temp
    NPC_TIME_TWISTED_DRAKE      = 54543,
    NPC_TIME_TWISTED_SEER       = 54553,
    NPC_CALL_FLAMES             = 54585, // temp
    NPC_UNDYING_FLAME           = 54550,
    
    NPC_TIME_TWISTED_FOOTMAN    = 54687,
    NPC_TIME_TWISTED_PRIEST     = 54690,
    NPC_FOUNTAIN_OF_LIGHT       = 54795, // temp
    NPC_TIME_TWISTED_RIFFLEMAN  = 54693,
    NPC_TIME_TWISTED_SORCERESS  = 54691,

    NPC_TIME_TWISTED_SCOURGE    = 54507,
    NPC_TIME_TWISTED_GEIST      = 54511
};

class npc_end_time_image_of_nozdormu : public CreatureScript
{
    public:

        npc_end_time_image_of_nozdormu() : CreatureScript("npc_end_time_image_of_nozdormu") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_end_time_image_of_nozdormuAI(pCreature);
        }

        struct npc_end_time_image_of_nozdormuAI : public ScriptedAI
        {
            npc_end_time_image_of_nozdormuAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                me->setActive(true);
                id = 0;
                bTalk = false;
                pInstance = me->GetInstanceScript();
            }

            void Reset()
            {
                events.Reset();
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_TALK_JAINA:
                        id = 2;
                        break;
                    case ACTION_TALK_BAINE:
                        id = 1;
                        break;
                    case ACTION_TALK_TYRANDE:
                        id = 0;
                        break;
                    case ACTION_TALK_SYLVANAS:
                        id = 3;
                        break;
                }
                if (pInstance)
                {
                    if (pInstance->GetData(11 + id) != IN_PROGRESS)
                        return;
                    else
                        pInstance->SetData(11 + id, DONE);
                }
                bTalk = true;
                events.ScheduleEvent(EVENT_TALK, 15000);
                if (id == 3)
                    events.ScheduleEvent(EVENT_TALK_1, 25000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!bTalk)
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TALK:
                            Talk(id, 0, 3);
                            if (id != 3)
                                bTalk = false;
                            break;
                        case EVENT_TALK_1:
                            Talk(SAY_INTRO_5, 0, 3);
                            bTalk = false;
                            break;
                    }
                }
            }

        private:
            bool bTalk;
            uint8 id;
            EventMap events;
            InstanceScript* pInstance;
        };
};

class npc_end_time_infinite_warden : public CreatureScript
{
    public:

        npc_end_time_infinite_warden() : CreatureScript("npc_end_time_infinite_warden") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_end_time_infinite_wardenAI(pCreature);
        }

        struct npc_end_time_infinite_wardenAI : public ScriptedAI
        {
            npc_end_time_infinite_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                me->setActive(true);
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_VOID_SHIELD, urand(10000, 20000));
                events.ScheduleEvent(EVENT_VOID_STRIKE, urand(5000, 10000));
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_VOID_SHIELD:
                            DoCast(me, SPELL_VOID_SHIELD);
                            break;
                        case EVENT_VOID_STRIKE:
                            DoCast(me->GetVictim(), SPELL_VOID_STRIKE);
                            events.ScheduleEvent(EVENT_VOID_STRIKE, urand(8000, 15000));
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
        };
};

class npc_end_time_infinite_suppressor : public CreatureScript
{
    public:

        npc_end_time_infinite_suppressor() : CreatureScript("npc_end_time_infinite_suppressor") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_end_time_infinite_suppressorAI(pCreature);
        }

        struct npc_end_time_infinite_suppressorAI : public ScriptedAI
        {
            npc_end_time_infinite_suppressorAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                me->setActive(true);
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {

                events.ScheduleEvent(EVENT_ARCANE_WAVE, 1000);
                events.ScheduleEvent(EVENT_TEMPORAL_VORTEX, 5000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ARCANE_WAVE:
                            DoCast(me->GetVictim(), SPELL_ARCANE_WAVE);
                            events.ScheduleEvent(EVENT_ARCANE_WAVE, 3000);
                            break;
                        case EVENT_TEMPORAL_VORTEX:
                            DoCast(me->GetVictim(), SPELL_TEMPORAL_VORTEX);
                            events.ScheduleEvent(SPELL_TEMPORAL_VORTEX, urand(15000, 20000));
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        private:
            EventMap events;
        };
};

#ifndef __clang_analyzer__
void AddSC_end_time()
{
    new npc_end_time_image_of_nozdormu();
    new npc_end_time_infinite_warden();
    new npc_end_time_infinite_suppressor();
}
#endif
