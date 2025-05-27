#include "RandomNPC.h"
#include "openai_client.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

// 문자열을 enum으로 변환하는 유틸 함수들
eBookGenre stringToGenre(const std::string& str) {
    if (str == "Fantasy") return eBookGenre::Fantasy;
    if (str == "Horror") return eBookGenre::Horror;
    if (str == "Romance") return eBookGenre::Romance;
    return eBookGenre::Fantasy;
}

eBookMood stringToMood(const std::string& str) {
    if (str == "Dark") return eBookMood::Dark;
    if (str == "Light") return eBookMood::Light;
    return eBookMood::Light;
}

// public: NPC 생성 진입점
NPC* RandomNPC::create(bool useAI) {
    return useAI ? createNpcFromOpenAI() : createRandomNpcLocally();
}

// 랜덤 NPC 생성 (로컬)
NPC* RandomNPC::createRandomNpcLocally() {
    std::vector<std::string> names = { "릴리아", "다리우스", "엘렌", "파벨" };
    std::string name = names[rand() % names.size()];

    eBookGenre genre = static_cast<eBookGenre>(rand() % 3);  // 0~2: Fantasy, Horror, Romance
    eBookMood mood = static_cast<eBookMood>(rand() % 2);     // 0~1: Dark, Light
    int gold = rand() % 101 + 50;                            // 50~150
    int magic = rand() % 51 + 20;                            // 20~70

    int r = rand() % 2;
    if (r == 0) return new WizardNPC(name, genre, mood, gold, magic);
    else        return new StudentNPC(name, genre, mood, gold, magic);
}

// OpenAI 기반 NPC 생성
NPC* RandomNPC::createNpcFromOpenAI() {
    OpenAIClient client;

    std::string prompt = R"(다음과 같은 형식으로 NPC 정보를 JSON으로 생성해줘:
{
  "name": "엘드릭",
  "gender": "남성",
  "age": 43,
  "gold": 120,
  "preferredGenre": "Fantasy",
  "mood": "Dark",
  "type": "wizard"
}
'preferredGenre'는 Fantasy, Horror, Romance 중 하나
'mood'는 Dark 또는 Light 중 하나
'type'은 wizard 또는 student 중 하나
)";

    nlohmann::json json = client.sendChatCompletion(prompt);

    if (json.empty()) {
        std::cerr << "[AI 오류] NPC JSON이 비어 있습니다. 기본 NPC를 생성합니다." << std::endl;
        return createRandomNpcLocally();
    }

    std::string name = json["name"];
    std::string type = json.value("type", "wizard");
    eBookGenre genre = stringToGenre(json["preferredGenre"]);
    eBookMood mood = stringToMood(json.value("mood", "Light"));
    int gold = json["gold"];
    int magic = rand() % 51 + 20;

    if (type == "wizard")
        return new WizardNPC(name, genre, mood, gold, magic);
    else
        return new StudentNPC(name, genre, mood, gold, magic);
}
