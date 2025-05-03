#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>          // std::string 사용을 위한 헤더
#include "Inventory.h"     // Inventory 클래스 정의 포함
#include "NPC.h"           // NPC 클래스 정의 포함
#include "Book.h"          // Book 클래스 정의 포함
#include "Enums.h"         // eBookCondition 등 열거형 정의 포함

/**
 * @class UIManager
 * @brief 사용자 인터페이스(UI) 출력을 담당하는 클래스
 *
 * 게임의 각 단계에서 플레이어에게 정보를 표시하고,
 * 입력을 받을 수 있는 기능을 제공합니다.
 */
class UIManager {
public:
    /**
     * @brief 메인 메뉴 화면을 출력
     *
     * 게임 시작 또는 하루 시작 시 호출하여
     * 플레이어가 선택할 수 있는 주요 모드를 안내합니다.
     */
    void displayMainMenu();

    /**
     * @brief 인벤토리 화면을 출력
     *
     * @param inventory  현재 플레이어의 인벤토리 정보
     *
     * Inventory 객체를 참조하여 보유 중인 책 목록을
     * 제목과 간단한 정보와 함께 표시합니다.
     */
    void displayInventory(const Inventory& inventory);

    /**
     * @brief NPC 상호작용 화면을 출력
     *
     * @param npc  상호작용할 NPC 객체 포인터
     *
     * NPC의 이름, 선호 장르/분위기 등을 표시하여
     * 플레이어가 NPC의 요청을 이해하도록 돕습니다.
     */
    void displayNPCInteraction(NPC* npc);

    /**
     * @brief 책 상세 정보를 출력
     *
     * @param book  상세 정보를 표시할 Book 객체 포인터
     *
     * 책의 제목, 설명, 장르, 분위기, 분량, 상태 등을
     * 사용자에게 보여줍니다.
     */
    void displayBookDetail(const Book* book);

    /**
     * @brief 책 상태(Condition)를 출력
     *
     * @param bc  책 상태 열거형 값(eBookCondition)
     *
     * eBookCondition 값에 따라 "Perfect", "Worn", "Damaged" 등의
     * 상태 메시지 및 아이콘을 표시합니다.
     */
    void displayBookCondition(eBookCondition bc);

    /**
     * @brief 페널티 정보를 출력
     *
     * @param gold  차감될 골드 양
     * @param mp    차감될 마력 양
     *
     * NPC가 불만족했을 때 발생하는 페널티 정보를
     * 플레이어에게 안내합니다.
     */
    void displayPenaltyInfo(int gold, int mp);

    /**
     * @brief ASCII 아트를 화면에 출력
     *
     * @param art  출력할 ASCII 아트 문자열
     *
     * 일일 요약 등의 시각적 효과를 위해 사용합니다.
     */
    void displayAsciiArt(const std::string& art);

    /**
     * @brief 레벨업 메시지를 출력
     *
     * @param level  새로운 레벨 값
     *
     * 플레이어가 레벨업했을 때 축하 메시지와 함께
     * 새로운 레벨을 표시합니다.
     */
    void displayLevelUpMessage(int level);

    /**
     * @brief 사용자로부터 입력을 받는 함수
     *
     * @param prompt  입력 요청 메시지
     * @return int    사용자가 입력한 정수 값
     *
     * 메뉴 선택 등 숫자 입력이 필요한 경우 호출합니다.
     */
    int getUserInput(const std::string& prompt);

    /**
     * @brief 모드 선택 화면을 출력
     *
     * 미니게임 또는 집필 등 플레이어가 수행할 수 있는
     * 다양한 모드를 안내합니다.
     */
    void displayModeSelection();

    /**
     * @brief 미니게임 결과를 출력
     *
     * @param result  게임 결과 메시지 ("Win" 또는 "Lose" 등)
     *
     * 미니게임 수행 후 성공/실패 결과를 사용자에게 알려줍니다.
     */
    void displayMiniGameResult(const std::string& result);
};

#endif // UIMANAGER_H