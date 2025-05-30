#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <random>
#include "Enums.h"
#include "ConsoleIO.h"

class Book {
private:
    // 책의 상태를 범위 형태로 반환하는 함수
    int getRandomInRange(int min, int max) const;

protected:
    std::string title;           // 책 제목
    std::string description;     // 책 설명 또는 요약
    eBookGenre genre;            // 책 장르 (Enums.h 참고)
    eBookMood mood;              // 책이 전달하는 분위기 (Enums.h 참고)
    int length;                  // 책의 분량 (페이지 수 또는 읽기 소요 시간)
    eBookEdge edge;              // 책의 반전 요소
    eBookEtc etc;                // 기타
    bool isDamaged;              // 책 손상 여부 (true: 손상됨, false: 양호)
    eDamageType damageType;      // 손상 유형 (Enums.h에 정의된 eDamageType)
    eBookCondition condition;    // 책 상태 (Enums.h에 정의된 eBookCondition)
    int conditionValue;          // 0~100 사이의 수치형 상태값
    bool available;              // 책의 대여 가능 여부 (true: 대여 가능, false: 대여 불가)

public:
    Book(const std::string& title,
        const std::string& description,
        eBookGenre genre,
        eBookMood mood,
        int length,
        eBookEdge edge,
        eBookEtc etc);

    ~Book() = default;

    void repair();

    void displayInfo() const;

    std::string getTitle() const;
    eBookCondition getCondition() const;
    eBookGenre getGenre() const;
    eBookMood getMood() const;
    std::string getGenreName() const;
    std::string getMoodName() const;
    std::string getEdgeName() const;
    std::string getEtcName() const;
    //std::string getStockSymbol() const; // 재고 여부
    int getVolume() const;  // = length
    std::string getConditionPercentText() const;


    void setTitle(const std::string& newTitle);
    void setCondition(eBookCondition newCondition);
    void setIsDamaged(bool damaged);
    void setDamageType(eDamageType type);
    //void setLength(int newLength);
    //void setEdge(eBookEdge newEdge);
    //void setGenre(eBookGenre newGenre);
    //void setMood(eBookMood newMood);

    // 대여 가능 여부
    bool isAvailable() const { return available; }
    void setAvailable(bool a) { available = a; }

    // 책 상태 (손상도)
    void setConditionValue(int value) { conditionValue = value; }
    int getConditionValue() const;
};

#endif // BOOK_H
