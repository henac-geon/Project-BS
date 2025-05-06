#ifndef PENALTYSYSTEM_H
#define PENALTYSYSTEM_H

#include "Book.h"

class PenaltySystem {
public:
    static int calculateGoldPenalty(const Book& book);
    static int calculateMagicPenalty(const Book& book);
};

#endif // PENALTYSYSTEM_H
