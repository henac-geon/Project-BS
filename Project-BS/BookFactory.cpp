#include "BookFactory.h"
#include <codecvt>
#include <locale>

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

std::string genreToString(eBookGenre g) {
    switch (g) {
    case eBookGenre::Fantasy: return "판타지";
    case eBookGenre::SciFi: return "공상과학";
    case eBookGenre::Apocalypse: return "아포칼립스";
    case eBookGenre::Romance: return "로맨스";
    case eBookGenre::Horror: return "공포";
    case eBookGenre::Mystery: return "미스터리";
    case eBookGenre::NonFiction: return "논픽션";
    default: return "기타";
    }
}

std::string moodToString(eBookMood mood) {
    switch (mood) {
    case eBookMood::Dark:        return "암울";
    case eBookMood::Light:       return "밝음";
    case eBookMood::Emotional:   return "감성적";
    case eBookMood::Tense:       return "긴장감";
    case eBookMood::Whimsical:   return "기발함";
    default:                     return "중립";
    }
}

std::string edgeToString(eBookEdge edge) {
    switch (edge) {
    case eBookEdge::None:        return "없음";
    //case eBookEdge::Cursed:      return "저주";
    //case eBookEdge::Blessed:     return "축복";
    //case eBookEdge::Enchanted:   return "마법";
    default:                     return "없음";
    }
}

std::string etcToString(eBookEtc etc) {
    switch (etc) {
    case eBookEtc::None:             return "없음";
    //case eBookEtc::Illustrated:      return "삽화";
    //case eBookEtc::Signed:           return "서명본";
    //case eBookEtc::Ancient:          return "고대";
    //case eBookEtc::SecretCode:       return "숨겨진 코드";
    //case eBookEtc::ForbiddenTech:    return "금단 기술";
    default:                         return "없음";
    }
}



// 유니코드 문자 너비 계산 함수
int wcwidth(wchar_t ucs) {
    if (ucs == 0) return 0;
    if (ucs < 32 || (ucs >= 0x7F && ucs < 0xA0)) return -1;

    // 결합 문자
    if ((ucs >= 0x300 && ucs <= 0x36F) || (ucs >= 0x200B && ucs <= 0x200F))
        return 0;

    // 넓은 문자 (CJK, 이모지 포함)
    if ((ucs >= 0x1100 && ucs <= 0x115F) || (ucs >= 0x2E80 && ucs <= 0xA4CF) ||
        (ucs >= 0xAC00 && ucs <= 0xD7A3) || (ucs >= 0xF900 && ucs <= 0xFAFF) ||
        (ucs >= 0xFE10 && ucs <= 0xFE6F) || (ucs >= 0x1F300 && ucs <= 0x1F64F) ||
        (ucs >= 0x1F900 && ucs <= 0x1F9FF))
        return 2;

    return 1;
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


Book* BookFactory::createRandomBook() {
    eBookGenre genre = static_cast<eBookGenre>(rand() % 3);  // Fantasy, Romance, Horror 예시
    eBookMood mood = static_cast<eBookMood>(rand() % 2);     // Light, Dark 예시
    int length = 60 + (rand() % 61); // 60~120
    eBookEdge edge = eBookEdge::None;
    eBookEtc etc = eBookEtc::None;

    return createBook("", "", genre, mood, length, edge, etc);
}


Book* BookFactory::createBook(
    const std::string& title,
    const std::string& description,
    eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc) {
    std::string genreStr = genreToString(genre);
    if (!isElementAllowed("장르", genreStr)) {
        ConsoleIO::println("선택한 장르가 현재 레벨에서는 사용할 수 없습니다. 기본값으로 대체됩니다.");
        genre = eBookGenre::Fantasy;
    }

    std::string finalTitle = title;
    std::string finalDesc = description;

    if (finalTitle.empty() || finalDesc.empty()) {
        auto generated = generateTitleAndDescription(genre, mood, edge, etc);
        if (finalTitle.empty()) finalTitle = generated.first;
        if (finalDesc.empty()) finalDesc = generated.second;
    }

    switch (genre) {
    case eBookGenre::Fantasy:
        return new FantasyBook(finalTitle, finalDesc, length);
    case eBookGenre::SciFi:
        return new ScienceBook(finalTitle, finalDesc, length);
    default:
        return new FantasyBook("기본 판타지", "AI 생성 실패", length);
    }
}

std::pair<std::string, std::string> BookFactory::generateTitleAndDescription(
    eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc) {

    OpenAIClient client;
    std::string prompt = "다음 속성을 가진 책의 제목과 간단한 설명을 한국어로 생성해줘.\n\n";
    prompt += "장르: " + genreToString(genre) + "\n";
    prompt += "분위기: " + moodToString(mood) + "\n";
    prompt += "특수 효과: " + edgeToString(edge) + "\n";
    prompt += "기타: " + etcToString(etc) + "\n\n";
    prompt += "응답 형식:\n{\n  \"title\": \"...\",\n  \"description\": \"...\"\n}";

    nlohmann::json response = client.sendChatCompletion(prompt);
    std::string title = response.value("title", "이름 없는 책");
    std::string description = response.value("description", "설명 없음");

    return { title, description };
}


void BookFactory::displayPlayerStatus() const {
    std::string line;

    line += "마법 기운: " + std::to_string(player.getMagicPower()) + "   ";
    line += "골드: " + std::to_string(player.getGold()) + "   ";
    line += "LV." + std::to_string(player.getLevel()) + " (" + std::to_string(player.getExperience()) + "%)   ";
    line += "서점 랭킹: Rank " + std::to_string(player.getBookstoreRank()) + "   ";
    line += "재고 상태: " + std::to_string(player.getBookStock()) + "/" + std::to_string(player.getMaxBookStock());

    ConsoleIO::println(line);
}



// UTF-8 문자열의 실제 출력 폭 계산
int BookFactory::getDisplayWidth(const std::string& str) const {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(str);
    int width = 0;
    for (wchar_t ch : wideStr) {
        int w = wcwidth(ch);
        if (w > 0) width += w;
    }
    return width;
}

// 오른쪽 패딩 적용
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
// 사용 가능한 요소를 표로 출력
void BookFactory::displayAvailableElements() const {
    const std::vector<std::string> categories = { "장르", "분위기", "분량", "옛지 요소", "기타" };
    std::vector<std::vector<std::string>> allOptions;
    size_t maxRows = 0;
    int level = player.getLevel();

    // 옵션 필터링 및 최대 행 수 계산
    for (const auto& category : categories) {
        auto filtered = elementManager.getAvailableOptions(category, level);
        allOptions.push_back(filtered);
        maxRows = (filtered.size() > maxRows) ? filtered.size() : maxRows; // 삼항 연산자 적용
    }

    // 헤더 출력
    std::string header;
    for (const auto& category : categories) {
        header += padRight(category, COLUMN_WIDTH) + "   ";
    }
    ConsoleIO::println(header);

    // 구분선 생략 (원래는 ───────── 등)

    // 항목 출력
    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;
        for (size_t col = 0; col < allOptions.size(); ++col) {
            std::string value = (row < allOptions[col].size()) ? allOptions[col][row] : " ";
            std::string displayStr;

            if (value == "잠금") {
                displayStr = "(잠금)  ";
            }
            else {
                std::string point;
                if (categories[col] == "장르") {
                    if (value == "판타지") point = "◆10";
                    else if (value == "공상과학") point = "◆50";
                    else if (value == "아포칼립스") point = "◆90";
                }
                else if (categories[col] == "분위기") {
                    if (value == "밝음") point = "◆20";
                    else if (value == "암울") point = "◆40";
                    else if (value == "공포") point = "◆50";
                    else point = "◆60";
                }
                else if (categories[col] == "분량") {
                    if (value == "30") point = "◆30";
                    else if (value == "90") point = "◆90";
                    else if (value == "120") point = "◆120";
                }
                else if (categories[col] == "옛지 요소") {
                    if (value == "없음") point = "◆0";
                    else if (value == "반전") point = "◆100";
                }
                else if (categories[col] == "기타") {
                    if (value == "없음") point = "◆0";
                    else if (value == "숨겨진 코드") point = "◆70";
                    else if (value == "고대 룬") point = "◆100";
                    else if (value == "금단 기술") point = "◆120";
                }
                displayStr = value + (point.empty() ? "" : " [" + point + "]");
            }

            line += padRight(displayStr, COLUMN_WIDTH) + "  ";
        }
        ConsoleIO::println(line);
    }
}

