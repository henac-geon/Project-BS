#pragma once

#ifndef CURD_STORE_H
#define CURD_STORE_H

#include <vector>
#include <string>
#include "Book.h"
#include "BookFactory.h"
#include "Inventory.h"
#include "WritingElementManager.h"
#include "Enums.h"

// 상수 정의 (적절한 값 지정 필요)
constexpr int MAX_MAGIC_POWER = 100;
constexpr int MAX_GOLD = 99999;
constexpr int MAX_LEVEL = 10;
constexpr int MAX_BOOKSTORE_RANK = 5;
constexpr int MAX_BOOK_STOCK = 50;

class CrudStore {
private:
    int level;
    double experience;
    int magicPower;
    int gold;
    int bookstoreRank;
    int bookStock;
    int maxBookStock = 5; // 최대 책 재고 수

    int dailyGoldEarned = 0;
    int dailyScoreEarned = 0;
    int dailyMagicPowerEarned = 0;
    int dailyExperienceEarned = 0;
    int numberOfVisitorsToday = 4; // 오늘 방문할 NPC 수

    int rankPoints = 0;              // 랭킹 포인트
    int dailyRankPointsEarned = 0;   // 오늘 얻은 랭킹 포인트

    int satisfiedCount = 0; // 만족한 고객 수
    int dissatisfiedCount = 0; // 불만족한 고객 수

    Inventory inventory;
    BookFactory bookFactory;
    WritingElementManager writingElementManager;

    bool canAffordGold(int amount);
public:
    CrudStore();

    // 상태 표시
    void displayStatus() const;
    void displayDailySummary() const;

    // 경험치 및 레벨 관련
    void gainExperience(int amount);
    bool checkLevelUp();
    int getLevel() const;
    double getExperience() const;

    void setnumberOfVisitorsToday(int num);
    int getNumberOfVisitorsToday() const;

    // 마법 기운 관련
    int getMagicPower() const;
    void consumeMagicPower(int amount);
    void restoreMagicPower(int amount);
    void addMagicPower(int amount);
    void setMagicPower(int amount);

    // 골드 관련
    int getGold() const;
    void setGold(int amount);
    void addGold(int amount);
    void useGold(int amount);

    // 랭킹 / 재고
    int getBookstoreRank() const;
    void setBookstoreRank(int rank);
    int getBookStock() const;
    void setBookStock(int stock);
    int getMaxBookStock() const;
    void adjustBookStock(int delta);
    void increaseMaxBookStock(int amount);

    // 일일 수익 기록
    void addDailyGold(int amount);
    void addDailyMagicPower(int amount);
    void addDailyExperience(int amount);
    int getDailyGoldEarned() const;
    int getDailyMagicPowerEarned() const;
    int getDailyExperienceEarned() const;
    void resetDailyEarnings();

    // 랭킹 포인트
    int getRankPoints() const;
    int getDailyRankPointsEarned() const;
    void addRankPoints(int amount);
    void addDailyRankPoints(int amount);
    void checkupRankUP();

    // 요소 접근자
    Inventory& getInventory();
    BookFactory& getBookFactory();
    WritingElementManager& getWritingElementManager();

    std::string formatEnumElement(WritingElementCategory category, int enumValue) const;


    // 책 집필 전 요소 가능 여부 검사
    bool canAffordBookElements(eBookGenre genre, eBookMood mood, int length,
        eBookEdge edge, eBookEtc etc) const;

    // 책 집필 시도
    Book* tryWriteBook(const std::string& title, const std::string& desc,
        eBookGenre genre, eBookMood mood, int length,
        eBookEdge edge, eBookEtc etc);

    // 요소 목록 출력
    void displayAvailableElements() const;

    // 추후 구현
    int calculateGoldPenalty(const Book& book) const;
    int calculateMagicPenalty(const Book& book) const;

    void incrementSatisfied() { satisfiedCount++; }
    void incrementDissatisfied() { dissatisfiedCount++; };

    void displayCustomerSatisfaction() const;
    void resetSatisfactionCounters();
};

#endif // KURDS_STORE_H
