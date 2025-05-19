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
    std::string name;               // NPC의 이름
    eBookGenre preferredGenre;      // NPC가 선호하는 책 장르 (Enums.h 참조)
    eBookMood preferredMood;        // NPC가 현재 기분에 맞춰 선호하는 책 분위기
    std::vector<Book*> inventory;   // NPC가 소유하거나 대여 가능한 책 목록
    int gold;                       // NPC가 보유한 금화 (경제 시스템에서 사용)
    int magicPower;                 // NPC의 마법력 (특정 보상 또는 상호작용에 활용)
    eRequestType requestType = eRequestType::GenreAndMood;  // NPC가 원하는 책 추천 조건

public:
    /**
     * @brief NPC 생성자
     * @param name        NPC의 이름
     * @param genre       NPC가 선호하는 책 장르
     * @param mood        NPC가 선호하는 책 분위기
     * @param gold        초기 금화량
     * @param magicPower  초기 마법력
     */
    NPC(const std::string& name,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int magicPower);

    /**
     * @brief 가상 소멸자
     * 파생 클래스에서 동적 할당된 자원을 안전하게 해제하기 위해 선언합니다.
     */
    virtual ~NPC() = default;

    /**
     * @brief NPC가 책을 요청하는 함수
     * @param candidates  요청 가능한 책 후보 목록
     * @return            선택된 Book 포인터 (없으면 nullptr)
     * @note 순수 가상 함수로, 파생 클래스에서 구체적으로 구현해야 합니다.
     */
    virtual Book* requestBook(const std::vector<Book*>& candidates) = 0;

    /**
     * @brief NPC가 책을 평가하는 함수
     * @param book  평가할 책 포인터
     * @return      평가 결과 (true: 만족, false: 불만족)
     * @note NPC의 선호도에 따라 평가 로직을 구현합니다.
     */
    virtual bool rateBook(Book* book) const;

    /**
     * @brief NPC가 손상된 책에 대해 보상하는 함수
     * @param book  손상된 책 포인터
     * @note 책 상태에 따라 금화나 마법력으로 보상을 처리할 로직을 구현합니다.
     */
    virtual void compensateForDamage(Book* book) = 0;

    /**
    * 
    * 외부에서 접근 할 수 있게 만들어주는 get 함수와 set 함수
    * 
    */

    // 이름
    std::string getName() const;
    void setName(const std::string& newName);

    // 장르
    eBookGenre getPreferredGenre() const;
    void setPreferredGenre(eBookGenre genre);

    // 무드
    eBookMood getPreferredMood() const;
    void setPreferredMood(eBookMood mood);

    // 인벤토리 확인
    const std::vector<Book*>& getInventory() const;

    // 골드
    int getGold() const;
    void setGold(int newGold);

    // 마법력
    int getMagicPower() const;
    void setMagicPower(int newMagicPower);

    // 요청 타입
    eRequestType getRequestType() const;
    void setRequestType(eRequestType type);

    // 아트
    std::string getArt() const;

    // 대화
    std::string getDialogue() const;
};

#endif // NPC_H
