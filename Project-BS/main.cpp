#include <iostream>
#include "GameManager.h"

/**
 * @brief ���� ���� ������(main)
 *
 * GameManager�� �̿��� �Ϸ� ���� ���� ������ �����մϴ�.
 * �÷��̾�� ���� ���� ��带 ������ �� �ֽ��ϴ�:
 *  1. å ����
 *  2. NPC ����
 *  3. ���� ���
 *  4. ����
 */
int main() {
    GameManager game;
    bool running = true;

    while (running) {
        // 1) �Ϸ� ���� ó�� �� ���� �޴� ���
        game.startDay();

        // 2) ��� ����
        std::cout << "Select Mode:" << std::endl;
        std::cout << " 1. Write Book" << std::endl;
        std::cout << " 2. Serve NPCs" << std::endl;
        std::cout << " 3. Daily Summary" << std::endl;
        std::cout << " 4. Exit" << std::endl;
        int choice = game.selectMode();
        // int choice = game.uiManager.getUserInput("Enter choice (1-4): ");

        // 3) ���ÿ� ���� ����
        switch (choice) {
        case 1:
            game.writeBook();         // å ����
            break;
        case 2:
            game.serveNPCs();         // NPC ����
            break;
        case 3:
            game.dailySummary();      // ���� ���
            break;
        case 4:
            running = false;          // ����
            continue;
        default:
            std::cout << "Invalid choice, try again." << std::endl;
            continue;
        }

        // 4) �Ϸ� ���� ó�� �� ������ üũ
        game.endDay();
    }

    std::cout << "Thank you for playing!" << std::endl;
    return 0;
}