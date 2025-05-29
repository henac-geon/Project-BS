#include "RandomNPC.h"
#include "openai_client.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

// ---------------------- ENUM 문자열 매핑 함수 ----------------------

eBookGenre RandomNPC::stringToGenre(const std::string& str) {
    if (str == "Fantasy") return eBookGenre::Fantasy;
    if (str == "Romance") return eBookGenre::Romance;
    if (str == "Horror") return eBookGenre::Horror;
    if (str == "Mystery") return eBookGenre::Mystery;
    if (str == "SciFi") return eBookGenre::SciFi;
    if (str == "Apocalypse") return eBookGenre::Apocalypse;
    if (str == "NonFiction") return eBookGenre::NonFiction;
    return eBookGenre::Fantasy;
}

eBookMood RandomNPC::stringToMood(const std::string& str) {
    if (str == "Dark") return eBookMood::Dark;
    if (str == "Light") return eBookMood::Light;
    if (str == "Emotional") return eBookMood::Emotional;
    if (str == "Tense") return eBookMood::Tense;
    if (str == "Whimsical") return eBookMood::Whimsical;
    return eBookMood::Light;
}

eNPCType RandomNPC::stringToNPCType(const std::string& str) {
    if (str == "student") return eNPCType::Student;
    if (str == "wizard") return eNPCType::Wizard;
    if (str == "merchant") return eNPCType::Merchant;
    if (str == "librarian") return eNPCType::Librarian;
    return eNPCType::Student;
}

std::string RandomNPC::genreToString(eBookGenre genre) {
    switch (genre) {
    case eBookGenre::Fantasy: return "Fantasy";
    case eBookGenre::Romance: return "Romance";
    case eBookGenre::Horror: return "Horror";
    case eBookGenre::Mystery: return "Mystery";
    case eBookGenre::SciFi: return "SciFi";
    case eBookGenre::Apocalypse: return "Apocalypse";
    case eBookGenre::NonFiction: return "NonFiction";
    default: return "Fantasy";
    }
}

std::string RandomNPC::moodToString(eBookMood mood) {
    switch (mood) {
    case eBookMood::Dark: return "Dark";
    case eBookMood::Light: return "Light";
    case eBookMood::Emotional: return "Emotional";
    case eBookMood::Tense: return "Tense";
    case eBookMood::Whimsical: return "Whimsical";
    default: return "Light";
    }
}


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
// ---------------------- 랜덤 NPC (로컬) ----------------------

NPC* RandomNPC::createRandomNpcLocally() {
    std::vector<std::string> names = { "릴리아", "다리우스", "엘렌", "파벨" };
    std::string name = names[rand() % names.size()];

    eBookGenre genre = static_cast<eBookGenre>(rand() % 7);
    eBookMood mood = static_cast<eBookMood>(rand() % 5);
    int gold = rand() % 101 + 50;
    int magic = rand() % 51 + 20;
    bool isMale = rand() % 2;

    int i = rand() % 7;
    NPC* npc = nullptr;
    if (i == 0) npc = new StudentNPC(name, isMale, genre, mood, gold, magic);
    else if (i == 1) npc = new WizardNPC(name, isMale, genre, mood, gold, magic);
    else if (i == 2) npc = new MerchantNPC(name, isMale, genre, mood, gold, magic);
    else if (i == 3) npc = new LibrarianNPC(name, isMale, genre, mood, gold, magic);
    else if (i == 4) npc = new VampireNPC(name, isMale, genre, mood, gold, magic);
    else if (i == 5) npc = new KnightNPC(name, isMale, genre, mood, gold, magic);
    else npc = new ElfScholarNPC(name, isMale, genre, mood, gold, magic);

    std::vector<std::string> dialogues = {
        "어서오세요. 책을 찾으시나요?",
        "오늘은 새로운 이야기와 마주하고 싶군요."
    };
    npc->setDialogues(dialogues);

    return npc;
}


// ---------------------- OpenAI 기반 NPC 생성 (완전 자율) ----------------------
NPC* RandomNPC::createNpcFromOpenAICreative() {
    OpenAIClient client;

    std::string prompt = R"(
다음 JSON 형식으로 NPC를 생성해줘. 반드시 아래 enum 값만 사용해.

- gender: true (남성), false (여성)
- genre (preferredGenre): "Fantasy", "Romance", "Horror", "Mystery", "SciFi", "Apocalypse", "NonFiction"
- mood: "Dark", "Light", "Emotional", "Tense", "Whimsical"
- type: "student", "wizard", "merchant", "librarian"
- dialogue: 문자열 배열, 최소 3줄 이상 (예: ["어서오세요!", "찾으시는 책이 있나요?"])

형식 예:
{
  "name": "엘드릭",
  "gender": true,
  "age": 43,
  "gold": 120,
  "preferredGenre": "Fantasy",
  "mood": "Dark",
  "type": "wizard",
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
    bool isMale = json.value("sex", true) ? true : false;
    std::string typeStr = json.value("type", "student");
    std::string genreStr = json.value("preferredGenre", "Fantasy");
    std::string moodStr = json.value("mood", "Light");

    std::vector<std::string> dialogues;
    if (json.contains("dialogue") && json["dialogue"].is_array()) {
        for (const auto& d : json["dialogue"]) {
            if (d.is_string()) dialogues.push_back(d.get<std::string>());
        }
    }
    else if (json.contains("dialogue") && json["dialogue"].is_string()) {
        dialogues.push_back(json["dialogue"].get<std::string>());
    }
    else {
        dialogues.push_back("어서오세요!");
    }


    int gold = json.value("gold", 100);
    int magic = rand() % 51 + 20;

    eBookGenre genre = stringToGenre(genreStr);
    eBookMood mood = stringToMood(moodStr);
    eNPCType npcType = stringToNPCType(typeStr);

    NPC* npc = nullptr;
    switch (npcType) {
    case eNPCType::Wizard:
        npc = new WizardNPC(name, isMale, genre, mood, gold, magic);
        break;
    case eNPCType::Student:
        npc = new StudentNPC(name, isMale, genre, mood, gold, magic);
        break;
    case eNPCType::Merchant:
        npc = new MerchantNPC(name, isMale, genre, mood, gold, magic);
        break;
    case eNPCType::Librarian:
        npc = new LibrarianNPC(name, isMale, genre, mood, gold, magic);
        break;
    default:
        npc = new StudentNPC(name, isMale, genre, mood, gold, magic);
        break;
    }

    npc->setDialogues(dialogues);

    return npc;
}

// ---------------------- OpenAI 기반 NPC 생성 (간단 AI) ----------------------
NPC* RandomNPC::createNpcFromOpenAISimple(NPC* baseNPC) {
	if (baseNPC == nullptr) {
		baseNPC = createRandomNpcLocally();
	}

    OpenAIClient client;

    // 기본 속성 추출
    std::string name = baseNPC->getName();
    std::string genderStr = baseNPC->getIsMale() ? "male" : "female";

    // 타입 추정 (RTTI 기반)
    std::string typeStr;
    if (dynamic_cast<WizardNPC*>(baseNPC))         typeStr = "wizard";
    else if (dynamic_cast<StudentNPC*>(baseNPC))   typeStr = "student";
    else if (dynamic_cast<MerchantNPC*>(baseNPC))  typeStr = "merchant";
    else if (dynamic_cast<LibrarianNPC*>(baseNPC)) typeStr = "librarian";
    else                                            typeStr = "student"; // fallback

    std::string genreStr = genreToString(baseNPC->getPreferredGenre());
    std::string moodStr = moodToString(baseNPC->getPreferredMood());

    // 프롬프트 구성
    std::string prompt = R"(
다음 NPC의 정보를 참고하여 간단한 대사 3줄을 JSON 형식으로 생성해줘.

입력:
{
  "name": ")" + name + R"(",
  "gender": ")" + genderStr + R"(",
  "type": ")" + typeStr + R"(",
  "preferredGenre": ")" + genreStr + R"(",
  "preferredMood": ")" + moodStr + R"("
}

응답 형식:
{
  "name": ")" + name + R"(",
  "dialogue": [
    "어서오세요.",
    "마법의 흔적이 느껴지는 책을 찾고 있어요.",
    "오늘은 뭔가 특별한 느낌이 오네요."
  ]
}
)";

    // AI 응답 처리
    nlohmann::json json = client.sendChatCompletion(prompt);

    std::vector<std::string> dialogues;
    if (json.contains("dialogue") && json["dialogue"].is_array()) {
        for (const auto& d : json["dialogue"]) {
            if (d.is_string()) dialogues.push_back(d.get<std::string>());
        }
    }

    // AI가 생성한 대사 반영
    if (!dialogues.empty()) {
        baseNPC->setDialogues(dialogues);
    }

    return baseNPC;
}
