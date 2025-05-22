#include "CrudStore.h"
#include <iostream>

CrudStore::CrudStore(const std::string& storeName)
    : name(storeName), experience(0), level(1), score(0) {
}

void CrudStore::displayStatus() const {
    std::cout << "===== [" << name << "] 상태 출력 =====" << std::endl;
    std::cout << "레벨: " << level << " (" << experience << " XP)" << std::endl;
    std::cout << "골드: " << player.getGold() << std::endl;
    std::cout << "마법력: " << player.getMagicPower() << std::endl;
    std::cout << "서점 등급: " << player.getBookstoreRank() << std::endl;
    std::cout << "책 보유량: " << player.getBookStock() << std::endl;
    std::cout << "평판 점수: " << score << std::endl;
    std::cout << "====================================" << std::endl;
}

void CrudStore::gainExperience(int amount) {
    experience += amount;
    checkLevelUp();
}

bool CrudStore::checkLevelUp() {
    const int threshold = 100;
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
    return book.getDamage() * 10;
}

int CrudStore::calculateMagicPenalty(const Book& book) const {
    return book.getDamage() * 5;
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
