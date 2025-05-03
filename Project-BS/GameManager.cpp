#include "GameManager.h"    // GameManager Ŭ���� ���� ����
#include "AsciiArtRepository.h" // ASCII ��Ʈ ����� ��� ����
#include "BookFactory.h"     // ������ å ������ ���丮 Ŭ����
#include "PenaltySystem.h"   // ���Ƽ ��� �ý���
#include <iostream>           // std::cout ���
#include <string>             // std::to_string ���

/**
 * @brief �⺻ ������
 *
 * - day�� 1�� �ʱ�ȭ�Ͽ� 1�������� ����
 * - gold �� magicPower�� 0���� �ʱ�ȭ
 * - actions �� actionNames �ʱ�ȭ
 */
GameManager::GameManager()
    : day(1),        // ���� ���� �ϼ� ����
    gold(0),
    magicPower(0)
{
    initActions();
}

/**
 * @brief �Ҹ���
 *
 * ���� �Ҵ�� NPC �� MiniGame ��ü�� �����Ͽ� �޸� ������ �����մϴ�.
 */
GameManager::~GameManager() {
    for (auto npc : npcs) {
        delete npc;
    }
    for (auto mg : miniGames) {
        delete mg;
    }
}

/**
 * @brief actions �� actionNames �ʱ�ȭ
 */
void GameManager::initActions() {
    actionNames = {
        "Write Book",
        "Serve NPCs",
        "View Inventory",
        "Daily Summary",
        "Exit"
    };

    actions = {
        [this]() { writeBook();     return true; },
        [this]() { serveNPCs();     return true; },
        [this]() { viewInventory(); return true; },
        [this]() { dailySummary();  return true; },
        [this]() { return false;             }
    };
    std::cout << AsciiArt::getWelcomeArt() << std::endl;
}

/**
 * @brief �Ϸ縦 �����ϸ� ���� �޴��� UI�� ǥ��
 */
void GameManager::startDay() {
    uiManager.displayMainMenu();
}

/**
 * @brief ����� ��� ���� �Է� �ޱ�
 */
int GameManager::selectMode() {
    return uiManager.getUserInput(
        "Enter choice (1-" + std::to_string(actionNames.size()) + "): "
    );
}

/**
 * @brief ���õ� ��� ����
 * @param idx �޴� ��ȣ(1-based)
 * @return bool ���� ��� ���� (false�� ����)
 */
bool GameManager::executeAction(int idx) {
    if (idx < 1 || idx > static_cast<int>(actions.size())) {
        std::cout << "Invalid choice, try again." << std::endl;
        return true;
    }
    return actions[idx - 1]();
}

/**
 * @brief å ���� ���
 */
void GameManager::writeBook() {
    std::cout << AsciiArt::writeBookArt() << std::endl;
    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
}

/**
 * @brief NPC ���� ���
 */
void GameManager::serveNPCs() {
    for (auto npc : npcs) {
        auto book = npc->requestBook(inventory.getBooks());
        bool satisfied = false;
        if (book) {
            satisfied = npc->rateBook(book);
            if (!satisfied) {
                int gp = PenaltySystem::calculateGoldPenalty(*book);
                int mp = PenaltySystem::calculateMagicPenalty(*book);
                uiManager.displayPenaltyInfo(gp, mp);
            }
        }
        scoreSystem.updateScore(satisfied);
    }
}

/**
 * @brief �κ��丮 ��ȸ ���
 */
void GameManager::viewInventory() {
    uiManager.displayInventory(inventory);
}

/**
 * @brief �ϰ� ��� ���
 */
void GameManager::dailySummary() {
    uiManager.displayAsciiArt("Day Summary");
}

/**
 * @brief �Ϸ� ���� ó�� �� ������ üũ
 */
void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ++day;
}