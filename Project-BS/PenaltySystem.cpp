#include "PenaltySystem.h"


int PenaltySystem::calculateGoldPenalty(const Book& book) {
    return book.getCondition() == eBookCondition::Damaged ? 20 : 10;
}

int PenaltySystem::calculateMagicPenalty(const Book& book) {
    return book.getCondition() == eBookCondition::Damaged ? 5 : 2;
}
