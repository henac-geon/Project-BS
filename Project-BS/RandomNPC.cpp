#include "RandomNPC.h"
#include "WizardNPC.h"
#include "StudentNPC.h"
#include <cstdlib>
#include <ctime>
#include <vector>

NPC* RandomNPC::create() {
    std::vector<std::string> names = { "마법사", "학생" };
    int nameIndex = rand() % names.size();

    std::string name = names[nameIndex];
    eBookGenre genre = static_cast<eBookGenre>(rand() % 6);  // 0~5 중 랜덤 값
    eBookMood mood = static_cast<eBookMood>(rand() % 5);      // 0~4 중 랜덤 값
    int gold = rand() % 101 + 50;   // 50 ~ 150 중 랜덤 값 (임시 보유 골드 값)
    int magic = rand() % 51 + 20;   // 20 ~ 70 중 랜덤 값 (임시 보유 마법력 값)

    // eRequestType type = static_cast<eRequestType>(rand() % 4); // NPC 책 요청 타입을 랜덤으로 바꿔주는 코드

    int r = rand() % 2; // 마법사 or 학생 선택 변수 -> 나중에 NPC 추가되면 변경

    if (r == 0) return new WizardNPC(name, genre, mood, gold, magic);
    else        return new StudentNPC(name, genre, mood, gold, magic);
}

/*

위에 랜덤 코드를 사용 할 때 변경하기


if (r == 0) {
        auto* npc = new WizardNPC(name, genre, mood, gold, magic);
        npc->setRequestType(type);
        return npc;
    } else {
        auto* npc = new StudentNPC(name, genre, mood, gold, magic);
        npc->setRequestType(type);
        return npc;
    }

*/