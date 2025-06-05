#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"

// NPC 클래스는 게임 내 책을 대여하거나 반환하는 손님 역할을 수행합니다.
class NPC {
protected:
    std::string name;                         // NPC 이름
    bool isMale;                              // 성별
    eBookGenre preferredGenre;                // 선호 장르
    eBookMood preferredMood;                  // 선호 분위기
    int gold;                                 // 보유 골드
    int magicPower;                           // 마법 기운
    eRequestType requestType;                 // 요청 유형
    std::vector<std::string> dialogues;       // 대사 목록

    Book* currentBook = nullptr;              // 현재 들고 있는 책, 대여여부까지 체크 가능

public:
    // 생성자 및 소멸자
    NPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int gold, int magicPower);
    virtual ~NPC() = default;

    // 순수 가상 함수 (자식 클래스에서 구현 필요)
    virtual bool rateBook(Book* book) const = 0;           // 책 평가
    virtual bool borrowBook(Book* book) = 0;               // 책 대여 시도
    virtual Book* returnBook() = 0;                        // 책 반환
    virtual bool isReturningBook() const = 0;              // 책을 반환할지 여부
    virtual bool wantsRecommendation() const = 0;          // 추천을 원하는지 여부

    virtual int payGold(int amount = 0) = 0;               // 골드 지불 (구현 방식 다양화)
    virtual int payMagicPower(int amount = 0) = 0;         // 마법 기운 지불 (구현 방식 다양화)
    virtual int payExp(int amount = 0) = 0;                // 경험치 획득 처리 (구현 방식 다양화)

    virtual void compensateForDamage(Book* book) = 0;      // 책이 손상되었을 때 보상 처리
    virtual void debugPrint() const = 0;                   // 디버깅 정보 출력

    // Getter
    std::string getName() const;
    bool getIsMale() const;
    eBookGenre getPreferredGenre() const;
    eBookMood getPreferredMood() const;
    int getGold() const;
    int getMagicPower() const;
    eRequestType getRequestType() const;
    bool hasBorrowed() const;                              // 책을 대여한 상태인지

    // Setter
    void setGold(int amount);
    void setMagicPower(int amount);
    void setRequestType(eRequestType type);
    void setDialogues(const std::vector<std::string>& lines);

    // 행동 관련 메서드
    void removeBook(Book* book); // 책 제거
    std::string getArt() const;                            // NPC 아트 반환

    // 대사 관련
    const std::vector<std::string>& getDialogues() const;
};

#endif // NPC_H
