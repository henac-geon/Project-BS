#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "Inventory.h"
#include "NPC.h"
#include "MiniGame.h"
#include "LevelSystem.h"
#include "ScoreSystem.h"
#include "UIManager.h"

class GameManager {
private:
    Inventory inventory;
    std::vector<NPC*> npcs;
    std::vector<MiniGame*> miniGames;
    int day;
    int gold;
    int magicPower;
    LevelSystem levelSystem;
    ScoreSystem scoreSystem;
    UIManager uiManager;

public:
    GameManager();
    ~GameManager();
    void startDay();
    void writeBook();
    void serveNPCs();
    void dailySummary();
    void endDay();
};

#endif // GAMEMANAGER_H
