#include "NPC.h"
#include "StudentNPC.h"
#include "ConsolePrinter.h"

/**

StudentNPC::StudentNPC(const std::string& name)
    : NPC(name, eBookGenre::Mystery, eBookMood::Light, 100, 10) {
}

*/

StudentNPC::StudentNPC(const std::string& name,
    eBookGenre genre,
    eBookMood mood,
    int gold,
    int magicPower)
    : NPC(name, genre, mood, gold, magicPower) {
}

Book* StudentNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.front();
    return nullptr;
}

bool StudentNPC::rateBook(Book* book) const {
    return NPC::rateBook(book);  // 학생 NPC 책 평가
}

void StudentNPC::compensateForDamage(Book* book) {
    ConsolePrinter::println(getName() + " compensates 10 gold.");
    setGold(getGold() - 10);
}
