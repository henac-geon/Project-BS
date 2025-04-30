#include "ScoreSystem.h"  // ScoreSystem 클래스 정의 헤더 포함

/**
 * @brief 기본 생성자
 *
 * score와 grade를 기본값으로 초기화합니다.
 * - score: 0 (초기 누적 점수)
 * - grade: 0 (초기 등급)
 */
ScoreSystem::ScoreSystem()
    : score(0),    // 초기 점수 설정
    grade(0)      // 초기 등급 설정
{
    // 생성자 본문이 비어있으며, 멤버 초기화 리스트로만 초기화 수행
}

/**
 * @brief 점수를 업데이트하고 등급을 재계산하는 함수
 *
 * @param satisfied  사용자가 만족스러운 결과를 얻었는지 여부
 *
 * - true  : 만족 시 score에 10점 추가
 * - false : 불만족 시 score에서 5점 차감
 *
 * 업데이트 후, grade는 score를 10으로 나눈 몫으로 설정됩니다.
 * 예를 들어 score가 25라면 grade는 2가 됩니다.
 */
void ScoreSystem::updateScore(bool satisfied) {
    if (satisfied) {
        score += 10;   // 만족 시 10점 증가
    }
    else {
        score -= 5;    // 불만족 시 5점 감소
    }
    // 누적 점수에 기반해 등급 계산 (점수 / 10)
    grade = score / 10;
}

/**
 * @brief 현재 누적 점수를 반환하는 Getter
 * @return int - 현재 score 값
 */
int ScoreSystem::getScore() const {
    return score;  // score 멤버 반환
}

/**
 * @brief 현재 등급을 반환하는 Getter
 * @return int - 현재 grade 값
 */
int ScoreSystem::getGrade() const {
    return grade;  // grade 멤버 반환
}
