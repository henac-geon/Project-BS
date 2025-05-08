#include "ScienceBook.h"

ScienceBook::ScienceBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::SciFi, eBookMood::Emotional, length, eBookEdge::None, eBookEtc::None) {
}

void ScienceBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void ScienceBook::displayInfo() const {
    std::cout << "Science Book: " << title << " - " << description << " (" << length << " pages)" << std::endl;
}
