#ifndef LEVELSYSTEM_H
#define LEVELSYSTEM_H

class LevelSystem {
private:
    int experience;
    int level;
public:
    LevelSystem();
    void gainExp(int amount);
    bool checkLevelUp();
    int getLevel() const;
};

#endif // LEVELSYSTEM_H
