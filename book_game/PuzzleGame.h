#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include "MiniGame.h"

class PuzzleGame : public MiniGame {
public:
    bool play(Book* book) override;
};

#endif // PUZZLEGAME_H
