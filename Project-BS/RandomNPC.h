#pragma once

#ifndef RANDOM_NPC_H
#define RANDOM_NPC_H

#include "NPC.h"

// 앞으로 다양한 NPC 타입들을 불러올 때 쓰는 랜덤 생성기
class RandomNPC {
public:
    static NPC* create();  // 마법사, 학생 중 하나를 랜덤 생성
};

#endif // RANDOM_NPC_H
