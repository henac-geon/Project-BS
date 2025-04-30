#include "PenaltySystem.h"


// condition가 protected라 접근 불가, 수정해야 함
int PenaltySystem::calculateGoldPenalty(const Book& book) {
    return book.condition == eBookCondition::Damaged ? 20 : 10;
}

// condition가 protected라 접근 불가, 수정해야 함
int PenaltySystem::calculateMagicPenalty(const Book& book) {
    return book.condition == eBookCondition::Damaged ? 5 : 2;
}
