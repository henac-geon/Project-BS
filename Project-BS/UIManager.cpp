#include "UIManager.h"   // UIManager Ŭ���� ���� ��� ����
#include "AsciiArtRepository.h" // ASCII ��Ʈ ����� ��� ����
#include <iostream>        // std::cout, std::cin ����� ���� iostream ���
#include <cstdlib>

/**
 * @brief ���� �޴��� �ֿܼ� ���
 *
 * "=== Main Menu ===" ����� ����Ͽ�
 * �÷��̾�� �ֿ� ��� ���� �������̽��� �����մϴ�.
 */
void UIManager::displayMainMenu() {
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. ���� ���" << std::endl;
    std::cout << "2. NPC ����" << std::endl;
    std::cout << "3. �̴ϰ���" << std::endl;
    std::cout << "4. �κ��丮 Ȯ��" << std::endl;
    std::cout << "5. ����" << std::endl;
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
    std::cout << "\n �κ��丮 ���:" << std::endl;
    const auto& books = inventory.getBooks();
    if (books.empty()) {
        std::cout << " - ��ϵ� å�� �����ϴ�." << std::endl;
        return;
    }
    for (size_t i = 0; i < books.size(); ++i) {
        std::cout << i << ": " << books[i]->getTitle() << std::endl;
    }
	//TODO: å �� ���� ��� ��� �߰� ����
	//TODO: �κ��丮 ������ ��� �߰� ����
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
    std::cout << "\n NPC���� ��ȣ�ۿ��� �����մϴ�..." << std::endl;
    if (npc) {
        std::cout << " - �̸�: "; // << npc->getName() << std::endl;
        // �ʿ�� ��ȣ �帣 � ��� ����
    }
    //TODO: ��ȣ�ۿ� ��� �߰� ����
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
    if (book) {
        std::cout << "\n å �� ����:" << std::endl;
        book->displayInfo();
    }
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
    std::cout << "����: ";
    switch (bc) {
    case eBookCondition::Perfect: std::cout << "�ֻ�"; break;
    case eBookCondition::Worn: std::cout << "��ȣ"; break;
    case eBookCondition::Damaged: std::cout << "�ణ�� �ջ��� ����"; break;
    case eBookCondition::Destroyed: std::cout << "�Ѽ��� ���� �� ���� �ʿ�"; break;
    default: std::cout << "�� �� ����"; break;
    }
    std::cout << std::endl;
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
    std::cout << "\n ���Ƽ �߻�!" << std::endl;
    std::cout << " - ��� ����: " << gold << std::endl;
    std::cout << " - ���� ����: " << mp << std::endl;
}

/**
 * @brief ASCII ��Ʈ�� �ֿܼ� ���
 *
 * @param art  ����� ASCII ��Ʈ ���ڿ�
 *
 * ���� ����̳� Ư�� �̺�Ʈ�� �ð��� ȿ���� ���� ����մϴ�.
 */
void UIManager::displayAsciiArt(const std::string& art) {
    std::cout << "\n" << art << std::endl;
}

/**
 * @brief ������ ���� �޽����� �ֿܼ� ���
 *
 * @param level  ���ο� ���� ��
 *
 * ������ �� "Level Up! New Level: X" ���·� ǥ���մϴ�.
 */
void UIManager::displayLevelUpMessage(int level) {
    std::cout << AsciiArt::getLevelUpArt() << std::endl;
    std::cout << "\n ���� ��! ���ο� ����: " << level << std::endl;
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
    // TODO: ���� ó�� �� ���Է� ���� ���� ����
    return input;
}

/**
 * @brief ��� ���� ȭ���� �ֿܼ� ���
 *
 * �÷��̾ ������ �� �ִ� ���(����, NPC ����, �̴ϰ��� ��)�� �ȳ��մϴ�.
 */
void UIManager::displayModeSelection() {
    std::cout << "\n ��带 �����ϼ���:" << std::endl;
    std::cout << "1. ���� ���" << std::endl;
    std::cout << "2. NPC ����" << std::endl;
    std::cout << "3. �̴ϰ���" << std::endl;
    std::cout << "4. ���ư���" << std::endl;
}
/**
 * @brief �̴ϰ��� ����� �ֿܼ� ���
 *
 * @param result  ���� ��� ���ڿ� ("Win" �Ǵ� "Lose" ��)
 *
 * �̴ϰ��� ���� �� ����� ����ڿ��� �˷��ݴϴ�.
 */
void UIManager::displayMiniGameResult(const std::string& result) {
    std::cout << "\n �̴ϰ��� ���: " << result << std::endl;
}

void UIManager::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
