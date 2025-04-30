#include "StudentNPC.h"

StudentNPC::StudentNPC(const std::string& name)
    : NPC(name, eBookGenre::Mystery, eBookMood::Light, 100, 10) {
}

Book* StudentNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.front();
    return nullptr;
}

bool StudentNPC::rateBook(Book* book) {
    return true;
}

void StudentNPC::compensateForDamage(Book* book) {
    std::cout << name << " compensates 10 gold." << std::endl;
    gold -= 10;
}
