﻿#include "UIManager.h"          // UIManager 클래스 정의 헤더 포함
#include "AsciiArtRepository.h" // ASCII 아트 저장소 헤더 포함
#include "ConsoleIO.h"
#include <iostream>             // std::cout, std::cin 사용을 위한 iostream 헤더
#include <cstdlib>
#include <string>
#include <array>

void UIManager::displayInventory(const Inventory& inventory) {
    ConsoleIO::println("\n[책 재고]\n");
    ConsoleIO::println("[텍스트 입력창]에 희망하는 행동을 텍스트로 작성해주세요.\n");
    ConsoleIO::println(AsciiArt::getLine('='));
    ConsoleIO::println("  번호 | 제목 | 장르 | 분위기 | 분량 | 반전 | 엣지 요소 | 품질"); // | 재고 상태 | 품질");
    ConsoleIO::println("");
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
    ConsoleIO::println("");
    ConsoleIO::println(AsciiArt::getLine('='));
}



void UIManager::displayBookDetail(const Book* book) {
    if (book) {
        ConsoleIO::println("\n 책 상세 정보:");
        book->displayInfo();  // 내부에 출력 처리되어 있다고 가정
    }
}

void UIManager::displayAsciiArt(const std::string& art) {
    ConsoleIO::println("\n" + art);
}

void UIManager::displayLevelUpMessage(int level) {
    ConsoleIO::println(AsciiArt::getLevelUpArt());
    ConsoleIO::println("\n 레벨 업! 새로운 레벨: " + std::to_string(level));
}


/**
 * @brief 화면을 지우는 함수
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
