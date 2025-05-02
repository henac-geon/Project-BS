#pragma once

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>                // std::vector ����� ���� ���
#include "Inventory.h"          // Inventory Ŭ���� ���� ����
#include "NPC.h"                // NPC Ŭ���� ���� ����
#include "MiniGame.h"           // MiniGame Ŭ���� ���� ����
#include "LevelSystem.h"        // LevelSystem Ŭ���� ���� ����
#include "ScoreSystem.h"        // ScoreSystem Ŭ���� ���� ����
#include "UIManager.h"          // UIManager Ŭ���� ���� ����

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

public:
    /**
     * @brief �⺻ ������
     *
     * ��� ����ý��� �� �ڿ��� �ʱ�ȭ�ϸ�,
     * day�� 1������ �����˴ϴ�.
     */
    GameManager();

    /**
     * @brief �Ҹ���
     *
     * ���� ������ NPC �� MiniGame ��ü�� �����Ͽ� �޸� ������ �����մϴ�.
     */
    ~GameManager();

    /**
     * @brief �÷��̾�� ��� ���� UI�� ����, ���õ� ���� ��ȯ
     * @return int - 1: WriteBook, 2: ServeNPCs, 3: DailySummary, 4: Exit
     */
    int selectMode();

    /**
     * @brief �Ϸ縦 �����ϴ� �ʱ�ȭ �Լ�
     *
     * day�� ������Ű��, ���� �ڿ�(���, ������)�� �����ϰų� ���ʽ��� �����մϴ�.
     * UI�� �� �Ϸ� ���� �޽����� ����մϴ�.
     */
    void startDay();

    /**
     * @brief å�� �����ϴ� �Լ�
     *
     * Inventory�� �� å�� �߰��ϰ�,
     * ����ġ �� ������ ������ ȹ���մϴ�.
     * UI�� ���� ���� ����� ǥ���մϴ�.
     */
    void writeBook();

    /**
     * @brief NPC�鿡�� ���񽺸� �����ϴ� �Լ�
     *
     * npcs ����� ��ȸ�ϸ� �� NPC�� �ִ� å ��û�� �����ϰ�,
     * å �� �� ����(���/������)�� ó���մϴ�.
     * ����ġ �� ���� ���ʽ��� �����մϴ�.
     */
    void serveNPCs();

    /**
     * @brief �Ϸ� �ϰ� ����� ����ϴ� �Լ�
     *
     * ���� ȹ���� ����ġ, ����, ���, ������ ��ȭ�� �� ����/��� ������ UI�� ǥ���մϴ�.
     */
    void dailySummary();

    /**
     * @brief �Ϸ縦 �����ϴ� �Լ�
     *
     * �Ϸ� ������ ����/���� �۾��� �����ϰ�,
     * �ʿ��� ��� �ڵ� ���� �Ǵ� ���� �ܰ� �غ� �մϴ�.
     */
    void endDay();
};

#endif // GAMEMANAGER_H
