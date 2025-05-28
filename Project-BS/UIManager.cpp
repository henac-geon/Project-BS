#include "UIManager.h"   // UIManager 클래스 정의 헤더 포함
#include "AsciiArtRepository.h" // ASCII 아트 저장소 헤더 포함
#include "ConsoleIO.h"
#include <iostream>        // std::cout, std::cin 사용을 위한 iostream 헤더
#include <cstdlib>
#include <string>
#include <array>

/**
 * @brief 메인 메뉴를 콘솔에 출력
 *
 * "=== Main Menu ===" 헤더를 사용하여
 * 플레이어에게 주요 명령 선택 인터페이스를 제공합니다.
 */
void UIManager::displayMainMenu() {
    ConsoleIO::println("\n=== Main Menu ===");
    ConsoleIO::println("1. 집필 모드");
    ConsoleIO::println("2. NPC 응대");
    ConsoleIO::println("3. 미니게임");
    ConsoleIO::println("4. 인벤토리 확인");
    ConsoleIO::println("5. 종료");
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
    ConsoleIO::println("\n 인벤토리 목록:");
    const auto& books = inventory.getBooks();
    if (books.empty()) {
        ConsoleIO::println(" - 등록된 책이 없습니다.");
        return;
    }
    for (size_t i = 0; i < books.size(); ++i) {
        ConsoleIO::println(std::to_string(i) + ": " + books[i]->getTitle());
    }
	//TODO: 책 상세 정보 출력 기능 추가 구현
	//TODO: 인벤토리 나가기 기능 추가 구현
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
    if (book) {
        ConsoleIO::println("\n 책 상세 정보:");
        book->displayInfo();  // 내부에 출력 처리되어 있다고 가정
    }
}

/**
 * @brief 책 상태(Condition)를 콘솔에 출력
 *
 * @param bc  eBookCondition 열거형 값
 *
 * 정수형으로 변환하여 상태 값을 표시하며,
 * enum-to-string 매핑을 구현하여 출력할 수도 있습니다.
 * TODO: enum-to-string 매핑 테이블은 추후 Enums.h에 이관해야 함
 */
void UIManager::displayBookCondition(eBookCondition bc) {
    constexpr std::array<const char*, 4> conditionStrings = {
        "최상",
        "양호",
        "약간의 손상이 있음",
        "훼손이 많이 됨 수리 필요"
    };

    ConsoleIO::print("상태: ");

    int index = static_cast<int>(bc); // enum을 정수형으로 변환
    if (index >= 0 && index < static_cast<int>(conditionStrings.size())) {
        ConsoleIO::println(conditionStrings[index]);
    }
    else {
        ConsoleIO::println("알 수 없음");
    }
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
    ConsoleIO::println("\n 페널티 발생!");
    ConsoleIO::println(" - 골드 감소: " + std::to_string(gold));
    ConsoleIO::println(" - 마력 감소: " + std::to_string(mp));
}

/**
 * @brief ASCII 아트를 콘솔에 출력
 *
 * @param art  출력할 ASCII 아트 문자열
 *
 * 일일 요약이나 특별 이벤트의 시각적 효과를 위해 사용합니다.
 */
void UIManager::displayAsciiArt(const std::string& art) {
    ConsoleIO::println("\n" + art);
}

/**
 * @brief 레벨업 축하 메시지를 콘솔에 출력
 *
 * @param level  새로운 레벨 값
 *
 * 레벨업 시 "Level Up! New Level: X" 형태로 표시합니다.
 */
void UIManager::displayLevelUpMessage(int level) {
    ConsoleIO::println(AsciiArt::getLevelUpArt());
    ConsoleIO::println("\n 레벨 업! 새로운 레벨: " + std::to_string(level));
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
    ConsoleIO::print(prompt);
    int input;
    std::cin >> input;
    // TODO: 예외 처리 및 재입력 로직 구현 가능
    return input;
}

/**
 * @brief 모드 선택 화면을 콘솔에 출력
 *
 * 플레이어가 수행할 수 있는 모드(집필, NPC 응대, 미니게임 등)를 안내합니다.
 */
void UIManager::displayModeSelection() {
    ConsoleIO::println(L"\n모드를 선택하세요:");
    ConsoleIO::println(L"1. 집필 모드");
    ConsoleIO::println(L"2. NPC 응대");
    ConsoleIO::println(L"3. 미니게임");
    ConsoleIO::println(L"4. 돌아가기");
}

/**
 * @brief 미니게임 결과를 콘솔에 출력
 *
 * @param result  게임 결과 문자열 ("Win" 또는 "Lose" 등)
 *
 * 미니게임 수행 후 결과를 사용자에게 알려줍니다.
 */
void UIManager::displayMiniGameResult(const std::string& result) {
    ConsoleIO::println("\n 미니게임 결과: " + result);
}

/**
 * @brief 화면을 지우는 함수
 *
 * 플랫폼에 따라 콘솔 화면을 지웁니다.
 * Windows에서는 "cls", Unix 계열에서는 "clear" 명령어를 사용합니다.
 */
void UIManager::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
