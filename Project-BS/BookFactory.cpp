#include "BookFactory.h"
#include "Enum_Utils.h"
#include "Openai_Chat_Client.h"

#include <codecvt>
#include <locale>
#include <cstdlib>

std::vector<Book*> BookFactory::initBooks(int count) {
    std::vector<Book*> books;
    books.reserve(count);

    books.push_back(createBookinit("어둠의 성서", "세상을 멸망으로 이끄는 금서의 비밀", eBookGenre::Fantasy, eBookMood::Dark, 80, eBookEdge::None, eBookEtc::None));
    books.push_back(createBookinit("기억의 단편", "과거와 미래가 교차하는 로맨스 이야기", eBookGenre::Romance, eBookMood::Touching, 92, eBookEdge::Reversal, eBookEtc::Label));
    books.push_back(createBookinit("죽음의 저편", "공포와 공허 속 생존자들의 기록", eBookGenre::Horror, eBookMood::Tense, 74, eBookEdge::Unprecedented, eBookEtc::Fragrance));
    books.push_back(createBookinit("7번째 단서", "사라진 탐정이 남긴 마지막 퍼즐", eBookGenre::Mystery, eBookMood::Strange, 88, eBookEdge::Cliché, eBookEtc::None));
    books.push_back(createBookinit("행성 제로", "외계 문명과 인류의 첫 접촉", eBookGenre::SciFi, eBookMood::Bright, 99, eBookEdge::Unprecedented, eBookEtc::Branding));

    //books.push_back(createBookinit("종말의 도시", "인류 최후의 생존자를 향한 추적", eBookGenre::Apocalypse, eBookMood::Tense, 81, eBookEdge::None, eBookEtc::Promotion));
    //books.push_back(createBookinit("빛 속의 잔상", "희망과 절망 사이를 걷는 사랑 이야기", eBookGenre::Romance, eBookMood::Bright, 87, eBookEdge::Reversal, eBookEtc::Fragrance));
    //books.push_back(createBookinit("괴현상 보고서", "도시 괴담을 조사한 연구원의 일지", eBookGenre::Documentary, eBookMood::Strange, 72, eBookEdge::Cliché, eBookEtc::Label));
    //books.push_back(createBookinit("화성의 유언", "인류 개척단이 남긴 마지막 메시지", eBookGenre::SciFi, eBookMood::Touching, 78, eBookEdge::None, eBookEtc::None));
    //books.push_back(createBookinit("심연의 속삭임", "잠들지 못하는 자들의 저주", eBookGenre::Horror, eBookMood::Dark, 66, eBookEdge::Reversal, eBookEtc::None));

    //books.push_back(createBookinit("신의 실험실", "유전자 조작의 끝에서 만난 진실", eBookGenre::Documentary, eBookMood::Tense, 91, eBookEdge::Unprecedented, eBookEtc::Branding));
    //books.push_back(createBookinit("붉은 달 아래", "달빛 아래 숨겨진 비밀 의식", eBookGenre::Mystery, eBookMood::Dark, 85, eBookEdge::Cliché, eBookEtc::None));
    //books.push_back(createBookinit("시간의 결", "타임루프 속에서 되찾은 소중한 하루", eBookGenre::SciFi, eBookMood::Touching, 90, eBookEdge::Reversal, eBookEtc::Promotion));
    //books.push_back(createBookinit("나비의 숲", "현실과 환상이 교차하는 판타지 여정", eBookGenre::Fantasy, eBookMood::Strange, 83, eBookEdge::Unprecedented, eBookEtc::Label));
    //books.push_back(createBookinit("끝나지 않은 일기", "폐허 속 어린아이의 생존 기록", eBookGenre::Apocalypse, eBookMood::Dark, 70, eBookEdge::None, eBookEtc::None));

    return books;
}

Book* BookFactory::createBook(const std::string& title, const std::string& description,
    eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) {
    std::string finalTitle = title;
    std::string finalDesc = description;

    // 제목과 설명이 비어있다면 OpenAI를 통해 생성
    if (finalTitle.empty() || finalDesc.empty()) {
        auto generated = generateTitleAndDescription(genre, mood, edge, etc);
        if (finalTitle.empty()) finalTitle = generated.first;
        if (finalDesc.empty()) finalDesc = generated.second;
    }

    return new Book(finalTitle, finalDesc, genre, mood, length, edge, etc);
}

Book* BookFactory::createBookinit(const std::string& title, const std::string& description,
    eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) {

    // 기존 방식으로 Book 생성
    Book* book = createBook(title, description, genre, mood, length, edge, etc);

    // 조건 덮어쓰기
    book->setCondition(eBookCondition::Worn);

    return book;
}


Book* BookFactory::createRandomBook() {
    eBookGenre genre = static_cast<eBookGenre>(rand() % 7);
    eBookMood mood = static_cast<eBookMood>(rand() % 5);
    int length = 60 + (rand() % 61);
    eBookEdge edge = eBookEdge::None;
    eBookEtc etc = eBookEtc::None;

    return createBook("", "", genre, mood, length, edge, etc);
}

// OpenAI를 통해 책 제목과 설명을 생성하는 함수
std::pair<std::string, std::string> BookFactory::generateTitleAndDescription(
    eBookGenre genre, eBookMood mood, eBookEdge edge, eBookEtc etc) {
    OpenAIChatClient client;
    std::string prompt = "다음 속성을 가진 책의 제목과 간단한 설명을 한국어로 생성해줘.\n\n";
    prompt += "장르: " + Enum_Utils::toKorean(genre) + "\n";
    prompt += "분위기: " + Enum_Utils::toKorean(mood) + "\n";
    prompt += "특수 효과: " + Enum_Utils::toKorean(edge) + "\n";
    prompt += "기타: " + Enum_Utils::toKorean(etc) + "\n\n";
    prompt += "응답 형식:\n{\n  \"title\": \"...\",\n  \"description\": \"...\"\n}";

    nlohmann::json response = client.sendChatCompletion(prompt);
    std::string title = response.value("title", "이름 없는 책");
    std::string description = response.value("description", "설명 없음");
    return { title, description };
}
