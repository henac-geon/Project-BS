#ifndef RANDOM_NPC_H
#define RANDOM_NPC_H

#include "NPC.h"
#include "StudentNPC.h"
#include "WizardNPC.h"
#include "MerchantNPC.h"
#include "LibrarianNPC.h"
#include "VampireNPC.h"
#include "KnightNPC.h"
#include "ElfScholarNPC.h"
#include "Enums.h"
#include <string>

class RandomNPC {
public:
    static NPC* create(eNPCGenerationMode mode);

private:
    static NPC* createRandomNpcLocally();
    static NPC* createNpcFromOpenAISimple(NPC* npc);
    static NPC* createNpcFromOpenAICreative();
    static eBookGenre stringToGenre(const std::string& str);
    static eBookMood stringToMood(const std::string& str);
    static eNPCType stringToNPCType(const std::string& str);
    static std::string genreToString(eBookGenre genre);
    static std::string moodToString(eBookMood mood);
};

#endif
