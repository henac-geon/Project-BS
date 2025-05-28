#include "TypingGame.h"
#include <iostream>
#include <algorithm>  // std::shuffle -> 배열이나 벡터의 순서를 무작위로 바꿈
#include <random>
#include <chrono>

TypingGame::TypingGame() {
    // 문장 리스트
    all_sentences = {
        "그는 고요히 흐르는 강을 응시했다.",
        "잊히지 않는 기억들이 불쑥 떠올랐다.",
        "빠르게 타이핑하면 실수가 늘어난다.",
        "어딘가 낯설지만 익숙한 풍경이었다.",
        "그녀의 이름조차 흐릿해졌다.",
        "이별의 순간은 항상 갑작스럽다.",
        "“괜찮아”라는 말이 위로가 되지 않았다.",
        "Ctrl과 Shift를 동시에 눌러보세요.",
        "무의미한 반복이 습관이 되었다.",
        "타자 속도보다 정확성이 중요하다."
    };
}

bool TypingGame::play(Book* book) {
    std::vector<std::string> quiz_list = all_sentences;

    // 문장 순서 섞기
    std::shuffle(quiz_list.begin(), quiz_list.end(), std::default_random_engine((unsigned int)std::chrono::system_clock::now().time_since_epoch().count()));

    // 상위 5개만 사용
    quiz_list.resize(5);

    std::string input;

    std::cout << "\n훼손된 문장을 다시 적어보자 (총 5문장)\n";

    for (int i = 0; i < 5; ++i) {
        std::cout << "\n문장 " << (i + 1) << " / 5:\n";
        std::cout << "▶ " << quiz_list[i] << "\n";
        std::cout << "입력: ";
        std::getline(std::cin, input);

        if (input == quiz_list[i]) {
            std::cout << "정확히 입력했습니다!\n";
        }
        else {
            std::cout << "오타가 있습니다. 게임 실패!\n";
            return false;
        }
    }

    std::cout << "\n모든 문장을 성공적으로 입력했습니다! 복원 성공!\n";
    return true;
}
