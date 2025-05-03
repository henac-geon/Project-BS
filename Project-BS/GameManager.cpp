#include "GameManager.h"    // GameManager 클래스 정의 포함
#include "AsciiArtRepository.h" // ASCII 아트 저장소 헤더 포함
#include "BookFactory.h"     // 무작위 책 생성용 팩토리 클래스
#include "PenaltySystem.h"   // 페널티 계산 시스템
#include <iostream>           // std::cout 사용
#include <string>             // std::to_string 사용

/**
 * @brief 기본 생성자
 *
 * - day를 1로 초기화하여 1일차부터 시작
 * - gold 및 magicPower는 0으로 초기화
 * - actions 및 actionNames 초기화
 */
GameManager::GameManager()
    : day(1),        // 게임 시작 일수 설정
    gold(0),
    magicPower(0)
{
    initActions();
}

/**
 * @brief 소멸자
 *
 * 동적 할당된 NPC 및 MiniGame 객체를 해제하여 메모리 누수를 방지합니다.
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
 * @brief actions 및 actionNames 초기화
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
 * @brief 하루를 시작하며 메인 메뉴를 UI에 표시
 */
void GameManager::startDay() {
    uiManager.displayMainMenu();
}

/**
 * @brief 사용자 모드 선택 입력 받기
 */
int GameManager::selectMode() {
    return uiManager.getUserInput(
        "Enter choice (1-" + std::to_string(actionNames.size()) + "): "
    );
}

/**
 * @brief 선택된 모드 실행
 * @param idx 메뉴 번호(1-based)
 * @return bool 게임 계속 여부 (false면 종료)
 */
bool GameManager::executeAction(int idx) {
    if (idx < 1 || idx > static_cast<int>(actions.size())) {
        std::cout << "Invalid choice, try again." << std::endl;
        return true;
    }
    return actions[idx - 1]();
}

/**
 * @brief 책 집필 기능
 */
void GameManager::writeBook() {
    std::cout << AsciiArt::writeBookArt() << std::endl;
    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
}

/**
 * @brief NPC 응대 기능
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
 * @brief 인벤토리 조회 기능
 */
void GameManager::viewInventory() {
    uiManager.displayInventory(inventory);
}

/**
 * @brief 일과 요약 기능
 */
void GameManager::dailySummary() {
    uiManager.displayAsciiArt("Day Summary");
}

/**
 * @brief 하루 종료 처리 및 레벨업 체크
 */
void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ++day;
}