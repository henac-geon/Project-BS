#include "LevelSystem.h"  // LevelSystem 클래스 정의 헤더 포함

/**
 * @brief 기본 생성자
 *
 * experience를 0으로, level을 1로 초기화합니다.
 * - experience: 0 (게임 시작 시 경험치 없음)
 * - level: 1      (게임 시작 시 기본 레벨)
 */
LevelSystem::LevelSystem()
    : experience(0),  // 초기 경험치 설정
      level(1)        // 초기 레벨 설정
{
    // 생성자 본문은 비어 있으며, 멤버 초기화 리스트로만 초기화 수행
}

/**
 * @brief 경험치를 획득하여 누적하는 함수
 *
 * @param amount  획득할 경험치 양
 *
 * 전달된 amount 만큼 experience에 더합니다.
 * 이 함수는 단순 누적 기능만 수행하며,
 * 레벨업 여부는 checkLevelUp() 호출로 판단합니다.
 */
void LevelSystem::gainExp(int amount) {
    experience += amount;  // 경험치 증가
}

/**
 * @brief 레벨업 가능 여부를 검사하고, 가능 시 레벨업 수행
 *
 * @return bool  레벨업이 발생했으면 true, 그렇지 않으면 false
 *
 * - threshold: 현재 레벨에 100을 곱한 값으로 설정 (예: 레벨 2이면 200)
 * - experience가 threshold 이상이면:
 *     1) level을 1 증가시킴
 *     2) experience에서 threshold를 차감하여 초과 경험치는 다음 레벨에 반영
 *     3) true 반환
 * - 그렇지 않으면 false 반환
 */
bool LevelSystem::checkLevelUp() {
    int threshold = level * 100;            // 현재 레벨 기반 임계값 계산
    if (experience >= threshold) {
        level++;                            // 레벨업
        experience -= threshold;           // 초과 경험치 남기기
        return true;                       // 레벨업 발생
    }
    return false;                          // 레벨업 없음
}

/**
 * @brief 현재 레벨을 반환하는 Getter
 *
 * @return int - 현재 level 값
 */
int LevelSystem::getLevel() const {
    return level;  // level 멤버 반환
}
