#pragma once
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
    void displayInventory(const Inventory& inventory);
    void displayBookDetail(const Book* book);
    void displayAsciiArt(const std::string& art);
    void displayLevelUpMessage(int level);
    void clearScreen();
};

#endif // UIMANAGER_H
