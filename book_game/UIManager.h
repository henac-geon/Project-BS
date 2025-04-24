#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include "Inventory.h"
#include "NPC.h"
#include "Book.h"
#include "Enums.h"

class UIManager {
public:
    void displayMainMenu();
    void displayInventory(const Inventory& inventory);
    void displayNPCInteraction(NPC* npc);
    void displayBookDetail(const Book* book);
    void displayBookCondition(eBookCondition bc);
    void displayPenaltyInfo(int gold, int mp);
    void displayAsciiArt(const std::string& art);
    void displayLevelUpMessage(int level);
    int getUserInput(const std::string& prompt);
    void displayModeSelection();
    void displayMiniGameResult(const std::string& result);
};

#endif // UIMANAGER_H
