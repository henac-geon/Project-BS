#include "CrudStore.h"
#include <iostream>

CrudStore::CrudStore(const std::string& storeName)
    : name(storeName), experience(0), level(1), score(0) {
    // 초기화 작업
    for (int i = 0; i < 5; ++i) {
        inventory.addBook(bookFactory.createRandomBook());
    }
}

void CrudStore::displayStatus() const {
    std::string line;

    line += "마법 기운: " + std::to_string(player.getMagicPower()) + "   ";
    line += "골드: " + std::to_string(player.getGold()) + "   ";
    line += "LV." + std::to_string(player.getLevel()) + " (" + std::to_string(player.getExperience()) + "%)   ";
    line += "서점 랭킹: Rank " + std::to_string(player.getBookstoreRank()) + "   ";
    line += "재고 상태: " + std::to_string(player.getBookStock()) + "/" + std::to_string(player.getMaxBookStock());

    ConsoleIO::println(line);
}

void CrudStore::gainExperience(int amount) {
    experience += amount;
    checkLevelUp();
}

bool CrudStore::checkLevelUp() {
    const int threshold = 100;
    // TODO: 레벨업 로직 따로 만들기(레벨업을 하면 얻는 부과 효과를 구현해야 함)
    if (experience >= threshold) {
        level++;
        experience -= threshold;
        std::cout << "레벨업! 현재 레벨: " << level << std::endl;
        return true;
    }
    return false;
}

int CrudStore::getLevel() const {
    return level;
}

int CrudStore::calculateGoldPenalty(const Book& book) const {
    return 0; // book.getConditionValue() * 10;
}

int CrudStore::calculateMagicPenalty(const Book& book) const {
    return 0; // book.getConditionValue() * 5;
}

// 점수 시스템 구현
void CrudStore::addScore(int amount) {
    score += amount;
}

void CrudStore::deductScore(int amount) {
    score -= amount;
    if (score < 0) score = 0;
}

int CrudStore::getScore() const {
    return score;
}

Inventory& CrudStore::getInventory() {
    return inventory;
}

BookFactory& CrudStore::getBookFactory() {
    return bookFactory;
}

Player& CrudStore::getPlayer() {
    return player;
}

WritingElementManager& CrudStore::getWritingElementManager() {
    return writingElementManager;
}

const std::string& CrudStore::getStoreName() const {
    return name;
}
