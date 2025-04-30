#include "PenaltySystem.h"


// condition�� protected�� ���� �Ұ�, �����ؾ� ��
int PenaltySystem::calculateGoldPenalty(const Book& book) {
    return book.condition == eBookCondition::Damaged ? 20 : 10;
}

// condition�� protected�� ���� �Ұ�, �����ؾ� ��
int PenaltySystem::calculateMagicPenalty(const Book& book) {
    return book.condition == eBookCondition::Damaged ? 5 : 2;
}
