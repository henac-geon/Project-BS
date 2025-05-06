#pragma once
#ifndef LEVELSYSTEM_H
#define LEVELSYSTEM_H

/**
 * @class LevelSystem
 * @brief 플레이어의 경험치(Experience)와 레벨(Level)을 관리하는 클래스
 *
 * 경험치를 획득(gainExp)하면 내부적으로 경험치를 누적하고,
 * 레벨업 조건을 만족하는지 확인(checkLevelUp)하여 레벨을 올립니다.
 */
class LevelSystem {
private:
    int experience;  // 현재 누적 경험치
    int level;       // 현재 레벨 (기본값 1 이상)

public:
    /**
     * @brief 기본 생성자
     *
     * experience와 level을 기본값으로 초기화합니다:
     * - experience: 0 (게임 시작 시 경험치 없음)
     * - level: 1      (게임 시작 시 레벨 1)
     */
    LevelSystem();

    /**
     * @brief 경험치를 획득하여 누적하는 함수
     *
     * @param amount  획득할 경험치 양
     *
     * amount만큼 experience를 증가시킵니다.
     * 필요 시 내부에서 즉시 레벨업 조건을 확인하거나,
     * 외부에서 checkLevelUp()을 호출하여 레벨업 여부를 판단할 수 있습니다.
     */
    void gainExp(int amount);

    /**
     * @brief 레벨업 가능 여부를 검사하고, 가능하면 레벨업을 수행
     *
     * @return bool  레벨업이 발생했으면 true, 그렇지 않으면 false
     *
     * 내부 경험치가 레벨업 임계값(threshold)을 넘었는지 확인하고,
     * 넘었다면 level을 증가시키고 초과 경험치를 남겨둘 수 있습니다.
     * 구체적인 임계값 및 보너스 로직은 구현에서 정의합니다.
     */
    bool checkLevelUp();

    /**
     * @brief 현재 레벨을 반환하는 Getter
     * @return int - 현재 level 값
     */
    int getLevel() const;
};

#endif // LEVELSYSTEM_H