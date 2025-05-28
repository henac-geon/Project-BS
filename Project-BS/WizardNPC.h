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
    int magicPower; ///< 마법사의 마력 기운

public:

    WizardNPC(
        const std::string& name,
        bool isMale,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int magicPower);

    // 후보 책 목록에서 하나의 책을 선택하여 요청
    Book* requestBook(const std::vector<Book*>& candidates);

    // 책에 대한 만족도를 판단하여 평점을 반환
    bool rateBook(Book* book) const;

    // 책이 손상된 경우에 대한 보상을 진행
    void compensateForDamage(Book* book);

};

#endif // WIZARDNPC_H
