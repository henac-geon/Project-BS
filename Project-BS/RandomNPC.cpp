#include "RandomNPC.h"
#include "Openai_Chat_Client.h"
#include "Enum_Utils.h"
#include "AINPC.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

// 변환 함수 제거됨

// ---------------------- NPC 생성 ----------------------

NPC* RandomNPC::create(eNPCGenerationMode mode) {
    switch (mode) {
    case eNPCGenerationMode::SimpleAI:
        return createNpcFromOpenAISimple(createRandomNpcLocally());
    case eNPCGenerationMode::CreativeAI:
        return createNpcFromOpenAICreative();
    case eNPCGenerationMode::Local:
        return createRandomNpcLocally();
    default:
        return createRandomNpcLocally();
    }
}

/// GPT를 쓰지 않고 로컬에서 NPC를 생성합니다.
NPC* RandomNPC::createRandomNpcLocally() {
    std::vector<std::string> names = { "릴리아", "다리우스", "엘렌", "파벨" };
    std::string name = names[rand() % names.size()];

    // 랜덤으로 NPC 속성 생성
    eBookGenre genre = static_cast<eBookGenre>(rand() % 7);
    eBookMood mood = static_cast<eBookMood>(rand() % 5);
    eRequestType requestType = static_cast<eRequestType>(rand() % 5);
    int gold = rand() % 101 + 50;
    int magic = rand() % 51 + 20;
    bool isMale = rand() % 2;

    std::vector<std::string> defaultDialogues = {
    "어서오세요. 책을 찾으시나요?",
    "오늘은 새로운 이야기와 마주하고 싶군요."
    };


    int i = rand() % 7;
    NPC* npc = nullptr;
    if (i == 0) npc = new StudentNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else if (i == 1) npc = new WizardNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else if (i == 2) npc = new MerchantNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else if (i == 3) npc = new LibrarianNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else if (i == 4) npc = new VampireNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else if (i == 5) npc = new KnightNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);
    else npc = new ElfScholarNPC(name, isMale, genre, mood, gold, magic, defaultDialogues);

    npc->setRequestType(requestType);

    return npc;
}

// OpenAI를 사용하여 NPC를 생성합니다. 창의적인 방식으로 NPC를 생성합니다.
NPC* RandomNPC::createNpcFromOpenAICreative() {
    OpenAIChatClient client;

    std::string prompt = R"(
다음 JSON 형식으로 NPC를 생성해줘. 반드시 아래 enum 값만 사용해.
dialogue는 최소 3줄 이상이어야 하며, NPC의 성격과 배경에 맞는 대사를 포함해야 해. 추가로 대사를 통해 NPC가 원하는 책의 장르와 기분을 표현해줘.

- gender: true (남성), false (여성)
- genre (preferredGenre): "Fantasy", "Romance", "Horror", "Mystery", "SciFi", "Apocalypse", "Documentary"
- mood: "Dark", "Light", "Touching", "Tense", "Strange"
- RequestType: "GenreOnly", "MoodOnly", "GenreAndMood", "AnyBook"
- dialogue: 문자열 배열, 최소 3줄 이상 (예: ["어서오세요!", "찾으시는 책이 있나요?"])

형식 예:
{
  "name": "엘드릭",
  "gender": true,
  "age": 43,
  "gold": 120,
  "preferredGenre": "Fantasy",
  "RequestType": "GenreOnly",
  "mood": "Dark",
  "dialogue": [
    "이 책방에서 금지된 마법서를 찾을 수 있을까?",
    "조심해라. 마법은 항상 대가를 요구하지."
  ]
}
)";

    nlohmann::json json = client.sendChatCompletion(prompt);

    if (json.empty()) {
        std::cerr << "[AI 오류] NPC JSON이 비어 있습니다. 기본 NPC를 생성합니다." << std::endl;
        return createRandomNpcLocally();
    }

    std::string name = json.value("name", "이름없음");
    bool isMale = json.value("sex", true);
    std::string genreStr = json.value("preferredGenre", "Fantasy");
    std::string moodStr = json.value("mood", "Light");
    std::string RequestTypeStr = json.value("RequestType", "GenreOnly");


    std::vector<std::string> dialogues;
    if (json.contains("dialogue") && json["dialogue"].is_array()) {
        for (const auto& d : json["dialogue"]) {
            if (d.is_string()) dialogues.push_back(d.get<std::string>());
        }
    }

    if (dialogues.size() < 3) {
        dialogues = {
            "어서오세요!",
            "책을 찾으시는군요?",
            "어떤 장르를 좋아하시나요?"
        };
    }

    int gold = json.value("gold", 100);
    int magic = rand() % 51 + 20;

    eBookGenre genre = Enum_Utils::fromEnglishGenre(genreStr);
    eBookMood mood = Enum_Utils::fromEnglishMood(moodStr);
    eRequestType requestType = Enum_Utils::fromEnglishRequestType(RequestTypeStr);

    NPC* npc = nullptr;
    // AI 생성용 NPC 클래스를 사용
    npc = new AINPC(name, isMale, genre, mood, gold, magic, dialogues);

    npc->setRequestType(requestType);

    return npc;
}

NPC* RandomNPC::createNpcFromOpenAISimple(NPC* baseNPC) {
    if (!baseNPC) baseNPC = createRandomNpcLocally();

    OpenAIChatClient client;
    std::string name = baseNPC->getName();
    std::string genderStr = baseNPC->getIsMale() ? "male" : "female";
    std::string genreStr = Enum_Utils::toEnglish(baseNPC->getPreferredGenre());
    std::string moodStr = Enum_Utils::toEnglish(baseNPC->getPreferredMood());
    int gold = baseNPC->getGold();
    int magic = baseNPC->getMagicPower();
    std::string RequestTypeStr = Enum_Utils::toEnglish(baseNPC->getRequestType());


    std::string prompt = R"(
다음 NPC의 정보를 참고하여 간단한 대사 3줄을 JSON 형식으로 생성해줘.
dialogue는 최소 3줄 이상이어야 하며, NPC의 성격과 배경에 맞는 대사를 포함해야 해. 추가로 대사를 통해 NPC가 원하는 책의 장르와 기분을 표현해줘.
입력: {
  "name": ")" + name + R"(",
  "gender": ")" + genderStr + R"(",
  "preferredGenre": ")" + genreStr + R"(",
  "preferredMood": ")" + moodStr + R"(",
  "RequestType": ")" + RequestTypeStr + R"(",
}

형식 예:
{
  "dialogue": [
    "이 책방에서 금지된 마법서를 찾을 수 있을까?",
    "조심해라. 마법은 항상 대가를 요구하지."
  ]
})";

    nlohmann::json json = client.sendChatCompletion(prompt);

    std::vector<std::string> dialogues;
    if (json.contains("dialogue") && json["dialogue"].is_array()) {
        for (const auto& d : json["dialogue"]) {
            if (d.is_string()) dialogues.push_back(d.get<std::string>());
        }
    }

    if (!dialogues.empty()) {
        baseNPC->setDialogues(dialogues);
    }

    return baseNPC;
}
