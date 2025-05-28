#include "UIManager.h"   // UIManager 클래스 정의 헤더 포함
#include "AsciiArtRepository.h" // ASCII 아트 저장소 헤더 포함
#include "ConsoleIO.h"
#include <iostream>        // std::cout, std::cin 사용을 위한 iostream 헤더
#include <cstdlib>
#include <string>
#include <array>

/**
 * @brief 인벤토리 책 목록을 콘솔에 출력
 *
 * @param inventory  출력할 Inventory 객체
 *
 * inventory.getBooks()로 책 목록을 가져와
 * 인덱스와 책 제목을 한 줄씩 출력합니다.
 */
void UIManager::displayInventory(const Inventory& inventory) {
    ConsoleIO::println("\n[책 재고]");
    ConsoleIO::println("[텍스트 입력창]에 희망하는 행동을 텍스트로 작성해주세요.");
    ConsoleIO::println("------------------------------------------------------------");
    ConsoleIO::println("번호 | 제목 | 장르 | 분위기 | 분량 | 반전 | 엣지 요소 | 품질"); // | 재고 상태 | 품질");

    const auto& books = inventory.getBooks();
    if (books.empty()) {
        ConsoleIO::println(" - 등록된 책이 없습니다.");
        return;
    }

    for (size_t i = 0; i < books.size(); ++i) {
        const Book* book = books[i];
        std::string line = "· ";
        line += (i < 9 ? "0" : "") + std::to_string(i + 1);  // 번호 01, 02 형식
        line += " - " + book->getTitle();
        line += " - " + book->getGenreName();
        line += " - " + book->getMoodName();
        line += " - " + std::to_string(book->getVolume());
        line += " - " + book->getEdgeName();
        line += " - " + book->getEtcName();
        //line += " - " + book->getStockSymbol();  // ●, ○, ×, 재고 상태
        line += " - " + book->getConditionPercentText();  // 손상 비율
        ConsoleIO::println(line);
    }
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
