#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>      // std::string 사용을 위한 헤더
#include <vector>      // std::vector 사용을 위한 헤더
#include "Book.h"     // Book 클래스 정의 포함
#include "Enums.h"    // eBookGenre, eBookMood 열거형 정의 포함
#include "AsciiArtRepository.h"

// NPC(Non-Player Character) 추상 클래스
// 게임 내에서 책을 요청하고 평점 매기기, 손상된 책에 대한 보상을 처리하는 인터페이스 역할을 합니다.
class NPC {
protected:
    std::string name;
    eBookGenre preferredGenre;      // 선호하는 책 장르 (Enums.h 참조)
    eBookMood preferredMood;        // 현재 기분에 맞춰 선호하는 책 분위기
    std::vector<Book*> inventory;   // 소유하거나 대여 가능한 책 목록
    int gold;                       // 보유한 금화 (경제 시스템에서 사용)
    int magicPower;                 // 마법력 (특정 보상 또는 상호작용에 활용)
    eRequestType requestType = eRequestType::GenreAndMood;  // NPC가 원하는 책 추천 조건

public:
    NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower);
    virtual ~NPC() = default;

    virtual Book* requestBook(const std::vector<Book*>& candidates) = 0;

    /// 요청한 책을 평가하는 함수
    virtual bool rateBook(Book* book) const;

    /// NPC가 손상된 책에 대해 보상하는 함수
    virtual void compensateForDamage(Book* book) = 0;


    std::string getName() const;
    eBookGenre getPreferredGenre() const;
    eBookMood getPreferredMood() const;
    const std::vector<Book*>& getInventory() const;
    int getGold() const;
    int getMagicPower() const;
    eRequestType getRequestType() const;
    std::string getArt() const;
    std::string getDialogue() const;

    void setName(const std::string& newName);
    void setPreferredGenre(eBookGenre genre);
    void setPreferredMood(eBookMood mood);
    void setGold(int newGold);
    void setMagicPower(int newMagicPower);
    void setRequestType(eRequestType type);
};

#endif // NPC_H
