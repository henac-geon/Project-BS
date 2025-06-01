#pragma once
#include "MiniGame.h"
#include <vector>
#include <string>

class TypingGame : public MiniGame {
private:
    std::vector<std::string> all_sentences;  // 전체 문장 저장용

public:
    TypingGame();
    bool play(Book* book) override;  // Book은 무시하고 게임만 실행
};
