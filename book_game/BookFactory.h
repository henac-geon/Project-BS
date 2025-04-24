#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "Book.h"
#include "FantasyBook.h"
#include "ScienceBook.h"

class BookFactory {
public:
    static Book* createRandomBook();
    static Book* createBook(eBookGenre genre, eBookMood mood, int length);
};

#endif // BOOKFACTORY_H
