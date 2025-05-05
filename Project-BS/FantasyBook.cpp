#include "FantasyBook.h"

FantasyBook::FantasyBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::Fantasy, eBookMood::Whimsical, length, edge, etc) {
}

void FantasyBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void FantasyBook::displayInfo() const {
    std::cout << "Fantasy Book: " << title << " - " << description << " (" << length << " pages)" << std::endl;
}
