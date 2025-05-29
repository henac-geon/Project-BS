#include "FantasyBook.h"
#include "ConsoleIO.h"

//책의 고유 특성이 있는 거 아니면 책을 굳이 상속할 필요 없이 그냥 book클래스만 써도 될듯
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
