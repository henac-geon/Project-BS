#pragma once

#ifndef LIBRARIANNPC_H
#define LIBRARIANNPC_H

#include "NPC.h"

class LibrarianNPC : public NPC {
public:
    LibrarianNPC(const std::string& n, bool s, eBookGenre g, eBookMood m, int gold, int mp, const std::vector<std::string>& dialogues)
        : NPC(n, s, g, m, gold, mp, dialogues) {
    }

    bool rateBook(Book* book) const override;
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
