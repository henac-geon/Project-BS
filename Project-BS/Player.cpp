#include "Player.h"

// 생성자
Player::Player()
    : magicPower(MAX_MAGIC_POWER), gold(0), level(1),
    experience(0.0), bookstoreRank(1), bookStock(0) {
}

// Getter 함수들
int Player::getMagicPower() const { return magicPower; }
int Player::getGold() const { return gold; }
int Player::getLevel() const { return level; }
double Player::getExperience() const { return experience; }
int Player::getBookstoreRank() const { return bookstoreRank; }
int Player::getBookStock() const { return bookStock; }

// Modifier 함수들
void Player::consumeMagicPower(int amount) {
    if (amount < 0) return;
    magicPower -= amount;
    if (magicPower < 0) magicPower = 0;
}

void Player::restoreMagicPower(int amount) {
    if (amount < 0) return;
    magicPower += amount;
    if (magicPower > MAX_MAGIC_POWER) magicPower = MAX_MAGIC_POWER;
}

void Player::addMagicPower(int amount) {
    if (amount < 0) return;
    magicPower += amount;
    if (magicPower > MAX_MAGIC_POWER) magicPower = MAX_MAGIC_POWER;
}

void Player::setMagicPower(int amount) {
    if (amount < 0) amount = 0;
    if (amount > MAX_MAGIC_POWER) amount = MAX_MAGIC_POWER;
    magicPower = amount;
}

void Player::setGold(int amount) {
    if (amount < 0) amount = 0;
    if (amount > MAX_GOLD) amount = MAX_GOLD;
    gold = amount;
}

void Player::setLevel(int lvl) {
    if (lvl < 1) lvl = 1;
    if (lvl > MAX_LEVEL) lvl = MAX_LEVEL;
    level = lvl;
}

void Player::setExperience(double amount) {
    if (amount < 0.0) amount = 0.0;
    experience = amount;
    levelUpIfNeeded();
}

void Player::setBookstoreRank(int rank) {
    if (rank >= 1 && rank <= MAX_BOOKSTORE_RANK)
        bookstoreRank = rank;
}

void Player::setBookStock(int stock) {
    if (stock < 0) stock = 0;
    if (stock > MAX_BOOK_STOCK) stock = MAX_BOOK_STOCK;
    bookStock = stock;
}

void Player::addGold(int amount) {
    if (amount < 0) return;
    gold += amount;
    if (gold > MAX_GOLD) gold = MAX_GOLD;
}

void Player::useGold(int amount) {
    if (amount < 0) return;
    gold -= amount;
    if (gold < 0) gold = 0;
}

void Player::gainExperience(double amount) {
    if (amount < 0.0) return;
    experience += amount;
    levelUpIfNeeded();
}

void Player::levelUpIfNeeded() {
    while (level < MAX_LEVEL) {
        double requiredExp = 100.0 * level;
        if (experience >= requiredExp) {
            experience -= requiredExp;
            level++;
        }
        else {
            break;
        }
    }

    if (level >= MAX_LEVEL) {
        level = MAX_LEVEL;
        experience = 0.0;
    }
}

void Player::updateBookstoreRank(int rank) {
    if (rank >= 1 && rank <= MAX_BOOKSTORE_RANK) {
        bookstoreRank = rank;
    }
}

void Player::adjustBookStock(int delta) {
    bookStock += delta;
    if (bookStock > MAX_BOOK_STOCK) bookStock = MAX_BOOK_STOCK;
    if (bookStock < 0) bookStock = 0;
}
