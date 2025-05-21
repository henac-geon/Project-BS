#include "Player.h"


Player::Player()
    : magicPower(999999), gold(999999999), level(9), levelProgress(99.99), bookstoreRank(99), bookStock(40) {
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
    while (levelProgress >= 100.0) {
        level++;
        levelProgress -= 100.0;
    }
}

void Player::updateBookstoreRank(int rank) {
    bookstoreRank = rank;
}

void Player::adjustBookStock(int delta) {
    bookStock += delta;
    if (bookStock < 0) bookStock = 0;
}
