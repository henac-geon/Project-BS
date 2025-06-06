#pragma once

#ifndef CURD_STORE_H
#define CURD_STORE_H

#include <string>
#include "BookFactory.h"
#include "Inventory.h"
#include "WritingElementManager.h"

class CrudStore {
public:
    CrudStore();

    // 상태 출력
    void displayStatus() const;
    void displayDailySummary() const;

    // 경험치/레벨
    void gainExperience(int amount);
    bool checkLevelUp();
    int getLevel() const;

    // 점수
    void addScore(int amount);
    void deductScore(int amount);
    int getScore() const;

    // 페널티 계산
    int calculateGoldPenalty(const Book& book) const;
    int calculateMagicPenalty(const Book& book) const;

    // 요소 접근자
    Inventory& getInventory();
    BookFactory& getBookFactory();
    WritingElementManager& getWritingElementManager();

    // 일일 리워드
    void addDailyGold(int amount);
    void addDailyScore(int amount);
    void addDailyMagicPower(int amount);
    void addDailyExperience(int amount);
    void resetDailyEarnings();
    int getDailyGoldEarned() const;
    int getDailyScoreEarned() const;
    int getDailyMagicPowerEarned() const;
    int getDailyExperienceEarned() const;

    // 리소스 관리 (통합된 Player 기능)
    int getMagicPower() const;
    int getGold() const;
    double getExperience() const;
    int getBookstoreRank() const;
    int getBookStock() const;
    int getMaxBookStock() const;

    void consumeMagicPower(int amount);
    void restoreMagicPower(int amount);
    void addMagicPower(int amount);
    void setMagicPower(int amount);
    void setGold(int amount);
    void addGold(int amount);
    void useGold(int amount);
    void setBookstoreRank(int rank);
    void setBookStock(int stock);
    void adjustBookStock(int delta);

    bool canAffordBookElements(eBookGenre genre, eBookMood mood, int length, eBookEdge edge, eBookEtc etc) const;
    Book* tryWriteBook(const std::string& title, const std::string& desc, eBookGenre genre, eBookMood mood, int length, eBookEdge edge, eBookEtc etc);

    template <typename T>
    std::vector<ElementData<T>> getAvailableElements(WritingElementCategory category) const;

    void displayAvailableElements() const;

private:
    // 게임 진행 상태
    int level = 1;
    double experience = 0.0;
    int score = 0;

    // 리소스 (Player 기능)
    int magicPower = 100;
    int gold = 0;
    int bookstoreRank = 1;
    int bookStock = 0;

    static constexpr int MAX_MAGIC_POWER = 100;
    static constexpr int MAX_GOLD = 99999;
    static constexpr int MAX_LEVEL = 99;
    static constexpr int MAX_BOOKSTORE_RANK = 5;
    static constexpr int MAX_BOOK_STOCK = 50;

    // 구성 요소
    Inventory inventory;
    BookFactory bookFactory;
    WritingElementManager writingElementManager;

    // 일일 리워드
    int dailyGoldEarned = 0;
    int dailyScoreEarned = 0;
    int dailyMagicPowerEarned = 0;
    int dailyExperienceEarned = 0;
};

#endif // KURDS_STORE_H
