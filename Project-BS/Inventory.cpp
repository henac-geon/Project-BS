#include "Inventory.h"
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
    std::cout << "\n📖 훼손된 책 복구 시도 중: " << book->getTitle() << "\n";
    bool result = game->play(book);

    if (result) {
        std::cout << "✅ 책 복구 성공: " << book->getTitle() << "\n";
        return true;
    }
    else {
        std::cout << "❌ 책 복구 실패. 책을 폐기합니다.\n";
        removeBook(book);
        return false;
    }
}
