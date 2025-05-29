#include "StudentNPC.h"
#include <iostream>

bool StudentNPC::rateBook(Book* book) const {
    std::cout << "학생은 책의 교육적 가치를 평가합니다.\n";
    return true;
}

bool StudentNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* StudentNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool StudentNPC::isReturningBook() const {
    return borrowed;
}

bool StudentNPC::wantsRecommendation() const {
    return !borrowed;
}

void StudentNPC::compensateForDamage(Book* book) {
    std::cout << "학생이 책 손상에 대해 골드로 보상합니다.\n";
    gold -= 5;
}

void StudentNPC::debugPrint() const {
    std::cout << "[Student] " << name << " (gold: " << gold << ", magic: " << magicPower << ")\n";
}
