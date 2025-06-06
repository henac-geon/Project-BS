#include "BookFactory.h"
#include "enum_utils.h"
#include "openai_client.h"

#include <codecvt>
#include <locale>
#include <cstdlib>

Book* BookFactory::createBook(const std::string& title, const std::string& description,
    eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) {
    std::string finalTitle = title;
    std::string finalDesc = description;

    if (finalTitle.empty() || finalDesc.empty()) {
        auto generated = generateTitleAndDescription(genre, mood, edge, etc);
        if (finalTitle.empty()) finalTitle = generated.first;
        if (finalDesc.empty()) finalDesc = generated.second;
    }

    return new Book(finalTitle, finalDesc, genre, mood, length, edge, etc);
}

Book* BookFactory::createRandomBook() {
    eBookGenre genre = static_cast<eBookGenre>(rand() % 7);
    eBookMood mood = static_cast<eBookMood>(rand() % 5);
    int length = 60 + (rand() % 61);
    eBookEdge edge = eBookEdge::None;
    eBookEtc etc = eBookEtc::None;

    return createBook("", "", genre, mood, length, edge, etc);
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
