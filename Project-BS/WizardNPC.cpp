#include "NPC.h"
#include "WizardNPC.h"
#include "ConsolePrinter.h"

/**

WizardNPC::WizardNPC(const std::string& name)
    : NPC(name, eBookGenre::Fantasy, eBookMood::Dark, 200, 50) {
}

*/
WizardNPC::WizardNPC(const std::string& name,
    eBookGenre genre,
    eBookMood mood,
    int gold,
    int magicPower)
    : NPC(name, genre, mood, gold, magicPower) {
}

Book* WizardNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.back();
    return nullptr;
}

bool WizardNPC::rateBook(Book* book) const {
    return NPC::rateBook(book); // 마법사 NPC 책 평가
}

void WizardNPC::compensateForDamage(Book* book) {
    ConsolePrinter::println(getName() + " compensates 10 gold.");
    setMagicPower(getMagicPower() - 5);
}