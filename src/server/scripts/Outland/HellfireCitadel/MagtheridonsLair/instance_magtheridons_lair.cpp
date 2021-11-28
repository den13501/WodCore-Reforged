////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2016 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

/* ScriptData
SDName: Instance_Magtheridons_Lair
SD%Complete: 100
SDComment:
SDCategory: Hellfire Citadel, Magtheridon's lair
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "magtheridons_lair.h"

enum eSpells
{
    SPELL_SOUL_TRANSFER        = 30531, // core bug, does not support target 7
    SPELL_BLAZE_TARGET         = 30541, // core bug, does not support target 7
};

#define CHAMBER_CENTER_X            -15.14
#define CHAMBER_CENTER_Y              1.8
#define CHAMBER_CENTER_Z             -0.4

#define MAX_ENCOUNTER 2

#define EMOTE_BONDS_WEAKEN          "'s bonds begin to weaken!"

class instance_magtheridons_lair : public InstanceMapScript
{
    public:
        instance_magtheridons_lair()
            : InstanceMapScript("instance_magtheridons_lair", 544)
        {
        }

        struct instance_magtheridons_lair_InstanceMapScript : public InstanceScript
        {
            instance_magtheridons_lair_InstanceMapScript(Map* map) : InstanceScript(map)
            {
            }

            uint32 m_auiEncounter[MAX_ENCOUNTER];

            uint64 MagtheridonGUID;
            std::set<uint64> ChannelerGUID;
            uint64 DoorGUID;
            std::set<uint64> ColumnGUID;

            uint32 CageTimer;
            uint32 RespawnTimer;

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                MagtheridonGUID = 0;
                ChannelerGUID.clear();
                DoorGUID = 0;
                ColumnGUID.clear();

                CageTimer = 0;
                RespawnTimer = 0;
            }

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (m_auiEncounter[i] == IN_PROGRESS)
                        return true;

                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                case 17257:
                    MagtheridonGUID = creature->GetGUID();
                    break;
                case 17256:
                    ChannelerGUID.insert(creature->GetGUID());
                    break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                case 181713:
                    go->SetUInt32Value(GAMEOBJECT_FIELD_FLAGS, 0);
                    break;
                case 183847:
                    DoorGUID = go->GetGUID();
                    break;
                case 184653: // hall
                case 184634: // six columns
                case 184635:
                case 184636:
                case 184637:
                case 184638:
                case 184639:
                    ColumnGUID.insert(go->GetGUID());
                    break;
                }
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                case DATA_MAGTHERIDON:
                    return MagtheridonGUID;
                }
                return 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                case DATA_MAGTHERIDON_EVENT:
                    m_auiEncounter[0] = data;
                    if (data == NOT_STARTED)
                        RespawnTimer = 10000;
                    if (data != IN_PROGRESS)
                       HandleGameObject(DoorGUID, true);
                    break;
                case DATA_CHANNELER_EVENT:
                    switch (data)
                    {
                    case NOT_STARTED: // Reset all channelers once one is reset.
                        if (m_auiEncounter[1] != NOT_STARTED)
                        {
                            m_auiEncounter[1] = NOT_STARTED;
                            for (std::set<uint64>::const_iterator i = ChannelerGUID.begin(); i != ChannelerGUID.end(); ++i)
                            {
                                if (Creature* Channeler = instance->GetCreature(*i))
                                {
                                    if (Channeler->IsAlive())
                                        Channeler->AI()->EnterEvadeMode();
                                    else
                                        Channeler->Respawn();
                                }
                            }
                            CageTimer = 0;
                            HandleGameObject(DoorGUID, true);
                        }
                        break;
                    case IN_PROGRESS: // Event start.
                        if (m_auiEncounter[1] != IN_PROGRESS)
                        {
                            m_auiEncounter[1] = IN_PROGRESS;
                            // Let all five channelers aggro.
                            for (std::set<uint64>::const_iterator i = ChannelerGUID.begin(); i != ChannelerGUID.end(); ++i)
                            {
                                Creature* Channeler = instance->GetCreature(*i);
                                if (Channeler && Channeler->IsAlive())
                                    Channeler->AI()->AttackStart(Channeler->SelectNearestTarget(999));
                            }
                            // Release Magtheridon after two minutes.
                            Creature* Magtheridon = instance->GetCreature(MagtheridonGUID);
                            if (Magtheridon && Magtheridon->IsAlive())
                            {
                                Magtheridon->MonsterTextEmote(EMOTE_BONDS_WEAKEN, 0);
                                CageTimer = 120000;
                            }
                            HandleGameObject(DoorGUID, false);
                        }
                        break;
                    case DONE: // Add buff and check if all channelers are dead.
                        for (std::set<uint64>::const_iterator i = ChannelerGUID.begin(); i != ChannelerGUID.end(); ++i)
                        {
                            Creature* Channeler = instance->GetCreature(*i);
                            if (Channeler && Channeler->IsAlive())
                            {
                                //Channeler->CastSpell(Channeler, SPELL_SOUL_TRANSFER, true);
                                data = IN_PROGRESS;
                                break;
                            }
                        }
                        break;
                    }
                    m_auiEncounter[1] = data;
                    break;
                case DATA_COLLAPSE:
                    // true - collapse / false - reset
                    for (std::set<uint64>::const_iterator i = ColumnGUID.begin(); i != ColumnGUID.end(); ++i)
                        DoUseDoorOrButton(*i);
                    break;
                default:
                    break;
                }
            }

            uint32 GetData(uint32 type)
            {
                if (type == DATA_MAGTHERIDON_EVENT)
                    return m_auiEncounter[0];
                return 0;
            }

            void Update(uint32 diff)
            {
                UpdateOperations(diff);

                if (CageTimer)
                {
                    if (CageTimer <= diff)
                    {
                        Creature* Magtheridon = instance->GetCreature(MagtheridonGUID);
                        if (Magtheridon && Magtheridon->IsAlive())
                        {
                            Magtheridon->ClearUnitState(UNIT_STATE_STUNNED);
                            Magtheridon->AI()->AttackStart(Magtheridon->SelectNearestTarget(999));
                        }
                        CageTimer = 0;
                    } else CageTimer -= diff;
                }

                if (RespawnTimer)
                {
                    if (RespawnTimer <= diff)
                    {
                        for (std::set<uint64>::const_iterator i = ChannelerGUID.begin(); i != ChannelerGUID.end(); ++i)
                        {
                            if (Creature* Channeler = instance->GetCreature(*i))
                            {
                                if (Channeler->IsAlive())
                                    Channeler->AI()->EnterEvadeMode();
                                else
                                    Channeler->Respawn();
                            }
                        }
                        RespawnTimer = 0;
                    } else RespawnTimer -= diff;
                }
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_magtheridons_lair_InstanceMapScript(map);
        }
};

#ifndef __clang_analyzer__
void AddSC_instance_magtheridons_lair()
{
    new instance_magtheridons_lair();
}
#endif
