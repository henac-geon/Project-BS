#include "GameManager.h"
#include "BookFactory.h"
#include "PenaltySystem.h"

GameManager::GameManager(): day(1), gold(0), magicPower(0) {
    // Optionally initialize NPCs and miniGames
}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
    for (auto mg : miniGames) delete mg;
}

void GameManager::startDay() {
    uiManager.displayMainMenu();
}

void GameManager::writeBook() {
    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
}

void GameManager::serveNPCs() {
    for (auto npc : npcs) {
        auto book = npc->requestBook(inventory.getBooks());
        bool satisfied = false;
        if (book) {
            satisfied = npc->rateBook(book);
            if (!satisfied) {
                int gp = PenaltySystem::calculateGoldPenalty(*book);
                int mp = PenaltySystem::calculateMagicPenalty(*book);
                uiManager.displayPenaltyInfo(gp, mp);
            }
        }
        scoreSystem.updateScore(satisfied);
    }
}

void GameManager::dailySummary() {
    uiManager.displayAsciiArt("Day Summary");
}

void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    day++;
}
