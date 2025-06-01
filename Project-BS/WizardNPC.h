#pragma once

#ifndef WIZARDNPC_H
#define WIZARDNPC_H

#include "NPC.h"

class WizardNPC : public NPC {
public:
    WizardNPC(const std::string& n, bool s, eBookGenre g, eBookMood m, int gold, int mp)
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
