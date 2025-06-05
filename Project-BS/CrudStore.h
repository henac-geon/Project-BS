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

    int dailyGoldEarned = 0;    // 하루 동안 벌어들인 총 골드
    int dailyScoreEarned = 0;   // 하루 동안 획득한 점수
    int dailyMagicPowerEarned = 0;
    int dailyExperienceEarned = 0; // 하루 동안 획득한 경험치

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


    // 하루 수익 누적
    void addDailyGold(int amount);
    void addDailyMagicPower(int amount);
    void addDailyScore(int amount);
    void addDailyExperience(int amount);

    // 하루 정산 시 사용
    int getDailyGoldEarned() const;
    int getDailyMagicPowerEarned() const;
    int getDailyScoreEarned() const;
    int getDailyExperienceEarned() const;
    void resetDailyEarnings();  // 정산 후 초기화

    void displayDailySummary() const;
};

#endif // KURDS_STORE_H
#pragma once
