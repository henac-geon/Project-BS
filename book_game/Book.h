#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Enums.h"

class Book {
protected:
    std::string title;
    std::string description;
    eBookGenre genre;
    eBookMood mood;
    int length;
    bool isDamaged;
    eDamageType damageType;
    eBookCondition condition;

public:
    Book(const std::string& title, const std::string& description, eBookGenre genre, eBookMood mood, int length);
    virtual ~Book() = default;

    virtual void repair() = 0;
    virtual void displayInfo() const = 0;

    std::string getTitle() const;
};

#endif // BOOK_H
