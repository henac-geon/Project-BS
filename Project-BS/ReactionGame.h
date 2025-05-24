#pragma once
#include "MiniGame.h"

// 반응속도 미니게임은 Book을 사용하지 않음
class ReactionGame : public MiniGame {
public:
    bool play(Book* book) override;
};
