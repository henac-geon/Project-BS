#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>                // std::vector ����� ���� ���
#include <functional>           // std::function ����� ���� ���
#include <string>               // std::string ����� ���� ���
#include "Inventory.h"         // Inventory Ŭ���� ���� ����
#include "NPC.h"               // NPC Ŭ���� ���� ����
#include "MiniGame.h"          // MiniGame Ŭ���� ���� ����
#include "LevelSystem.h"       // LevelSystem Ŭ���� ���� ����
#include "ScoreSystem.h"       // ScoreSystem Ŭ���� ���� ����
#include "UIManager.h"         // UIManager Ŭ���� ���� ����

/**
 * @class GameManager
 * @brief ������ ��ü �帧�� �����ϴ� �߾� Ŭ����
 *
 * �Ϸ� ������ �÷��̾��� �ൿ(å ����, NPC ���� ��)�� ó���ϸ�,
 * ����ġ, ����, ����, �ڿ�(���, ������)�� �����ϰ�,
 * UI�� ���� ������ ����մϴ�.
 */
class GameManager {
private:
    Inventory inventory;                 // �÷��̾ ������ å ��� ����
    std::vector<NPC*> npcs;              // ��ȣ�ۿ��� NPC ��ü ���
    std::vector<MiniGame*> miniGames;    // ���� ������ �̴ϰ��� ���
    int day;                             // ���� ���� ���� �ϼ�
    int gold;                            // �÷��̾ ������ ���
    int magicPower;                      // �÷��̾��� ������
    LevelSystem levelSystem;             // ����ġ �� ���� ���� �ý���
    ScoreSystem scoreSystem;             // ���� �� ��� ���� �ý���
    UIManager uiManager;                 // ȭ�� ��� �� �Է� ó�� ����

    // �޴� �̸� & ���� ���� ����
    std::vector<std::string> actionNames;
    std::vector<std::function<bool()>> actions;

    /**
     * @brief actions �� actionNames �ʱ�ȭ
     */
    void initActions();  // actionNames / actions �ʱ�ȭ

public:
    /**
     * @brief ������
     */
    GameManager();

    /**
     * @brief �Ҹ���
     */
    ~GameManager();

    /**
     * @brief �Ϸ� ���� ó�� �� ���� �޴� ȭ�� ǥ��
     */
    void startDay();

    /**
     * @brief �޴� �׸��� ȭ�鿡 ���
     */
    void displayMenu();

    /**
     * @brief ����� ��� ���� �Է� �ޱ�
     * @return int ���õ� ��� ��ȣ
     */
    int selectMode();

    /**
     * @brief ���õ� ��� ����
     * @param idx �޴� ��ȣ(1-based)
     * @return bool ���� ��� ���� (false�� ����)
     */
    bool executeAction(int idx);

    /**
     * @brief å ���� ���
     */
    void writeBook();

    /**
     * @brief NPC ���� ���
     */
    void serveNPCs();

    /**
     * @brief �κ��丮 ��ȸ ���
     */
    void viewInventory();

    /**
     * @brief �ϰ� ��� ���
     */
    void dailySummary();

    /**
     * @brief �Ϸ� ���� ó�� �� ������ üũ
     */
    void endDay();
};

#endif // GAMEMANAGER_H