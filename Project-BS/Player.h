#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int magicPower;
    int gold;
    int level;
    double levelProgress; // 0.0 ~ 100.0
    int bookstoreRank;
    int bookStock;

public:
    Player();

    // Getter functions
    int getMagicPower() const;
    int getGold() const;
    int getLevel() const;
    double getLevelProgress() const;
    int getBookstoreRank() const;
    int getBookStock() const;

    // Modifier functions
    void consumeMagicPower(int amount);
    void addGold(int amount);
    void useGold(int amount);
    void gainExperience(double percent);
    void levelUpIfNeeded();
    void updateBookstoreRank(int rank);
    void adjustBookStock(int delta);
};

#endif // PLAYER_H
