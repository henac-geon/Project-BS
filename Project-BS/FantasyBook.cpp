#include "FantasyBook.h"
#include "ConsoleIO.h"

//장르까진 그러려니 하는데 무드나 딴거는 어떻게 떙겨올지 생각해봐야함.
FantasyBook::FantasyBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::Fantasy, eBookMood::Whimsical, length, eBookEdge::None, eBookEtc::None) {
}

void FantasyBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void FantasyBook::displayInfo() const {
    ConsoleIO::println("Fantasy Book: " + title + " - " + description + " (" + std::to_string(length) + " pages)");
}
