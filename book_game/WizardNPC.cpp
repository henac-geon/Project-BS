#include "WizardNPC.h"

WizardNPC::WizardNPC(const std::string& name)
    : NPC(name, eBookGenre::Fantasy, eBookMood::Dark, 200, 50) {}

Book* WizardNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.back();
    return nullptr;
}

bool WizardNPC::rateBook(Book* book) {
    return true;
}

void WizardNPC::compensateForDamage(Book* book) {
    std::cout << name << " uses magic to compensate." << std::endl;
    magicPower -= 5;
}
