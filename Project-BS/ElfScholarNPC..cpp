#include "ElfScholarNPC.h"
#include <iostream>

bool ElfScholarNPC::rateBook(Book* book) const {
    std::cout << "엘프 학자가 문학적 깊이를 평가합니다.\n";
    return true;
}

bool ElfScholarNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* ElfScholarNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool ElfScholarNPC::isReturningBook() const {
    return true;
}

bool ElfScholarNPC::wantsRecommendation() const {
    return preferredMood == eBookMood::Whimsical;
}

void ElfScholarNPC::compensateForDamage(Book* book) {
    std::cout << "엘프는 희귀 약초를 대신 건넵니다.\n";
    gold -= 3;
}

void ElfScholarNPC::debugPrint() const {
    std::cout << "[ElfScholar] " << name << " (magic: " << magicPower << ")\n";
}
