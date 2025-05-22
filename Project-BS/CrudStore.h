#pragma once
#ifndef CURD_STORE_H
#define CURD_STORE_H

#include "Inventory.h"
#include "BookFactory.h"
#include "WritingElementManager.h"
#include "Player.h"
#include "Book.h"

#include <string>

class CrudStore {
private:
    std::string name;

    Inventory inventory;
    BookFactory bookFactory;
    WritingElementManager writingElementManager;
    Player player;

    int experience;
    int level;

    int score;  // ScoreSystem 제거 → 점수 직접 구현

public:
    CrudStore(const std::string& storeName = "쿠르드 상점");

    void displayStatus() const;

    // 경험치 및 레벨
    void gainExperience(int amount);
    bool checkLevelUp();
    int getLevel() const;

    // 페널티
    int calculateGoldPenalty(const Book& book) const;
    int calculateMagicPenalty(const Book& book) const;

    // 점수 시스템 (내부 구현)
    void addScore(int amount);
    void deductScore(int amount);
    int getScore() const;

    // 접근자
    Inventory& getInventory();
    BookFactory& getBookFactory();
    Player& getPlayer();
    WritingElementManager& getWritingElementManager();
    const std::string& getStoreName() const;
};

#endif // KURDS_STORE_H
#pragma once
