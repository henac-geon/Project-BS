#include "ConsolePrinter.h"
#include "GameManager.h"

/**
 * @brief ���α׷� ������
 *
 * �ܼ� ��� ȯ���� �ʱ�ȭ�� �� GameManager�� �����մϴ�.
 */
int main() {
    ConsolePrinter::init();  // �ܼ� ���ڵ� �� ������ �ʱ�ȭ

    GameManager game;
    game.run();

    ConsolePrinter::println("Thank you for playing!");
    return 0;
}