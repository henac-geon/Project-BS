#pragma once

#ifndef RANDOM_NPC_H
#define RANDOM_NPC_H

#include "NPC.h"

// ������ �پ��� NPC Ÿ�Ե��� �ҷ��� �� ���� ���� ������
class RandomNPC {
public:
    static NPC* create();  // ������, �л� �� �ϳ��� ���� ����
};

#endif // RANDOM_NPC_H
