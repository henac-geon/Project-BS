#pragma once

#ifndef WIZARDNPC_H
#define WIZARDNPC_H

#include "NPC.h"

class WizardNPC : public NPC {
public:
    WizardNPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int len, eBookEdge edge, eBookEtc etc, int gold, int magicPower, const std::vector<std::string>& dialogues)
        : NPC(name, isMale, genre, mood, len, edge, etc, gold, magicPower, dialogues)
    {
    }
    // 필수 메서드 구현
    int rateBook(Book* book) const override;
    bool borrowBook(Book* book) override;
    Book* returnBook() override;
    bool isReturningBook() const override;
    bool wantsRecommendation() const override;
    void compensateForDamage(Book* book) override;
    void debugPrint() const override;

    int payGold(int amount = 0) override;               // 골드 지불 (구현 방식 다양화)
    int payMagicPower(int amount = 0) override;         // 마법 포인트 지불 (구현 방식 다양화)
    int payExp(int amount = 0) override;                // 경험치 지불 (구현 방식 다양화)
};

#endif
