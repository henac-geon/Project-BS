#include "KnightNPC.h"
#include <iostream>

bool KnightNPC::rateBook(Book* book) const {
    return preferredGenre == eBookGenre::Fantasy || preferredGenre == eBookGenre::NonFiction;
}

bool KnightNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* KnightNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool KnightNPC::isReturningBook() const {
    return true;
}

bool KnightNPC::wantsRecommendation() const {
    return true;
}

void KnightNPC::compensateForDamage(Book* book) {
    std::cout << "기사답게 즉시 보상합니다.\n";
    gold -= 10;
}

void KnightNPC::debugPrint() const {
    std::cout << "[Knight] " << name << " (gold: " << gold << ")\n";
}
