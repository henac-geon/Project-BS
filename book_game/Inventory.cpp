#include "Inventory.h"
#include <algorithm>

void Inventory::addBook(Book* book) {
    books.push_back(book);
}

void Inventory::removeBook(int index) {
    if (index >= 0 && index < (int)books.size()) {
        books.erase(books.begin() + index);
    }
}

Book* Inventory::findBook(const std::string& title) const {
    auto it = std::find_if(books.begin(), books.end(), [&](Book* b){
        return b->getTitle() == title;
    });
    if (it != books.end()) return *it;
    return nullptr;
}

const std::vector<Book*>& Inventory::getBooks() const {
    return books;
}
