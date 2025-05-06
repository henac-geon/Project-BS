// main.cpp
#include <iostream>
#include <windows.h>
#include "GameManager.h"

int main() {
    // 콘솔을 UTF-8로 설정하여 아트 깨짐 방지
    SetConsoleOutputCP(CP_UTF8);
    GameManager game;
    game.run();
    std::cout << "Thank you for playing!\n";
    return 0;
}