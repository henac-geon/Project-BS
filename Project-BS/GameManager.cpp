#include "GameManager.h"    // GameManager Ŭ���� ���� ����
#include "BookFactory.h"     // ������ å ������ ���丮 Ŭ����
#include "PenaltySystem.h"   // ���Ƽ ��� �ý���

/**
 * @brief �⺻ ������
 *
 * - day�� 1�� �ʱ�ȭ�Ͽ� 1�������� ����
 * - gold �� magicPower�� 0���� �ʱ�ȭ
 * - �ʿ��� ��� NPC �� �̴ϰ��� ��ü�� �����Ͽ� ��Ͽ� �߰�
 */
GameManager::GameManager()
    : day(1),        // ���� ���� �ϼ� ����
    gold(0),
    magicPower(0)
{
    // TODO: NPC* �� MiniGame* ��� �ʱ�ȭ ���� �߰� ����
}

/**
 * @brief �Ҹ���
 *
 * ���� �Ҵ�� NPC �� MiniGame ��ü�� ��ȸ�ϸ� �����Ͽ�
 * �޸� ������ �����մϴ�.
 */
GameManager::~GameManager() {
    // NPC ��ü ����
    for (auto npc : npcs) {
        delete npc;
    }
    // MiniGame ��ü ����
    for (auto mg : miniGames) {
        delete mg;
    }
}


int GameManager::selectMode() {
    uiManager.displayModeSelection();  // "Select Mode:" ���
    // ������Ʈ�� �Ѱܼ� �Է¹���
    return uiManager.getUserInput("Enter choice (1-4): ");
}

/**
 * @brief �Ϸ縦 �����ϸ� ���� �޴��� UI�� ǥ��
 *
 * uiManager�� ����Ͽ� �÷��̾�� ���� �� �ൿ ���� UI�� ����մϴ�.
 */
void GameManager::startDay() {
    uiManager.displayMainMenu();
}

/**
 * @brief å�� �����Ͽ� �κ��丮�� �߰�
 *
 * BookFactory�� ���� ������ å ��ü�� �����ϰ�,
 * ������ Book �����͸� Inventory�� �����մϴ�.
 */
void GameManager::writeBook() {
    auto book = BookFactory::createRandomBook();  // ���� å ����
    inventory.addBook(book);                      // �κ��丮�� �߰�
}

/**
 * @brief NPC�鿡�� å�� �����ϰ� �� �� ���Ƽ ó��
 *
 * npcs ���͸� ��ȸ�ϸ鼭:
 * 1) NPC�� ��û�ϴ� å�� inventory���� ����
 * 2) rateBook ȣ��� ���� ���� ����
 * 3) �Ҹ��� �� PenaltySystem�� ���� ��� �� ���� ���Ƽ ���
 * 4) uiManager�� ���Ƽ ������ ���
 * 5) scoreSystem.updateScore ȣ��� ���� ����
 */
void GameManager::serveNPCs() {
    for (auto npc : npcs) {
        // NPC�� �а� ���� å�� ����
        auto book = npc->requestBook(inventory.getBooks());
        bool satisfied = false;
        if (book) {
            // å ��
            satisfied = npc->rateBook(book);
            if (!satisfied) {
                // ���Ƽ ��� �� UI ���
                int gp = PenaltySystem::calculateGoldPenalty(*book);
                int mp = PenaltySystem::calculateMagicPenalty(*book);
                uiManager.displayPenaltyInfo(gp, mp);
            }
        }
        // ���� �ý��ۿ� ���� ���� ����
        scoreSystem.updateScore(satisfied);
    }
}

/**
 * @brief �Ϸ� �ϰ� ����� UI�� ���
 *
 * �Ϸ絿���� �ֿ� �̺�Ʈ�� ��踦 ASCII ��Ʈ ���·� ǥ���մϴ�.
 */
void GameManager::dailySummary() {
    uiManager.displayAsciiArt("Day Summary");
}

/**
 * @brief �Ϸ� ���� ó��
 *
 * - ������ ���� Ȯ�� �� UI �޽��� ���
 * - ���� �� �غ� ���� day�� ������ŵ�ϴ�.
 */
void GameManager::endDay() {
    // ������ �߻� �� �޽��� ���
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    // ���� ���� ����
    day++;
}