﻿#pragma once

#ifndef STUDENTNPC_H
#define STUDENTNPC_H

#include "NPC.h"

class StudentNPC : public NPC {
public:
    StudentNPC(const std::string& n, bool s, eBookGenre g, eBookMood m, int gold, int mp)
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
