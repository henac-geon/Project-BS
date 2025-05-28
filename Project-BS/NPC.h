#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"
#include "AsciiArtRepository.h"

class NPC {
private:
    std::string name;                       // NPC의 이름
    bool isMale;                            // NPC의 성별 (true: 남성, false: 여성)
    std::string art;                        // NPC의 ASCII 아트
    eBookGenre preferredGenre;              // NPC가 선호하는 책 장르
    eBookMood preferredMood;                // NPC가 선호하는 책의 분위기
    int gold;                               // NPC가 가진 골드
    int magicPower;                         // NPC의 마법 기운
    bool borrowed;                          // 책을 빌렸는지 여부
    std::vector<Book*> inventory;           // NPC가 소유한(빌린) 책 목록

    eRequestType requestType;               // NPC의 요청 유형
    std::vector<std::string> dialogues;     // NPC의 대사

public:
    NPC(const std::string& name, bool sex, eBookGenre genre, eBookMood mood, int gold, int magicPower);

    // 책 추천에 대한 반응
    bool rateBook(Book* book) const;

    // 대여/반납 관련
    bool borrowBook(Book* book);
    Book* returnBook();
    bool hasBorrowed() const;

    // NPC의 행동 결정
    bool isReturningBook() const;
    bool wantsRecommendation() const;

    // 재화 관련
    void payGold(int amount);
    void gainExp(int amount);

    // 책이 손상된 경우에 대한 보상을 진행
    void compensateForDamage(Book* book);

    eRequestType getRequestType() const;
    void setRequestType(eRequestType type);

    void setDialogues(const std::vector<std::string>& lines);
    const std::vector<std::string>& getDialogues() const;

    std::string getArt() const;

    void debugPrint() const;
};


#endif // NPC_H
