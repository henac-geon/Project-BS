#pragma once
#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

/**
 * @class ScoreSystem
 * @brief 플레이어 또는 시스템의 점수와 등급을 관리하는 클래스
 *
 * 이 클래스는 사용자의 만족 여부에 따라 점수를 갱신하고,
 * 점수에 기반해 등급(grade)을 산출하여 제공합니다.
 */
class ScoreSystem {
private:
    int score;  // 누적 점수: 만족한 행동이 있을 때마다 증가
    int grade;  // 등급: 점수 구간에 따라 결정되는 레벨 (예: 1~10)

public:
    /**
     * @brief 기본 생성자
     *
     * score와 grade를 초기값으로 설정합니다.
     * - score: 0
     * - grade: 0 (등급 미설정 상태)
     */
    ScoreSystem();

    /**
     * @brief 점수를 업데이트하는 함수
     *
     * @param satisfied  사용자 또는 시스템이 만족스러운 결과를 얻었는지 여부
     * - true  : 만족할 경우 score를 증가시키고, grade를 재계산
     * - false : 불만족할 경우 추가 점수가 없으며, 필요 시 패널티 로직 추가 가능
     *
     * updateScore 호출 시 내부 score를 업데이트한 후,
     * 새로운 점수 구간에 따라서 grade를 다시 설정합니다.
     */
    void updateScore(bool satisfied);

    /**
     * @brief 현재 누적 점수를 반환하는 Getter
     * @return int - 현재 score 값
     */
    int getScore() const;

    /**
     * @brief 현재 등급을 반환하는 Getter
     * @return int - 현재 grade 값
     *
     * grade는 score 값에 따라 구간별로 설정되며,
     * 예: score >= 100 이면 grade = 3, score >= 50 이면 grade = 2 등으로
     * 구체적인 구간 로직은 updateScore에서 구현합니다.
     */
    int getGrade() const;
};

#endif // SCORESYSTEM_H
