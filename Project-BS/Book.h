#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <random>
#include "Enums.h"

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

public:
    Book(const std::string& title,
        const std::string& description,
        eBookGenre genre,
        eBookMood mood,
        int length,
        eBookEdge edge,
        eBookEtc etc);

    virtual ~Book() = default;

    virtual void repair() = 0;

    virtual void displayInfo() const = 0;

    std::string getTitle() const;
    eBookCondition getCondition() const;
    eBookGenre getGenre() const;
    eBookMood getMood() const;
    int getDamage() const;

    void setTitle(const std::string& newTitle);
    //void setCondition(eBookCondition newCondition);
    //void setIsDamaged(bool damaged);
    //void setDamageType(eDamageType type);
    //void setLength(int newLength);
    //void setEdge(eBookEdge newEdge);
    //void setGenre(eBookGenre newGenre);
    //void setMood(eBookMood newMood);
};

#endif // BOOK_H
