#include "NPC.h"

NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name), preferredGenre(genre), preferredMood(mood), gold(gold), magicPower(magicPower) {}
