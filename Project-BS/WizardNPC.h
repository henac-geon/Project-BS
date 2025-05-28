#pragma once
#ifndef WIZARDNPC_H
#define WIZARDNPC_H

#include "NPC.h"
#include "Book.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief 마법사 타입의 NPC 클래스
 * 마법력을 갖추고 있으며, 책 요청과 평점, 파손 보상 로직을 특화함
 */
class WizardNPC : public NPC {
private:
    int magicPower; ///< 마법사의 마력 수치

public:
    /**
     * @brief WizardNPC 생성자
     * @param name NPC 이름
     * @param genre 선호하는 책 장르
     * @param mood 선호하는 책 분위기
     * @param gold 보유 금액
     * @param magicPower 마법력
     */
    WizardNPC(const std::string& name,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int magicPower);

    /**
     * @brief 후보 책 목록에서 하나의 책을 선택하여 요청
     * @param candidates 후보 책 리스트
     * @return 선택된 책 객체 포인터
     */
    Book* requestBook(const std::vector<Book*>& candidates);
    /**
     * @brief 책에 대한 만족도를 판단하여 평점을 반환
     * @param book 평가할 책 포인터
     * @return 평가 결과 (만족: true, 불만족: false)
     */
    bool rateBook(Book* book) const;

    /**
     * @brief 책이 손상된 경우 마법으로 복원하거나 보상을 진행
     * @param book 손상된 책 포인터
     */
    void compensateForDamage(Book* book);

    /// Getter for magicPower
    int getMagicPower() const { return magicPower; }

    /// Setter for magicPower
    void setMagicPower(int mp) { magicPower = mp; }
};

#endif // WIZARDNPC_H
