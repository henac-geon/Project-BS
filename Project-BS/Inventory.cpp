﻿#include "Inventory.h"
#include "ConsoleIO.h"
#include <algorithm>


void Inventory::addBook(Book* book) {
    books.push_back(book);
}

Book* Inventory::findBook(const std::string& title) const {
    auto it = std::find_if(books.begin(), books.end(), [&](Book* b) {
        return b->getTitle() == title;
        });
    if (it != books.end()) {
        return *it;
    }
    return nullptr;
}


const std::vector<Book*>& Inventory::getBooks() const {
    return books;
}


void Inventory::removeBook(Book* book) {
    books.erase(std::remove(books.begin(), books.end(), book), books.end());
    delete book; // 소각 처리
}

// 훼손된 책 복구 시도
bool Inventory::attemptToRestoreDamagedBook(Book* book, MiniGame* game) {
    ConsoleIO::print("\n훼손된 책 복구 시도 중: " + book->getTitle());

    bool result = game->play(book);

    if (result) {
        ConsoleIO::print("책 복구 성공: " + book->getTitle());
        return true;
    }
    else {
        ConsoleIO::print("책 복구 실패. 책을 폐기합니다.");
        removeBook(book);
        return false;
    }
}
