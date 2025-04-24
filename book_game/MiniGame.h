#ifndef MINIGAME_H
#define MINIGAME_H

#include "Book.h"

class MiniGame {
public:
    virtual ~MiniGame() = default;
    virtual bool play(Book* book) = 0;
};

#endif // MINIGAME_H
