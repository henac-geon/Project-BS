#pragma once
#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "enums.h"
#include "WritingElementManager.h"
#include "Player.h"
#include "Book.h"
#include "ConsoleIO.h"
#include "openai_client.h"
#include <string>
#include <vector>

class BookFactory {
public:
    BookFactory();

    Book* createRandomBook();
    Book* createBook(const std::string& title,
        const std::string& description,
        eBookGenre genre,
        eBookMood mood,
        int length,
        eBookEdge edge,
        eBookEtc etc);

    std::pair<std::string, std::string> generateTitleAndDescription(
        eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc);

    void displayPlayerStatus() const;
    void displayCategoryHeaders(const std::vector<std::string>& categories, int colWidth) const;
    void displayAvailableElements() const;

private:
    Player player;
    WritingElementManager elementManager;

    static int wcwidth(wchar_t ucs);
    int getDisplayWidth(const std::string& str) const;
    std::string padRight(const std::string& str, int totalWidth) const;
};

#endif // BOOKFACTORY_H
