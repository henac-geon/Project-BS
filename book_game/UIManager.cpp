#include "UIManager.h"
#include <iostream>

void UIManager::displayMainMenu() {
    std::cout << "=== Main Menu ===" << std::endl;
}

void UIManager::displayInventory(const Inventory& inventory) {
    std::cout << "Inventory:" << std::endl;
    for (size_t i = 0; i < inventory.getBooks().size(); ++i) {
        std::cout << i << ": " << inventory.getBooks()[i]->getTitle() << std::endl;
    }
}

void UIManager::displayNPCInteraction(NPC* npc) {
    std::cout << "Interacting with NPC" << std::endl;
}

void UIManager::displayBookDetail(const Book* book) {
    book->displayInfo();
}

void UIManager::displayBookCondition(eBookCondition bc) {
    std::cout << "Condition: " << static_cast<int>(bc) << std::endl;
}

void UIManager::displayPenaltyInfo(int gold, int mp) {
    std::cout << "Gold Penalty: " << gold << ", MP Penalty: " << mp << std::endl;
}

void UIManager::displayAsciiArt(const std::string& art) {
    std::cout << art << std::endl;
}

void UIManager::displayLevelUpMessage(int level) {
    std::cout << "Level Up! New Level: " << level << std::endl;
}

int UIManager::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    int input;
    std::cin >> input;
    return input;
}

void UIManager::displayModeSelection() {
    std::cout << "Select Mode:" << std::endl;
}

void UIManager::displayMiniGameResult(const std::string& result) {
    std::cout << "MiniGame Result: " << result << std::endl;
}
