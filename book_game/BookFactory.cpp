#include "BookFactory.h"
#include <cstdlib>

Book* BookFactory::createRandomBook() {
    int len = rand() % 100 + 50;
    return createBook(eBookGenre::Fantasy, eBookMood::Whimsical, len);
}

Book* BookFactory::createBook(eBookGenre genre, eBookMood mood, int length) {
    switch (genre) {
        case eBookGenre::Fantasy:
            return new FantasyBook("Random Fantasy", "A random fantasy book", length);
        case eBookGenre::SciFi:
            return new ScienceBook("Random SciFi", "A random science book", length);
        default:
            return new FantasyBook("Default Fantasy", "Default", length);
    }
}
