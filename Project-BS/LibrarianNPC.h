#pragma once

#ifndef LIBRARIANNPC_H
#define LIBRARIANNPC_H

#include "NPC.h"

class LibrarianNPC : public NPC {
public:
    LibrarianNPC(const std::string& n, bool s, eBookGenre g, eBookMood m, int gold, int mp)
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
