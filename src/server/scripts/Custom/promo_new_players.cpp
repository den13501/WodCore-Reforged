////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2016 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <ScriptPCH.h>
#include <ScriptMgr.h>

class PromotionNewPlayers : public PlayerScript
{
public:
    PromotionNewPlayers() :PlayerScript("PromotionNewPlayers") {}

    enum Values
    {
        Noverber302021 = 1638201600,  ///< Timestamp of 30nd of Noverber 2021.
        Noverber302049  = 2521814400,  ///< Timestamp of 23nd of Noverber 2049.
        Noverber152049 = 2520518400,  ///< Timestamp of 15nd of Noverber 2049.
        SwiftNetherDrake = 37015,   //SpellId. 迅捷虛空幼龍 https://cn.tbc.wowhead.com/spell=37015
        BlackQirajiBattletank = 26656, //SpellId. 黑色其拉作戰坦克
        ImperialQuilen   = 85870,   //ItemId
        ApprenticeRidingSkill = 33388 //初級騎術
    };

    void OnLogin(Player* p_Player)
    {
        if (time(NULL) < Values::Noverber302021 && p_Player->GetTotalPlayedTime() <= 3600)
        {
            p_Player->learnSpell(Values::ApprenticeRidingSkill, false);
            p_Player->learnSpell(Values::BlackQirajiBattletank, false);
        }

        if (time(nullptr) < Values::Noverber302049
            && p_Player->GetSession()->GetAccountJoinDate() >= Values::Noverber152049
            && p_Player->GetTotalPlayedTime() <= 3600)
            p_Player->AddItem(Values::ImperialQuilen, 1);
    }
};

#ifndef __clang_analyzer__
void AddSC_promotion_new_players()
{
    new PromotionNewPlayers();
};
#endif
