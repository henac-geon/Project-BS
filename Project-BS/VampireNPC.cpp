#include "VampireNPC.h"
#include <iostream>

bool VampireNPC::rateBook(Book* book) const {
    std::cout << "뱀파이어는 어두운 분위기의 책을 좋아합니다.\n";
    return preferredMood == eBookMood::Dark;
}

bool VampireNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* VampireNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool VampireNPC::isReturningBook() const {
    return true;
}

bool VampireNPC::wantsRecommendation() const {
    return true;
}

void VampireNPC::compensateForDamage(Book* book) {
    std::cout << "뱀파이어가 피의 계약서로 보상합니다 (골드 -5).\n";
    gold -= 5;
}

void VampireNPC::debugPrint() const {
    std::cout << "[Vampire] " << name << " (gold: " << gold << ")\n";
}
