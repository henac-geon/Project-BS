#include "Player.h"


Player::Player()
    : magicPower(0), gold(0), level(99), levelProgress(0), bookstoreRank(99), bookStock(0) {
}

int Player::getMagicPower() const { return magicPower; }
int Player::getGold() const { return gold; }
int Player::getLevel() const { return level; }
double Player::getLevelProgress() const { return levelProgress; }
int Player::getBookstoreRank() const { return bookstoreRank; }
int Player::getBookStock() const { return bookStock; }

void Player::consumeMagicPower(int amount) {
    if (amount > 0 && magicPower >= amount) {
        magicPower -= amount;
    }
}

void Player::addGold(int amount) {
    if (amount > 0) {
        gold += amount;
    }
}

void Player::useGold(int amount) {
    if (amount > 0 && gold >= amount) {
        gold -= amount;
    }
}

void Player::gainExperience(double percent) {
    levelProgress += percent;
    levelUpIfNeeded();
}

void Player::levelUpIfNeeded() {
    while (true) {
        // 경험치 요구량이 레벨에 비례하여 증가 (예: 기본 100에 레벨당 10% 증가)
        double requiredExp = 100.0 * (1.0 + 0.1 * level);
        if (levelProgress < requiredExp) break;
        level++;
        levelProgress -= requiredExp;
    }
}

void Player::updateBookstoreRank(int rank) {
    bookstoreRank = rank;
}

/// 책 재고를 조정하여 마이너스가 되지 않도록 하는 기능
void Player::adjustBookStock(int delta) {
    bookStock += delta;
    if (bookStock < 0) bookStock = 0;
}
