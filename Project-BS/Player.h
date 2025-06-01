#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    // 멤버 변수
    int magicPower; // 마법 기운
    int gold; // 골드
    int level; // 레벨
    double experience; // 경험치
    int bookstoreRank; // 서점 랭킹
    int bookStock; // 책 재고

    // 상한선 상수
    static constexpr int MAX_MAGIC_POWER = 999999;
    static constexpr int MAX_GOLD = 999999999;
    static constexpr int MAX_LEVEL = 99;
    static constexpr int MAX_BOOKSTORE_RANK = 100;
    static constexpr int MAX_BOOK_STOCK = 40;

public:
    Player();

    // Getter functions
    int getMagicPower() const;
    int getGold() const;
    int getLevel() const;
    double getExperience() const;
    int getBookstoreRank() const;
    int getBookStock() const;
    int getMaxMagicPower() const { return MAX_MAGIC_POWER; }
    int getMaxGold() const { return MAX_GOLD; }
    int getMaxLevel() const { return MAX_LEVEL; }
    int getMaxBookstoreRank() const { return MAX_BOOKSTORE_RANK; }
    int getMaxBookStock() const { return MAX_BOOK_STOCK; }

    // Modifier functions
    void consumeMagicPower(int amount);
    void addGold(int amount);
    void useGold(int amount);
    void gainExperience(double amount);
    void levelUpIfNeeded();
    void updateBookstoreRank(int rank);
    void adjustBookStock(int delta);
};

#endif // PLAYER_H
