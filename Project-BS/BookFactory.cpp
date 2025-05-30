#include "BookFactory.h"
#include "enum_utils.h"
#include <codecvt>
#include <locale>

namespace {
    constexpr int COLUMN_WIDTH = 16;
}

BookFactory::BookFactory() {
    elementManager.loadDefaultElements();
    elementManager.loadMagicCosts(); // 마법기운 테이블도 초기화
}

// 유니코드 문자 너비 계산 함수
int wcwidth(wchar_t ucs) {
    if (ucs == 0) return 0;
    if (ucs < 32 || (ucs >= 0x7F && ucs < 0xA0)) return -1;

    if ((ucs >= 0x300 && ucs <= 0x36F) || (ucs >= 0x200B && ucs <= 0x200F))
        return 0;

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

    return true;
}

Book* BookFactory::createRandomBook() {
    eBookGenre genre = static_cast<eBookGenre>(rand() % 3);
    eBookMood mood = static_cast<eBookMood>(rand() % 2);
    int length = 60 + (rand() % 61);
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

    // --- [1] 각 요소의 한글 이름 추출 ---
    std::string genreKo = EnumConverter<eBookGenre>::toKorean(genre);
    std::string moodKo = EnumConverter<eBookMood>::toKorean(mood);
    std::string lengthStr = std::to_string(length);
    std::string edgeKo = EnumConverter<eBookEdge>::toKorean(edge);
    std::string etcKo = EnumConverter<eBookEtc>::toKorean(etc);

    // --- [2] 각 요소별 마법 기운 비용 조회 ---
    int genreCost = elementManager.getMagicCost("장르", genreKo);
    int moodCost = elementManager.getMagicCost("분위기", moodKo);
    int lengthCost = elementManager.getMagicCost("분량", lengthStr);
    int edgeCost = elementManager.getMagicCost("옛지 요소", edgeKo);
    int etcCost = elementManager.getMagicCost("기타", etcKo);
    int totalCost = genreCost + moodCost + lengthCost + edgeCost + etcCost;

    // --- [3] 마법 기운 부족 시 일부 속성 축소 ---
    if (player.getMagicPower() < totalCost) {
        ConsoleIO::println("⚠ 마법 기운이 부족합니다. 일부 속성이 축소되어 책이 집필됩니다.");

        if (player.getMagicPower() < genreCost + lengthCost) {
            ConsoleIO::println("❌ 마법 기운이 너무 부족하여 책을 집필할 수 없습니다.");
            return nullptr;
        }

        if (player.getMagicPower() < totalCost) {
            if (edgeCost > 0) edge = eBookEdge::None;
            if (etcCost > 0)  etc = eBookEtc::None;
            if (moodCost > 40) mood = eBookMood::Light;
        }

        // 변경된 속성 기준으로 비용 재계산
        moodKo = EnumConverter<eBookMood>::toKorean(mood);
        edgeKo = EnumConverter<eBookEdge>::toKorean(edge);
        etcKo = EnumConverter<eBookEtc>::toKorean(etc);

        moodCost = elementManager.getMagicCost("분위기", moodKo);
        edgeCost = elementManager.getMagicCost("옛지 요소", edgeKo);
        etcCost = elementManager.getMagicCost("기타", etcKo);

        totalCost = genreCost + moodCost + lengthCost + edgeCost + etcCost;
    }

    // --- [4] 마법 기운 차감 ---
    player.consumeMagicPower(totalCost);

    // --- [5] 레벨 부족 시 대체 속성 적용 ---
    if (!isElementAllowed("장르", genreKo)) {
        ConsoleIO::println("⚠ 현재 레벨에서는 선택한 장르를 사용할 수 없습니다. '판타지'로 대체됩니다.");
        genre = eBookGenre::Fantasy;
    }
    if (!isElementAllowed("분위기", moodKo)) {
        ConsoleIO::println("⚠ 현재 레벨에서는 선택한 분위기를 사용할 수 없습니다. '밝음'으로 대체됩니다.");
        mood = eBookMood::Light;
    }
    if (!isElementAllowed("옛지 요소", edgeKo)) {
        ConsoleIO::println("⚠ 현재 레벨에서는 선택한 옛지 요소를 사용할 수 없습니다. '없음'으로 대체됩니다.");
        edge = eBookEdge::None;
    }
    if (!isElementAllowed("기타", etcKo)) {
        ConsoleIO::println("⚠ 현재 레벨에서는 선택한 기타 요소를 사용할 수 없습니다. '없음'으로 대체됩니다.");
        etc = eBookEtc::None;
    }

    // --- [6] AI 생성 제목/설명 보완 ---
    std::string finalTitle = title;
    std::string finalDesc = description;
    if (finalTitle.empty() || finalDesc.empty()) {
        auto generated = generateTitleAndDescription(genre, mood, edge, etc);
        if (finalTitle.empty()) finalTitle = generated.first;
        if (finalDesc.empty()) finalDesc = generated.second;
    }

    // --- [7] 책 객체 생성 후 반환 ---
    return new Book(finalTitle, finalDesc, genre, mood, length, edge, etc);
}


std::pair<std::string, std::string> BookFactory::generateTitleAndDescription(
    eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc) {

    OpenAIClient client;
    std::string prompt = "다음 속성을 가진 책의 제목과 간단한 설명을 한국어로 생성해줘.\n\n";
    prompt += "장르: " + EnumConverter<eBookGenre>::toKorean(genre) + "\n";
    prompt += "분위기: " + EnumConverter<eBookMood>::toKorean(mood) + "\n";
    prompt += "특수 효과: " + EnumConverter<eBookEdge>::toKorean(edge) + "\n";
    prompt += "기타: " + EnumConverter<eBookEtc>::toKorean(etc) + "\n\n";
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

std::string BookFactory::padRight(const std::string& str, int totalWidth) const {
    int padding = totalWidth - getDisplayWidth(str);
    return str + std::string((padding > 0) ? padding : 0, ' ');
}

void BookFactory::displayCategoryHeaders(const std::vector<std::string>& categories, int colWidth) const {
    std::string headerLine;
    for (const auto& category : categories) {
        headerLine += padRight("[" + category + "]", colWidth);
    }
    ConsoleIO::println(headerLine);
}

void BookFactory::displayAvailableElements() const {
    const std::vector<std::string> categories = { "장르", "분위기", "분량", "옛지 요소", "기타" };
    std::vector<std::vector<std::string>> allOptions;
    size_t maxRows = 0;
    int level = player.getLevel();

    for (const auto& category : categories) {
        auto filtered = elementManager.getAvailableOptions(category, level);
        allOptions.push_back(filtered);
        maxRows = (filtered.size() > maxRows) ? filtered.size() : maxRows;
    }

    std::string header;
    for (const auto& category : categories) {
        header += padRight(category, COLUMN_WIDTH) + "   ";
    }
    ConsoleIO::println(header);

    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;
        for (size_t col = 0; col < allOptions.size(); ++col) {
            std::string value = (row < allOptions[col].size()) ? allOptions[col][row] : " ";
            std::string displayStr;

            if (value == "잠금") {
                displayStr = "(잠금)";
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


//// 예시: 역변환 사용
//void BookFactory::exampleReverseConversion() {
//    std::string korean = "판타지";
//    eBookGenre genre = EnumConverter<eBookGenre>::fromKorean(korean);
//    int code = EnumConverter<eBookGenre>::toInt(genre);
//    eBookGenre genre2 = EnumConverter<eBookGenre>::fromInt(code);
//    ConsoleIO::println("역변환 테스트 완료: " + EnumConverter<eBookGenre>::toKorean(genre2));
//}
