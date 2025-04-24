#include "ScoreSystem.h"

ScoreSystem::ScoreSystem(): score(0), grade(0) {}

void ScoreSystem::updateScore(bool satisfied) {
    if (satisfied) score += 10;
    else score -= 5;
    grade = score / 10;
}

int ScoreSystem::getScore() const {
    return score;
}

int ScoreSystem::getGrade() const {
    return grade;
}
