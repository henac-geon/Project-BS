#include "Inventory.h"
#include <algorithm>


void Inventory::addBook(Book* book) {
    books.push_back(book);
}


bool Inventory::safeRemoveBook(int index) {
    if (index >= 0 && index < static_cast<int>(books.size())) {
        books.erase(books.begin() + index);
        return true;
    }
    return false;
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
