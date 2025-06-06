#pragma once

#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "Book.h"
#include "Enums.h"
#include <string>
#include <utility>

class BookFactory {
public:
    Book* createBook(const std::string& title, const std::string& description,
        eBookGenre genre, eBookMood mood, int length,
        eBookEdge edge, eBookEtc etc);

    Book* createRandomBook();

private:
    std::pair<std::string, std::string> generateTitleAndDescription(
        eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc);
};

#endif // BOOKFACTORY_H
