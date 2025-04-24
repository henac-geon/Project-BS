#include "Book.h"

Book::Book(const std::string& title, const std::string& description, eBookGenre genre, eBookMood mood, int length)
    : title(title), description(description), genre(genre), mood(mood), length(length), isDamaged(false), damageType(eDamageType::Lost), condition(eBookCondition::Perfect) {}

std::string Book::getTitle() const {
    return title;
}
