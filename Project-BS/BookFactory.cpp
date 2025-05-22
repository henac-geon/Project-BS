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

bool BookFactory::isElementAllowed(const std::string& category, const std::string& option) const {
    int level = player.getLevel();

    if (category == "장르") {
        if (option == "판타지") return true;
        if (option == "공상과학") return level >= 2;
        if (option == "아포칼립스") return level >= 5;
    }
    if (category == "옛지 요소") {
        if (option == "없음") return true;
        if (option == "반전") return level >= 5;
    }
    if (category == "기타") {
        if (option == "없음") return true;
        if (option == "숨겨진 코드") return level >= 30;
        if (option == "고대 룬" || option == "운명의 반전") return level >= 50;
        if (option == "미래 예시" || option == "금단 기술") return level >= 80;
    }

    // 기본적으로 허용
    return true;
}


Book* BookFactory::createBook(
    eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc
) {
    // 장르 제한 검사 (예시)
    std::string genreStr;
    switch (genre) {
    case eBookGenre::Fantasy: genreStr = "판타지"; break;
    case eBookGenre::SciFi: genreStr = "공상과학"; break;
    case eBookGenre::Apocalypse: genreStr = "아포칼립스"; break;
    }

    if (!isElementAllowed("장르", genreStr)) {
        ConsoleIO::println("선택한 장르가 현재 레벨에서는 사용할 수 없습니다. 기본값으로 대체됩니다.");
        genre = eBookGenre::Fantasy;  // 대체
    }

    // 이와 유사하게 mood, edge, etc 등에 대해서도 체크 가능

    // 최종 생성
    switch (genre) {
    case eBookGenre::Fantasy:
        return new FantasyBook("Random Fantasy", "A random fantasy book", length);
    case eBookGenre::SciFi:
        return new ScienceBook("Random SciFi", "A random science book", length);
    case eBookGenre::Apocalypse:
        return new FantasyBook("Alt Apoc", "Generated in Apoc genre", length); // TODO: 실제 클래스가 있다면 대체
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
    const int colWidth = 16;
    int level = player.getLevel();

    for (const auto& category : categories) {
        // WritingElementManager에 위임하여 레벨 기반 필터링 수행
        auto filtered = elementManager.getAvailableOptions(category, level);
        allOptions.push_back(filtered);
        maxRows = (filtered.size() > maxRows) ? filtered.size() : maxRows;

    }

    // 헤더 출력
    std::string headerLine;
    for (const auto& category : categories) {
        headerLine += padRight(category, colWidth);
    }
    ConsoleIO::println(headerLine);

    // 요소 출력
    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;
        for (const auto& column : allOptions) {
            std::string value = (row < column.size()) ? column[row] : "";
            line += padRight(value, colWidth);
        }
        ConsoleIO::println(line);
    }
}
