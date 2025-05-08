#include "RandomNPC.h"
#include "WizardNPC.h"
#include "StudentNPC.h"
#include <cstdlib>
#include <ctime>
#include <vector>

NPC* RandomNPC::create() {
    std::vector<std::string> names = { "������", "�л�" };
    int nameIndex = rand() % names.size();

    std::string name = names[nameIndex];
    eBookGenre genre = static_cast<eBookGenre>(rand() % 6);  // 0~5 �� ���� ��
    eBookMood mood = static_cast<eBookMood>(rand() % 5);      // 0~4 �� ���� ��
    int gold = rand() % 101 + 50;   // 50 ~ 150 �� ���� �� (�ӽ� ���� ��� ��)
    int magic = rand() % 51 + 20;   // 20 ~ 70 �� ���� �� (�ӽ� ���� ������ ��)

    // eRequestType type = static_cast<eRequestType>(rand() % 4); // NPC å ��û Ÿ���� �������� �ٲ��ִ� �ڵ�

    int r = rand() % 2; // ������ or �л� ���� ���� -> ���߿� NPC �߰��Ǹ� ����

    if (r == 0) return new WizardNPC(name, genre, mood, gold, magic);
    else        return new StudentNPC(name, genre, mood, gold, magic);
}

/*

���� ���� �ڵ带 ��� �� �� �����ϱ�


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