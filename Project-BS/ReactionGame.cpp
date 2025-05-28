#include "ReactionGame.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

bool ReactionGame::play(Book* book) {
    std::cout << "훼손된 책 복구 중... 집중하세요.\n";
    std::cout << "준비 중...\n";

    // 랜덤 대기 시간 (2~4초)
    int wait_ms = rand() % 2001 + 2000;
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));

    std::cout << "\n지금! → Enter를 누르세요!\n";

    auto start = std::chrono::high_resolution_clock::now();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 엔터 대기
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    double elapsed = diff.count();

    std::cout << "반응 속도: " << elapsed << "초\n";

    if (elapsed < 0.2) {    // 0.2초 보다 빠른 경우
        std::cout << "너무 빠릅니다! 조급했어요.\n";
        return false;
    }
    else if (elapsed <= 0.35) {  // 0.2초 ~ 0.35초 사이
        std::cout << "복구 성공! 빠르고 정확했습니다.\n";
        return true;
    }
    else {  // 0.35초 보다 느린 경우
        std::cout << "늦었습니다. 책 복구에 실패했습니다.\n";
        return false;
    }
}
