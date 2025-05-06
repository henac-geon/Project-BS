#include "ConsolePrinter.h"
#include "GameManager.h"

/**
 * @brief 프로그램 진입점
 *
 * 콘솔 출력 환경을 초기화한 후 GameManager를 실행합니다.
 */
int main() {
    ConsolePrinter::init();  // 콘솔 인코딩 및 로케일 초기화

    GameManager game;
    game.run();

    ConsolePrinter::println("Thank you for playing!");
    return 0;
}