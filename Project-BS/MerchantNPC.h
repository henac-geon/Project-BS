#pragma once

#ifndef MERCHANTNPC_H
#define MERCHANTNPC_H

#include "NPC.h"

class MerchantNPC : public NPC {
public:
    MerchantNPC(const std::string& n, bool s, eBookGenre g, eBookMood m, int gold, int mp)
        : NPC(n, s, g, m, gold, mp) {
    }

    bool rateBook(Book* book) const override;
    bool borrowBook(Book* book) override;
    Book* returnBook() override;
    bool isReturningBook() const override;
    bool wantsRecommendation() const override;
    void compensateForDamage(Book* book) override;
    void debugPrint() const override;
};

#endif
