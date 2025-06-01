#include "ScienceBook.h"
#include "ConsoleIO.h"


//책의 고유 특성이 있는 거 아니면 책을 굳이 상속할 필요 없이 그냥 book클래스만 써도 될듯
ScienceBook::ScienceBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::SciFi, eBookMood::Emotional, length, edge, etc) {
}

void ScienceBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void ScienceBook::displayInfo() const {
    ConsoleIO::println("Science Book: " + title + " - " + description + " (" + std::to_string(length) + " pages)");
}
