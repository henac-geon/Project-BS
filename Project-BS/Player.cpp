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

    // 최대 레벨 도달 시 경험치 고정
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
