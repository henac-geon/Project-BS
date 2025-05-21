#include "BookFactory.h"

namespace {
    constexpr int COLUMN_WIDTH = 16;
}

/*
 * TODO: 책을 생성하고 성공률을 체크하는 기능 추가 구현
 * TODO: 미니게임을 실행하는 기능을 추가 구현
 * TODO: 책을 복구하는 함수 추가 구현
*/

BookFactory::BookFactory() {
    elementManager.loadDefaultElements();
}

Book* BookFactory::createBook(
    eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc
) {
    switch (genre) {
        case eBookGenre::Fantasy:
            return new FantasyBook("Random Fantasy", "A random fantasy book", length);
        case eBookGenre::SciFi:
            return new ScienceBook("Random SciFi", "A random science book", length);
        default:
            return new FantasyBook("Default Fantasy", "Default", length);
    }
}

void BookFactory::displayPlayerStatus() const {
    std::string line;

    line += "마법 기운: " + std::to_string(player.getMagicPower()) + "   ";
    line += "골드: " + std::to_string(player.getGold()) + "   ";
    line += "LV." + std::to_string(player.getLevel()) + " (" + std::to_string(player.getLevelProgress()) + "%)   ";
    line += "서점 랭킹: Rank " + std::to_string(player.getBookstoreRank()) + "   ";
    line += "재고 상태: " + std::to_string(player.getBookStock()) + "/40";

    ConsoleIO::println(line);
}


// 문자열 실제 출력 폭 계산 (한글 2칸 가정)
int BookFactory::getDisplayWidth(const std::string& str) const {
    int width = 0;
    for (char ch : str) {
        width += (static_cast<unsigned char>(ch) & 0x80) ? 2 : 1;
    }
    return width;
}

// 고정 폭 출력용 오른쪽 패딩 적용
std::string BookFactory::padRight(const std::string& str, int totalWidth) const {
    int padding = totalWidth - getDisplayWidth(str);
    return str + std::string((padding > 0) ? padding : 0, ' ');
}

// 카테고리 헤더 출력
void BookFactory::displayCategoryHeaders(const std::vector<std::string>& categories, int colWidth) const {
    std::string headerLine;
    for (const auto& category : categories) {
        headerLine += padRight(std::string("[") + category + std::string("]"), colWidth);
    }
    ConsoleIO::println(headerLine);
}

// 요소 항목 출력
void BookFactory::displayAvailableElements() const {
    const std::vector<std::string> categories = { "장르", "분위기", "분량", "옛지 요소", "기타" };
    std::vector<std::vector<std::string>> allOptions;
    size_t maxRows = 0;
    const int colWidth = 16;  // 너비 조정 가능

    // 옵션 수집 및 최대 행 계산
    for (const auto& category : categories) {
        auto options = elementManager.getOptions(category);
        allOptions.push_back(options);
        if (options.size() > maxRows)
            maxRows = options.size();
    }

    // 헤더 출력
    std::string headerLine;
    for (const auto& category : categories) {
        headerLine += padRight(category, colWidth);
    }
    ConsoleIO::println(headerLine);

    // 각 행 출력
    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;
        for (const auto& column : allOptions) {
            std::string value = (row < column.size()) ? column[row] : "";
            line += padRight(value, colWidth);
        }
        ConsoleIO::println(line);
    }
}
