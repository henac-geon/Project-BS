#include "BookFactory.h"
#include "enum_utils.h"
#include <codecvt>
#include <locale>

namespace {
    constexpr int COLUMN_WIDTH = 16;
}

BookFactory::BookFactory() {
    elementManager = WritingElementManager();
}

Book* BookFactory::createRandomBook() {
    eBookGenre genre = static_cast<eBookGenre>(rand() % 3);
    eBookMood mood = static_cast<eBookMood>(rand() % 2);
    int length = 60 + (rand() % 61);
    eBookEdge edge = eBookEdge::None;
    eBookEtc etc = eBookEtc::None;

    return createBook("", "", genre, mood, length, edge, etc);
}

Book* BookFactory::createBook(const std::string& title, const std::string& description,
    eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) {

    int genreCost = elementManager.getMagicCost(WritingElementCategory::Genre, static_cast<int>(genre));
    int moodCost = elementManager.getMagicCost(WritingElementCategory::Mood, static_cast<int>(mood));
    int lengthCost = length;
    int edgeCost = elementManager.getMagicCost(WritingElementCategory::Edge, static_cast<int>(edge));
    int etcCost = elementManager.getMagicCost(WritingElementCategory::Etc, static_cast<int>(etc));

    int totalCost = genreCost + moodCost + lengthCost + edgeCost + etcCost;

    if (player.getMagicPower() < totalCost) {
        ConsoleIO::println("마법 기운이 부족합니다. 일부 속성이 축소되어 책이 집필됩니다.");

        if (player.getMagicPower() < genreCost + lengthCost) {
            ConsoleIO::println("마법 기운이 너무 부족하여 책을 집필할 수 없습니다.");
            return nullptr;
        }

        if (edgeCost > 0) edge = eBookEdge::None;
        if (etcCost > 0) etc = eBookEtc::None;
        if (moodCost > 40) mood = eBookMood::Light;

        moodCost = elementManager.getMagicCost(WritingElementCategory::Mood, static_cast<int>(mood));
        edgeCost = elementManager.getMagicCost(WritingElementCategory::Edge, static_cast<int>(edge));
        etcCost = elementManager.getMagicCost(WritingElementCategory::Etc, static_cast<int>(etc));
        totalCost = genreCost + moodCost + lengthCost + edgeCost + etcCost;
    }

    player.consumeMagicPower(totalCost);

    std::string finalTitle = title;
    std::string finalDesc = description;
    if (finalTitle.empty() || finalDesc.empty()) {
        auto generated = generateTitleAndDescription(genre, mood, edge, etc);
        if (finalTitle.empty()) finalTitle = generated.first;
        if (finalDesc.empty()) finalDesc = generated.second;
    }

    return new Book(finalTitle, finalDesc, genre, mood, length, edge, etc);
}

std::pair<std::string, std::string> BookFactory::generateTitleAndDescription(
    eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc) {
    OpenAIClient client;
    std::string prompt = "다음 속성을 가진 책의 제목과 간단한 설명을 한국어로 생성해줘.\n\n";
    prompt += "장르: " + enum_utils::toKoreanString(genre) + "\n";
    prompt += "분위기: " + enum_utils::toKoreanString(mood) + "\n";
    prompt += "특수 효과: " + enum_utils::toKoreanString(edge) + "\n";
    prompt += "기타: " + enum_utils::toKoreanString(etc) + "\n\n";
    prompt += "응답 형식:\n{\n  \"title\": \"...\",\n  \"description\": \"...\"\n}";

    nlohmann::json response = client.sendChatCompletion(prompt);
    std::string title = response.value("title", "이름 없는 책");
    std::string description = response.value("description", "설명 없음");
    return { title, description };
}

int BookFactory::wcwidth(wchar_t ucs) {
    if (ucs == 0) return 0;
    if (ucs < 32 || (ucs >= 0x7F && ucs < 0xA0)) return -1;
    if ((ucs >= 0x300 && ucs <= 0x36F) || (ucs >= 0x200B && ucs <= 0x200F)) return 0;
    if ((ucs >= 0x1100 && ucs <= 0x115F) || (ucs >= 0x2E80 && ucs <= 0xA4CF) ||
        (ucs >= 0xAC00 && ucs <= 0xD7A3) || (ucs >= 0xF900 && ucs <= 0xFAFF) ||
        (ucs >= 0xFE10 && ucs <= 0xFE6F) || (ucs >= 0x1F300 && ucs <= 0x1F64F) ||
        (ucs >= 0x1F900 && ucs <= 0x1F9FF)) return 2;
    return 1;
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

void BookFactory::displayPlayerStatus() const {
    std::string line;
    line += "마법 기운: " + std::to_string(player.getMagicPower()) + "   ";
    line += "골드: " + std::to_string(player.getGold()) + "   ";
    line += "LV." + std::to_string(player.getLevel()) + " (" + std::to_string(player.getExperience()) + "%)   ";
    line += "서점 랭킹: Rank " + std::to_string(player.getBookstoreRank()) + "   ";
    line += "재고 상태: " + std::to_string(player.getBookStock()) + "/" + std::to_string(player.getMaxBookStock());
    ConsoleIO::println(line);
}

void BookFactory::displayCategoryHeaders(const std::vector<std::string>& categories, int colWidth) const {
    std::string headerLine;
    for (const auto& category : categories) {
        headerLine += padRight("[" + category + "]", colWidth);
    }
    ConsoleIO::println(headerLine);
}

void BookFactory::displayAvailableElements() const {
    displayCategoryHeaders({ "장르", "분위기", "분량", "엣지", "기타" }, COLUMN_WIDTH);
    auto genreList = elementManager.getGenreNames();
    auto moodList = elementManager.getMoodNames();
    auto lengthList = elementManager.getAvailableLengths(player.getLevel());
    auto edgeList = elementManager.getEdgeNames();
    auto etcList = elementManager.getEtcNames();

    size_t maxRows = 0;
    for (auto sz : { genreList.size(), moodList.size(), lengthList.size(), edgeList.size(), etcList.size() })
        if (sz > maxRows) maxRows = sz;

    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;
        auto get = [&](const std::vector<std::string>& list) {
            return (row < list.size()) ? list[row] : " ";
            };
        line += padRight(get(genreList), COLUMN_WIDTH) + "  ";
        line += padRight(get(moodList), COLUMN_WIDTH) + "  ";
        line += padRight(get(lengthList), COLUMN_WIDTH) + "  ";
        line += padRight(get(edgeList), COLUMN_WIDTH) + "  ";
        line += padRight(get(etcList), COLUMN_WIDTH);
        ConsoleIO::println(line);
    }
}
