#ifndef TYPINGGAME_H
#define TYPINGGAME_H

#include "MiniGame.h"

class TypingGame : public MiniGame {
public:
    bool play(Book* book) override;
};

#endif // TYPINGGAME_H
