// main.cpp
#include "DictationGame.h"

int main() {
    // 백스페이스 허용 여부 설정(false면 백스페이스가 작동하지 않음)
    DictationGame game(false);

    // 5개의 라운드를 실행(실제 문장 개수가 1개라면, 한 번만 돌고 종료됨)
    game.runSession(5);

    return 0;
}
