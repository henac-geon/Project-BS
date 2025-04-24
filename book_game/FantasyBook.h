#ifndef FANTASYBOOK_H
#define FANTASYBOOK_H

#include "Book.h"
#include <iostream>

class FantasyBook : public Book {
public:
    FantasyBook(const std::string& title, const std::string& description, int length);
    void repair() override;
    void displayInfo() const override;
};

#endif // FANTASYBOOK_H
