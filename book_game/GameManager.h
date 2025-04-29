#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>                // std::vector 사용을 위한 헤더
#include "Inventory.h"          // Inventory 클래스 정의 포함
#include "NPC.h"                // NPC 클래스 정의 포함
#include "MiniGame.h"           // MiniGame 클래스 정의 포함
#include "LevelSystem.h"        // LevelSystem 클래스 정의 포함
#include "ScoreSystem.h"        // ScoreSystem 클래스 정의 포함
#include "UIManager.h"          // UIManager 클래스 정의 포함

/**
 * @class GameManager
 * @brief 게임의 전체 흐름을 제어하는 중앙 클래스
 *
 * 하루 단위로 플레이어의 행동(책 집필, NPC 응대 등)을 처리하며,
 * 경험치, 점수, 레벨, 자원(골드, 마법력)을 관리하고,
 * UI를 통해 정보를 출력합니다.
 */
class GameManager {
private:
    Inventory inventory;                 // 플레이어가 보유한 책 목록 관리
    std::vector<NPC*> npcs;              // 상호작용할 NPC 객체 목록
    std::vector<MiniGame*> miniGames;    // 진행 가능한 미니게임 목록
    int day;                             // 현재 게임 진행 일수
    int gold;                            // 플레이어가 보유한 골드
    int magicPower;                      // 플레이어의 마법력
    LevelSystem levelSystem;             // 경험치 및 레벨 관리 시스템
    ScoreSystem scoreSystem;             // 점수 및 등급 관리 시스템
    UIManager uiManager;                 // 화면 출력 및 입력 처리 관리

public:
    /**
     * @brief 기본 생성자
     *
     * 모든 서브시스템 및 자원을 초기화하며,
     * day는 1일차로 설정됩니다.
     */
    GameManager();

    /**
     * @brief 소멸자
     *
     * 동적 생성된 NPC 및 MiniGame 객체를 해제하여 메모리 누수를 방지합니다.
     */
    ~GameManager();

    /**
     * @brief 하루를 시작하는 초기화 함수
     *
     * day를 증가시키고, 일일 자원(골드, 마법력)을 리셋하거나 보너스를 적용합니다.
     * UI에 새 하루 시작 메시지를 출력합니다.
     */
    void startDay();

    /**
     * @brief 책을 집필하는 함수
     *
     * Inventory에 새 책을 추가하고,
     * 경험치 및 점수를 일정량 획득합니다.
     * UI를 통해 진행 결과를 표시합니다.
     */
    void writeBook();

    /**
     * @brief NPC들에게 서비스를 제공하는 함수
     *
     * npcs 목록을 순회하며 각 NPC가 주는 책 요청에 응답하고,
     * 책 평가 및 보상(골드/마법력)을 처리합니다.
     * 경험치 및 점수 보너스를 적용합니다.
     */
    void serveNPCs();

    /**
     * @brief 하루 일과 요약을 출력하는 함수
     *
     * 금일 획득한 경험치, 점수, 골드, 마법력 변화량 및 레벨/등급 정보를 UI에 표시합니다.
     */
    void dailySummary();

    /**
     * @brief 하루를 종료하는 함수
     *
     * 하루 단위로 저장/정리 작업을 수행하고,
     * 필요한 경우 자동 저장 또는 다음 단계 준비를 합니다.
     */
    void endDay();
};

#endif // GAMEMANAGER_H
