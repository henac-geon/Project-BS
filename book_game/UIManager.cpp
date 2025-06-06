#include "UIManager.h"   // UIManager 클래스 정의 헤더 포함
#include <iostream>        // std::cout, std::cin 사용을 위한 iostream 헤더

/**
 * @brief 메인 메뉴를 콘솔에 출력
 *
 * "=== Main Menu ===" 헤더를 사용하여
 * 플레이어에게 주요 명령 선택 인터페이스를 제공합니다.
 */
void UIManager::displayMainMenu() {
    std::cout << "=== Main Menu ===" << std::endl;
}

/**
 * @brief 인벤토리 책 목록을 콘솔에 출력
 *
 * @param inventory  출력할 Inventory 객체
 *
 * inventory.getBooks()로 책 목록을 가져와
 * 인덱스와 책 제목을 한 줄씩 출력합니다.
 */
void UIManager::displayInventory(const Inventory& inventory) {
    std::cout << "Inventory:" << std::endl;
    // 각 책의 인덱스와 제목을 나열
    for (size_t i = 0; i < inventory.getBooks().size(); ++i) {
        std::cout << i << ": "
                  << inventory.getBooks()[i]->getTitle()
                  << std::endl;
    }
}

/**
 * @brief NPC와 상호작용을 시작할 때 메시지 출력
 *
 * @param npc  상호작용할 NPC 포인터
 *
 * 간단한 안내 메시지를 출력하며,
 * 추후 NPC 이름, 선호 정보 등을 추가로 표시할 수 있습니다.
 */
void UIManager::displayNPCInteraction(NPC* npc) {
    std::cout << "Interacting with NPC" << std::endl;
}

/**
 * @brief 책 상세 정보를 콘솔에 출력
 *
 * @param book  정보를 표시할 Book 포인터
 *
 * Book::displayInfo()를 호출하여
 * 책의 제목, 설명, 장르, 분위기, 상태 등을 출력합니다.
 */
void UIManager::displayBookDetail(const Book* book) {
    book->displayInfo();
}

/**
 * @brief 책 상태(Condition)를 콘솔에 출력
 *
 * @param bc  eBookCondition 열거형 값
 *
 * 정수형으로 변환하여 상태 값을 표시하며,
 * enum-to-string 매핑을 구현하여 출력할 수도 있습니다.
 */
void UIManager::displayBookCondition(eBookCondition bc) {
    std::cout << "Condition: "
              << static_cast<int>(bc)
              << std::endl;
}

/**
 * @brief 골드 및 마력 페널티 정보를 출력
 *
 * @param gold  차감되는 골드 양
 * @param mp    차감되는 마력 양
 *
 * NPC 불만족 시 페널티 정보를 사용자에게 알려줍니다.
 */
void UIManager::displayPenaltyInfo(int gold, int mp) {
    std::cout << "Gold Penalty: " << gold
              << ", MP Penalty: " << mp
              << std::endl;
}

/**
 * @brief ASCII 아트를 콘솔에 출력
 *
 * @param art  출력할 ASCII 아트 문자열
 *
 * 일일 요약이나 특별 이벤트의 시각적 효과를 위해 사용합니다.
 */
void UIManager::displayAsciiArt(const std::string& art) {
    std::cout << art << std::endl;
}

/**
 * @brief 레벨업 축하 메시지를 콘솔에 출력
 *
 * @param level  새로운 레벨 값
 *
 * 레벨업 시 "Level Up! New Level: X" 형태로 표시합니다.
 */
void UIManager::displayLevelUpMessage(int level) {
    std::cout << "Level Up! New Level: " << level << std::endl;
}

/**
 * @brief 사용자로부터 정수 입력을 받는 함수
 *
 * @param prompt  입력 요청 메시지
 * @return int    입력된 정수 값
 *
 * prompt 메시지를 출력한 후 std::cin으로 입력을 받고,
 * 값을 반환합니다. 입력 검증 로직은 별도 구현 필요합니다.
 */
int UIManager::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    int input;
    std::cin >> input;
    return input;
}

/**
 * @brief 모드 선택 화면을 콘솔에 출력
 *
 * 플레이어가 수행할 수 있는 모드(집필, NPC 응대, 미니게임 등)를 안내합니다.
 */
void UIManager::displayModeSelection() {
    std::cout << "Select Mode:" << std::endl;
}

/**
 * @brief 미니게임 결과를 콘솔에 출력
 *
 * @param result  게임 결과 문자열 ("Win" 또는 "Lose" 등)
 *
 * 미니게임 수행 후 결과를 사용자에게 알려줍니다.
 */
void UIManager::displayMiniGameResult(const std::string& result) {
    std::cout << "MiniGame Result: " << result << std::endl;
}
