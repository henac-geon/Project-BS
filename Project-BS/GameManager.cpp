#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "BookFactory.h"
#include "PenaltySystem.h"
#include <iostream>

GameManager::GameManager()
    : day(1), gold(0), magicPower(0) {

}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
}

void GameManager::run() {
    std::string command;
    std::cout << "������ �����Ϸ��� '����'�� �Է��ϼ���: ";
    std::cin >> command;
    if (command != "����") return;

    while (true) {
        startDay();
        performWritingPhase();
        performNPCPhase();
        performSettlementPhase();
        endDay();

        std::cout << "���� ���� �����Ͻðڽ��ϱ�? (y/n): ";
        std::cin >> command;
        if (command != "y" && command != "Y") break;
    }
}

void GameManager::startDay() {
    uiManager.clearScreen();
    std::cout << AsciiArt::getWelcomeArt() << std::endl;
    std::cout << "\n Day " << day << " ����!\n";
}

void GameManager::performWritingPhase() {
    int numBooks = rand() % 3 + 1;
    std::cout << "\n ���� ������ å ��: " << numBooks << std::endl;

    for (int i = 0; i < numBooks; ++i) {
        auto book = BookFactory::createRandomBook();
        inventory.addBook(book);
        std::cout << "å ��ϵ�: " << book->getTitle() << std::endl;
    }

    std::string ans;
    std::cout << "�κ��丮�� Ȯ���Ͻðڽ��ϱ�? (y/n): ";
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::performNPCPhase() {
    uiManager.clearScreen();
    std::cout << AsciiArt::getWelcomeArt() << std::endl; // NPC ȭ������ ����
    int numNPC = rand() % 3 + 1;
    std::cout << "\n ���� ������ NPC ��: " << numNPC << std::endl;

    for (int i = 0; i < numNPC; ++i) {
        NPC* npc = new RandomNPC();
        npcs.push_back(npc);

		uiManager.displayNPCInteraction(npc); // NPC�� ��ȣ�ۿ� ȭ�� ����

		// ���� NPC�� ��û�� Ȯ��
		// å�� �ݳ��ϴ� ������ ��û�ϴ� �������� ���� �ٸ��� ����

		// TODO: å�� ��û�ϴ� ���� NPC�� ��û�� ���� �ٸ��� ����
		// ���� ���, Ư�� �帣�� �����⸦ ��ȣ�ϴ� NPC�� ���� �� ����
		// ���� �κ��丮�� ���� ���� ��û�� ���� ����
        // �Ű� ���� ���� �ؾ� ��
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

    std::string ans;
    std::cout << "�κ��丮�� Ȯ���Ͻðڽ��ϱ�? (y/n): ";
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::performSettlementPhase() {
    std::cout << "\n ���� �ܰ� ����!\n";
    for (auto& book : inventory.getBooks()) {
        if (book->getCondition() == eBookCondition::Damaged) {
            book->repair();
            std::cout << book->getTitle() << " ���� �Ϸ�!" << std::endl;
        }
    }
    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
    std::cout << "������ å ���� �Ϸ�: " << book->getTitle() << std::endl;

    std::string ans;
    std::cout << "�κ��丮�� Ȯ���Ͻðڽ��ϱ�? (y/n): ";
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ++day;
}
