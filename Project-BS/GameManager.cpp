#include "GameManager.h"    // GameManager 클래스 정의 포함
#include "BookFactory.h"     // 무작위 책 생성용 팩토리 클래스
#include "PenaltySystem.h"   // 페널티 계산 시스템

/**
 * @brief 기본 생성자
 *
 * - day를 1로 초기화하여 1일차부터 시작
 * - gold 및 magicPower는 0으로 초기화
 * - 필요한 경우 NPC 및 미니게임 객체를 생성하여 목록에 추가
 */
GameManager::GameManager()
    : day(1),        // 게임 시작 일수 설정
    gold(0),
    magicPower(0)
{
    // TODO: NPC* 및 MiniGame* 목록 초기화 로직 추가 가능
}

/**
 * @brief 소멸자
 *
 * 동적 할당된 NPC 및 MiniGame 객체를 순회하며 해제하여
 * 메모리 누수를 방지합니다.
 */
GameManager::~GameManager() {
    // NPC 객체 해제
    for (auto npc : npcs) {
        delete npc;
    }
    // MiniGame 객체 해제
    for (auto mg : miniGames) {
        delete mg;
    }
}


int GameManager::selectMode() {
    uiManager.displayModeSelection();  // "Select Mode:" 출력
    // 프롬프트를 넘겨서 입력받음
    return uiManager.getUserInput("Enter choice (1-4): ");
}

/**
 * @brief 하루를 시작하며 메인 메뉴를 UI에 표시
 *
 * uiManager를 사용하여 플레이어에게 오늘 할 행동 선택 UI를 출력합니다.
 */
void GameManager::startDay() {
    uiManager.displayMainMenu();
}

/**
 * @brief 책을 집필하여 인벤토리에 추가
 *
 * BookFactory를 통해 무작위 책 객체를 생성하고,
 * 생성된 Book 포인터를 Inventory에 보관합니다.
 */
void GameManager::writeBook() {
    auto book = BookFactory::createRandomBook();  // 랜덤 책 생성
    inventory.addBook(book);                      // 인벤토리에 추가
}

/**
 * @brief NPC들에게 책을 제공하고 평가 및 페널티 처리
 *
 * npcs 벡터를 순회하면서:
 * 1) NPC가 요청하는 책을 inventory에서 전달
 * 2) rateBook 호출로 만족 여부 판정
 * 3) 불만족 시 PenaltySystem을 통해 골드 및 마력 페널티 계산
 * 4) uiManager로 페널티 정보를 출력
 * 5) scoreSystem.updateScore 호출로 점수 갱신
 */
void GameManager::serveNPCs() {
    for (auto npc : npcs) {
        // NPC가 읽고 싶은 책을 선택
        auto book = npc->requestBook(inventory.getBooks());
        bool satisfied = false;
        if (book) {
            // 책 평가
            satisfied = npc->rateBook(book);
            if (!satisfied) {
                // 페널티 계산 및 UI 출력
                int gp = PenaltySystem::calculateGoldPenalty(*book);
                int mp = PenaltySystem::calculateMagicPenalty(*book);
                uiManager.displayPenaltyInfo(gp, mp);
            }
        }
        // 점수 시스템에 만족 여부 전달
        scoreSystem.updateScore(satisfied);
    }
}

/**
 * @brief 하루 일과 요약을 UI에 출력
 *
 * 하루동안의 주요 이벤트나 통계를 ASCII 아트 형태로 표시합니다.
 */
void GameManager::dailySummary() {
    uiManager.displayAsciiArt("Day Summary");
}

/**
 * @brief 하루 종료 처리
 *
 * - 레벨업 조건 확인 및 UI 메시지 출력
 * - 다음 날 준비를 위해 day를 증가시킵니다.
 */
void GameManager::endDay() {
    // 레벨업 발생 시 메시지 출력
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    // 다음 날로 진행
    day++;
}