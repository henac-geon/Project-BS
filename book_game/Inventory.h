#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Book.h"

class Inventory {
private:
    std::vector<Book*> books;
public:
    void addBook(Book* book);
    void removeBook(int index);
    Book* findBook(const std::string& title) const;
    const std::vector<Book*>& getBooks() const;
};

#endif // INVENTORY_H
