#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "UIManager.h"
#include "Inventory.h"
#include "NPC.h"
#include "ScoreSystem.h"
#include "LevelSystem.h"
#include "BookFactory.h"

#include <vector>
#include <string>

/**
 * @class GameManager
 * @brief 전체 게임의 진행을 담당하는 중앙 관리 클래스
 *
 * 게임의 흐름을 제어하며, 집필, NPC 상호작용, 정산, 다음 날 진행 등의
 * 기능을 포함한다.
 */
class GameManager {
private:
    int day;                   ///< 현재 날짜
    int gold;                  ///< 플레이어의 골드 (임시 중복 변수)
    int magicPower;            ///< 플레이어의 마법 기운 (임시 중복 변수)
    Inventory inventory;       ///< 플레이어의 인벤토리
    std::vector<NPC*> npcs;    ///< 하루에 등장하는 NPC 리스트
    UIManager uiManager;       ///< UI 출력 전담 관리자
    BookFactory bookFactory;   ///< 책 생성 전담 관리자
    ScoreSystem scoreSystem;   ///< 평판 및 점수 시스템
    LevelSystem levelSystem;   ///< 레벨 업 시스템

public:
    GameManager();
    ~GameManager();

    void run();                        ///< 전체 게임 루프 시작
    bool startDay();                  ///< 하루 시작 전 확인
    void performWritingPhase();       ///< 집필 단계
    void performShowInventoryPhase(); ///< 책 인벤토리 확인 및 소각
    void performNPCPhase();           ///< NPC 응대 단계
    void performSettlementPhase();    ///< 하루 마무리 정산 단계
    void endDay();                    ///< 하루 종료 및 레벨 확인
};

#endif // GAME_MANAGER_H
