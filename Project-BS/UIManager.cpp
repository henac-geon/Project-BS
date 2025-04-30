#include "UIManager.h"   // UIManager Ŭ���� ���� ��� ����
#include <iostream>        // std::cout, std::cin ����� ���� iostream ���

/**
 * @brief ���� �޴��� �ֿܼ� ���
 *
 * "=== Main Menu ===" ����� ����Ͽ�
 * �÷��̾�� �ֿ� ��� ���� �������̽��� �����մϴ�.
 */
void UIManager::displayMainMenu() {
    std::cout << "=== Main Menu ===" << std::endl;
}

/**
 * @brief �κ��丮 å ����� �ֿܼ� ���
 *
 * @param inventory  ����� Inventory ��ü
 *
 * inventory.getBooks()�� å ����� ������
 * �ε����� å ������ �� �پ� ����մϴ�.
 */
void UIManager::displayInventory(const Inventory& inventory) {
    std::cout << "Inventory:" << std::endl;
    // �� å�� �ε����� ������ ����
    for (size_t i = 0; i < inventory.getBooks().size(); ++i) {
        std::cout << i << ": "
            << inventory.getBooks()[i]->getTitle()
            << std::endl;
    }
}

/**
 * @brief NPC�� ��ȣ�ۿ��� ������ �� �޽��� ���
 *
 * @param npc  ��ȣ�ۿ��� NPC ������
 *
 * ������ �ȳ� �޽����� ����ϸ�,
 * ���� NPC �̸�, ��ȣ ���� ���� �߰��� ǥ���� �� �ֽ��ϴ�.
 */
void UIManager::displayNPCInteraction(NPC* npc) {
    std::cout << "Interacting with NPC" << std::endl;
}

/**
 * @brief å �� ������ �ֿܼ� ���
 *
 * @param book  ������ ǥ���� Book ������
 *
 * Book::displayInfo()�� ȣ���Ͽ�
 * å�� ����, ����, �帣, ������, ���� ���� ����մϴ�.
 */
void UIManager::displayBookDetail(const Book* book) {
    book->displayInfo();
}

/**
 * @brief å ����(Condition)�� �ֿܼ� ���
 *
 * @param bc  eBookCondition ������ ��
 *
 * ���������� ��ȯ�Ͽ� ���� ���� ǥ���ϸ�,
 * enum-to-string ������ �����Ͽ� ����� ���� �ֽ��ϴ�.
 */
void UIManager::displayBookCondition(eBookCondition bc) {
    std::cout << "Condition: "
        << static_cast<int>(bc)
        << std::endl;
}

/**
 * @brief ��� �� ���� ���Ƽ ������ ���
 *
 * @param gold  �����Ǵ� ��� ��
 * @param mp    �����Ǵ� ���� ��
 *
 * NPC �Ҹ��� �� ���Ƽ ������ ����ڿ��� �˷��ݴϴ�.
 */
void UIManager::displayPenaltyInfo(int gold, int mp) {
    std::cout << "Gold Penalty: " << gold
        << ", MP Penalty: " << mp
        << std::endl;
}

/**
 * @brief ASCII ��Ʈ�� �ֿܼ� ���
 *
 * @param art  ����� ASCII ��Ʈ ���ڿ�
 *
 * ���� ����̳� Ư�� �̺�Ʈ�� �ð��� ȿ���� ���� ����մϴ�.
 */
void UIManager::displayAsciiArt(const std::string& art) {
    std::cout << art << std::endl;
}

/**
 * @brief ������ ���� �޽����� �ֿܼ� ���
 *
 * @param level  ���ο� ���� ��
 *
 * ������ �� "Level Up! New Level: X" ���·� ǥ���մϴ�.
 */
void UIManager::displayLevelUpMessage(int level) {
    std::cout << "Level Up! New Level: " << level << std::endl;
}

/**
 * @brief ����ڷκ��� ���� �Է��� �޴� �Լ�
 *
 * @param prompt  �Է� ��û �޽���
 * @return int    �Էµ� ���� ��
 *
 * prompt �޽����� ����� �� std::cin���� �Է��� �ް�,
 * ���� ��ȯ�մϴ�. �Է� ���� ������ ���� ���� �ʿ��մϴ�.
 */
int UIManager::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    int input;
    std::cin >> input;
    return input;
}

/**
 * @brief ��� ���� ȭ���� �ֿܼ� ���
 *
 * �÷��̾ ������ �� �ִ� ���(����, NPC ����, �̴ϰ��� ��)�� �ȳ��մϴ�.
 */
void UIManager::displayModeSelection() {
    std::cout << "Select Mode:" << std::endl;
}

/**
 * @brief �̴ϰ��� ����� �ֿܼ� ���
 *
 * @param result  ���� ��� ���ڿ� ("Win" �Ǵ� "Lose" ��)
 *
 * �̴ϰ��� ���� �� ����� ����ڿ��� �˷��ݴϴ�.
 */
void UIManager::displayMiniGameResult(const std::string& result) {
    std::cout << "MiniGame Result: " << result << std::endl;
}
