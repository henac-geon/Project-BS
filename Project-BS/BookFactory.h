#pragma once
#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include <string>
#include <vector>
#include <iomanip>     // std::setw
#include "Book.h"
#include "FantasyBook.h"
#include "ScienceBook.h"
#include "ConsoleIO.h"
#include "Player.h"
#include "WritingElementManager.h"
#include "openai_client.h"

class BookFactory {
private:
    Player player;                            // 플레이어 정보
    WritingElementManager elementManager;     // 집필 요소 관리자

    // 내부 출력 보조 함수
    int getDisplayWidth(const std::string& str) const;
    std::string padRight(const std::string& str, int totalWidth) const;
    void displayCategoryHeaders(const std::vector<std::string>& categories, int colWidth) const;

public:
    BookFactory();
    ~BookFactory() = default;

    bool isElementAllowed(const std::string& category, const std::string& option) const;

    // 책 생성
    Book* createBook(const std::string& title, const std::string& description, eBookGenre genre, eBookMood mood, int length, eBookEdge edge, eBookEtc etc);
    Book* createRandomBook();
    std::pair<std::string, std::string> generateTitleAndDescription(
        eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc);

    // 출력 관련
    void displayPlayerStatus() const;
    void displayAvailableElements() const;
};

#endif // BOOKFACTORY_H
