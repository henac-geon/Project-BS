#include "ConsoleIO.h"
#include "GameManager.h"

int main() {
    //std::cout << "Welcome to the Game!" << std::endl;
    ConsoleIO::init();  // 콘솔 인코딩 및 로케일 초기화

    GameManager game;
    game.run();

    ConsoleIO::println("Thank you for playing!");

    return 0;
}
