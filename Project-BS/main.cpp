// main.cpp
#include <iostream>
#include <windows.h>
#include "GameManager.h"

int main() {
    // �ܼ��� UTF-8�� �����Ͽ� ��Ʈ ���� ����
    SetConsoleOutputCP(CP_UTF8);
    GameManager game;
    game.run();
    std::cout << "Thank you for playing!\n";
    return 0;
}