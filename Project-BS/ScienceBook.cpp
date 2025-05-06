#include "ScienceBook.h"
#include "ConsolePrinter.h"

ScienceBook::ScienceBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::SciFi, eBookMood::Emotional, length, edge, etc) {
}

void ScienceBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void ScienceBook::displayInfo() const {
    ConsolePrinter::println("Science Book: " + title + " - " + description + " (" + std::to_string(length) + " pages)");
}
