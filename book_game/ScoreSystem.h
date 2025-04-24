#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

class ScoreSystem {
private:
    int score;
    int grade;
public:
    ScoreSystem();
    void updateScore(bool satisfied);
    int getScore() const;
    int getGrade() const;
};

#endif // SCORESYSTEM_H
