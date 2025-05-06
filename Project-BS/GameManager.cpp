#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "BookFactory.h"
#include "PenaltySystem.h"
#include "RandomNPC.h"
#include "ConsolePrinter.h"
#include <string> 

/**
 * @brief 기본 생성자
 *
 * - day를 1로 초기화하여 1일차부터 시작
 * - gold 및 magicPower는 0으로 초기화
 * - actions 및 actionNames 초기화
 */
GameManager::GameManager()
    : day(1), gold(0), magicPower(0) {

}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
}

void GameManager::run() {
    std::string command;
    ConsolePrinter::print("게임을 시작하려면 '시작'을 입력하세요: ");
    std::cin >> command;
    if (command != "시작") return;

    while (true) {
        startDay();
        performWritingPhase();
        performNPCPhase();
        performSettlementPhase();
        endDay();

        ConsolePrinter::print("다음 날로 진행하시겠습니까? (y/n): ");
        std::cin >> command;
        if (command != "y" && command != "Y") break;
    }
}

void GameManager::startDay() {
    uiManager.clearScreen();
    ConsolePrinter::println(AsciiArt::getWelcomeArt());
    ConsolePrinter::println("\n Day " + std::to_string(day) + " 시작!\n");
}

void GameManager::performWritingPhase() {
    int numBooks = rand() % 3 + 1;
    ConsolePrinter::println("\n 오늘 집필할 책 수: " + std::to_string(numBooks));

    for (int i = 0; i < numBooks; ++i) {
        auto book = BookFactory::createRandomBook();
        inventory.addBook(book);
        ConsolePrinter::println("책 등록됨: " + book->getTitle());
    }

    std::string ans;
    ConsolePrinter::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::performNPCPhase() {
    uiManager.clearScreen();
    ConsolePrinter::println(AsciiArt::getWelcomeArt()); // NPC 화면으로 설정

    int numNPC = rand() % 3 + 1;
    ConsolePrinter::println("\n 오늘 응대할 NPC 수: " + std::to_string(numNPC));

    for (int i = 0; i < numNPC; ++i) {
        NPC* npc = RandomNPC::create();
        npcs.push_back(npc);

		uiManager.displayNPCInteraction(npc); // NPC와 상호작용 화면 설정

		// 먼저 NPC의 요청을 확인
		// 책을 반납하는 것인지 요청하는 것인지에 따라 다르게 구현

		// TODO: 책을 요청하는 것은 NPC의 요청에 따라 다르게 구현
		// 예를 들어, 특정 장르나 분위기를 선호하는 NPC가 있을 수 있음
		// 따라서 인벤토리에 없는 택을 요청할 수도 있음
        // 매개 변수 삭제 해야 함
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
    ConsolePrinter::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::performSettlementPhase() {
    ConsolePrinter::println("\n 정산 단계 시작!\n");

    for (auto& book : inventory.getBooks()) {
        if (book->getCondition() == eBookCondition::Damaged) {
            book->repair();
            ConsolePrinter::println(book->getTitle() + " 복원 완료!");
        }
    }

    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
    ConsolePrinter::println("마지막 책 집필 완료: " + book->getTitle());

    std::string ans;
    ConsolePrinter::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ++day;
}
