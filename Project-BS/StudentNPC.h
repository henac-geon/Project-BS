#pragma once
#ifndef STUDENTNPC_H
#define STUDENTNPC_H

#include "NPC.h"
#include <iostream>

class StudentNPC : public NPC {
public:
    StudentNPC(const std::string& name,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int magicPower);
    Book* requestBook(const std::vector<Book*>& candidates) override;
    bool rateBook(Book* book) const override;
    void compensateForDamage(Book* book) override;
};

#endif // STUDENTNPC_H
