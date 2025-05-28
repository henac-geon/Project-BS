#include "NPC.h"
#include "WizardNPC.h"
#include "ConsoleIO.h"

WizardNPC::WizardNPC(
    const std::string& name,
    bool isMale,
    eBookGenre genre,
    eBookMood mood,
    int gold,
    int magicPower)
    : NPC(name, isMale, genre, mood, gold, magicPower),
    magicPower(magicPower){
}

Book* WizardNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.back();
    return nullptr;
}

bool WizardNPC::rateBook(Book* book) const {
    return NPC::rateBook(book); // 마법사 NPC 책 평가
}

// 책 손상에 대한 보상 처리
void WizardNPC::compensateForDamage(Book* book) {
}
