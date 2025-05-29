#include "WizardNPC.h"
#include <iostream>

bool WizardNPC::rateBook(Book* book) const {
    std::cout << "마법사는 마법적 에너지를 느끼려 합니다.\n";
    return true;
}

bool WizardNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* WizardNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool WizardNPC::isReturningBook() const {
    return borrowed && (magicPower % 2 == 0);
}

bool WizardNPC::wantsRecommendation() const {
    return magicPower > 50;
}

void WizardNPC::compensateForDamage(Book* book) {
    std::cout << "마법사가 손상된 책을 마법으로 수리하려 하지만 실패했습니다.\n";
    gold -= 10;
}

void WizardNPC::debugPrint() const {
    std::cout << "[Wizard] " << name << " (magic: " << magicPower << ")\n";
}
