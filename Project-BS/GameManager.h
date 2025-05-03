#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>                // std::vector 사용을 위한 헤더
#include <functional>           // std::function 사용을 위한 헤더
#include <string>               // std::string 사용을 위한 헤더
#include "Inventory.h"         // Inventory 클래스 정의 포함
#include "NPC.h"               // NPC 클래스 정의 포함
#include "MiniGame.h"          // MiniGame 클래스 정의 포함
#include "LevelSystem.h"       // LevelSystem 클래스 정의 포함
#include "ScoreSystem.h"       // ScoreSystem 클래스 정의 포함
#include "UIManager.h"         // UIManager 클래스 정의 포함

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

    // 메뉴 이름 & 동작 람다 저장
    std::vector<std::string> actionNames;
    std::vector<std::function<bool()>> actions;

    /**
     * @brief actions 및 actionNames 초기화
     */
    void initActions();  // actionNames / actions 초기화

public:
    /**
     * @brief 생성자
     */
    GameManager();

    /**
     * @brief 소멸자
     */
    ~GameManager();

    /**
     * @brief 하루 시작 처리 및 메인 메뉴 화면 표시
     */
    void startDay();

    /**
     * @brief 메뉴 항목을 화면에 출력
     */
    void displayMenu();

    /**
     * @brief 사용자 모드 선택 입력 받기
     * @return int 선택된 모드 번호
     */
    int selectMode();

    /**
     * @brief 선택된 모드 실행
     * @param idx 메뉴 번호(1-based)
     * @return bool 게임 계속 여부 (false면 종료)
     */
    bool executeAction(int idx);

    /**
     * @brief 책 집필 기능
     */
    void writeBook();

    /**
     * @brief NPC 응대 기능
     */
    void serveNPCs();

    /**
     * @brief 인벤토리 조회 기능
     */
    void viewInventory();

    /**
     * @brief 일과 요약 기능
     */
    void dailySummary();

    /**
     * @brief 하루 종료 처리 및 레벨업 체크
     */
    void endDay();
};

#endif // GAMEMANAGER_H