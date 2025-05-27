#ifndef RANDOM_NPC_H
#define RANDOM_NPC_H

#include "NPC.h"          // NPC 기본 클래스
#include "WizardNPC.h"
#include "StudentNPC.h"
#include <string>

class RandomNPC {
public:
    // AI 사용 여부에 따라 NPC 생성
    static NPC* create(bool useAI = false);

private:
    static NPC* createRandomNpcLocally();
    static NPC* createNpcFromOpenAI();
};

#endif
