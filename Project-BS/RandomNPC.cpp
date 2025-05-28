#include "RandomNPC.h"
#include "openai_client.h"
#include "Enums.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

// ---------------------- ENUM 문자열 매핑 함수 ----------------------

eBookGenre stringToGenre(const std::string& str) {
    if (str == "Fantasy") return eBookGenre::Fantasy;
    if (str == "Romance") return eBookGenre::Romance;
    if (str == "Horror") return eBookGenre::Horror;
    if (str == "Mystery") return eBookGenre::Mystery;
    if (str == "SciFi") return eBookGenre::SciFi;
    if (str == "Apocalypse") return eBookGenre::Apocalypse;
    if (str == "NonFiction") return eBookGenre::NonFiction;
    return eBookGenre::Fantasy;
}

eBookMood stringToMood(const std::string& str) {
    if (str == "Dark") return eBookMood::Dark;
    if (str == "Light") return eBookMood::Light;
    if (str == "Emotional") return eBookMood::Emotional;
    if (str == "Tense") return eBookMood::Tense;
    if (str == "Whimsical") return eBookMood::Whimsical;
    return eBookMood::Light;
}

eNPCType stringToNPCType(const std::string& str) {
    if (str == "student") return eNPCType::Student;
    if (str == "wizard") return eNPCType::Wizard;
    if (str == "merchant") return eNPCType::Merchant;
    if (str == "librarian") return eNPCType::Librarian;
    return eNPCType::Student;
}

// ---------------------- NPC 생성 ----------------------

NPC* RandomNPC::create(bool useAI) {
    return useAI ? createNpcFromOpenAI() : createRandomNpcLocally();
}

// ---------------------- 랜덤 NPC (로컬) ----------------------

NPC* RandomNPC::createRandomNpcLocally() {
    std::vector<std::string> names = { "릴리아", "다리우스", "엘렌", "파벨" };
    std::string name = names[rand() % names.size()];

    eBookGenre genre = static_cast<eBookGenre>(rand() % 3);  // Fantasy, Horror, Romance
    eBookMood mood = static_cast<eBookMood>(rand() % 2);     // Dark, Light
    int gold = rand() % 101 + 50;                            // 50~150
    int magic = rand() % 51 + 20;                            // 20~70

    int r = rand() % 2;
    NPC* npc = nullptr;
    if (r == 0) {
        npc = new WizardNPC(name, genre, mood, gold, magic);
    }
    else {
        npc = new StudentNPC(name, genre, mood, gold, magic);
    }
    npc->setDialogue("안녕하세요, 책을 좀 보고 싶습니다.");
    return npc;

}

// ---------------------- OpenAI 기반 NPC 생성 ----------------------

NPC* RandomNPC::createNpcFromOpenAI() {
    OpenAIClient client;

    std::string prompt = R"(
다음 JSON 형식으로 NPC를 생성해줘. 반드시 아래 enum 값만 사용해.

- genre (preferredGenre): "Fantasy", "Romance", "Horror", "Mystery", "SciFi", "Apocalypse", "NonFiction"
- mood: "Dark", "Light", "Emotional", "Tense", "Whimsical"
- type: "student", "wizard", "merchant", "librarian"

형식 예:
{
  "name": "엘드릭",
  "gender": "남성",
  "age": 43,
  "gold": 120,
  "preferredGenre": "Fantasy",
  "mood": "Dark",
  "type": "wizard",
  "dialogue": "이 책방에서 금지된 마법서를 찾을 수 있을까?"
}
)";

    nlohmann::json json = client.sendChatCompletion(prompt);

    if (json.empty()) {
        std::cerr << "[AI 오류] NPC JSON이 비어 있습니다. 기본 NPC를 생성합니다." << std::endl;
        return createRandomNpcLocally();
    }

    std::string name = json.value("name", "이름없음");
    std::string typeStr = json.value("type", "student");
    std::string genreStr = json.value("preferredGenre", "Fantasy");
    std::string moodStr = json.value("mood", "Light");
    std::string dialogue = json.value("dialogue", "어서오세요!");

    int gold = json.value("gold", 100);
    int magic = rand() % 51 + 20;

    eBookGenre genre = stringToGenre(genreStr);
    eBookMood mood = stringToMood(moodStr);
    eNPCType npcType = stringToNPCType(typeStr);

    NPC* npc = nullptr;
    switch (npcType) {
    case eNPCType::Wizard:
        npc = new WizardNPC(name, genre, mood, gold, magic);
        break;
    case eNPCType::Student:
        npc = new StudentNPC(name, genre, mood, gold, magic);
        break;
    case eNPCType::Merchant:
        // TODO : npc = new MerchantNPC(name, genre, mood, gold, magic);
        npc = new StudentNPC(name, genre, mood, gold, magic);
        break;
    case eNPCType::Librarian:
        // TODO :  npc = new LibrarianNPC(name, genre, mood, gold, magic);
        npc = new StudentNPC(name, genre, mood, gold, magic);
        break;
    default:
        npc = new StudentNPC(name, genre, mood, gold, magic);
        break;
    }

    npc->setDialogue(dialogue);
    return npc;
}
