#include <iostream>
#include "GameManager.h"

/**
 * @brief 게임 실행 진입점(main)
 *
 * GameManager를 이용해 하루 단위 게임 루프를 실행합니다.
 * 플레이어는 매일 다음 모드를 선택할 수 있습니다:
 *  1. 책 집필
 *  2. NPC 응대
 *  3. 일일 요약
 *  4. 종료
 */
int main() {
    GameManager game;
    bool running = true;

    while (running) {
        // 1) 하루 시작 처리 및 메인 메뉴 출력
        game.startDay();

        // 2) 모드 선택
        std::cout << "Select Mode:" << std::endl;
        std::cout << " 1. Write Book" << std::endl;
        std::cout << " 2. Serve NPCs" << std::endl;
        std::cout << " 3. Daily Summary" << std::endl;
        std::cout << " 4. Exit" << std::endl;
        int choice = game.selectMode();
        // int choice = game.uiManager.getUserInput("Enter choice (1-4): ");

        // 3) 선택에 따른 동작
        switch (choice) {
        case 1:
            game.writeBook();         // 책 집필
            break;
        case 2:
            game.serveNPCs();         // NPC 응대
            break;
        case 3:
            game.dailySummary();      // 일일 요약
            break;
        case 4:
            running = false;          // 종료
            continue;
        default:
            std::cout << "Invalid choice, try again." << std::endl;
            continue;
        }

        // 4) 하루 종료 처리 및 레벨업 체크
        game.endDay();
    }

    std::cout << "Thank you for playing!" << std::endl;
    return 0;
}