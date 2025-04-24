#include "LevelSystem.h"

LevelSystem::LevelSystem(): experience(0), level(1) {}

void LevelSystem::gainExp(int amount) {
    experience += amount;
}

bool LevelSystem::checkLevelUp() {
    int threshold = level * 100;
    if (experience >= threshold) {
        level++;
        experience -= threshold;
        return true;
    }
    return false;
}

int LevelSystem::getLevel() const {
    return level;
}
