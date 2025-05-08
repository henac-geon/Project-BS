#pragma once

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "UIManager.h"
#include "Inventory.h"
#include "NPC.h"
#include "ScoreSystem.h"
#include "LevelSystem.h"
#include <vector>
#include <functional>
#include <string>

class GameManager {
public:
    GameManager();
    ~GameManager();

    void run();

private:
    int day;
    int gold;
    int magicPower;

    Inventory inventory;
    UIManager uiManager;
    std::vector<NPC*> npcs;

    ScoreSystem scoreSystem;
    LevelSystem levelSystem;

    void startDay();
    void performWritingPhase();
    void performNPCPhase();
    void performSettlementPhase();
    void endDay();
};

#endif // GAME_MANAGER_H