#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>          // std::string ����� ���� ���
#include "Inventory.h"     // Inventory Ŭ���� ���� ����
#include "NPC.h"           // NPC Ŭ���� ���� ����
#include "Book.h"          // Book Ŭ���� ���� ����
#include "Enums.h"         // eBookCondition �� ������ ���� ����

/**
 * @class UIManager
 * @brief ����� �������̽�(UI) ����� ����ϴ� Ŭ����
 *
 * ������ �� �ܰ迡�� �÷��̾�� ������ ǥ���ϰ�,
 * �Է��� ���� �� �ִ� ����� �����մϴ�.
 */
class UIManager {
public:
    /**
     * @brief ���� �޴� ȭ���� ���
     *
     * ���� ���� �Ǵ� �Ϸ� ���� �� ȣ���Ͽ�
     * �÷��̾ ������ �� �ִ� �ֿ� ��带 �ȳ��մϴ�.
     */
    void displayMainMenu();

    /**
     * @brief �κ��丮 ȭ���� ���
     *
     * @param inventory  ���� �÷��̾��� �κ��丮 ����
     *
     * Inventory ��ü�� �����Ͽ� ���� ���� å �����
     * ����� ������ ������ �Բ� ǥ���մϴ�.
     */
    void displayInventory(const Inventory& inventory);

    /**
     * @brief NPC ��ȣ�ۿ� ȭ���� ���
     *
     * @param npc  ��ȣ�ۿ��� NPC ��ü ������
     *
     * NPC�� �̸�, ��ȣ �帣/������ ���� ǥ���Ͽ�
     * �÷��̾ NPC�� ��û�� �����ϵ��� �����ϴ�.
     */
    void displayNPCInteraction(NPC* npc);

    /**
     * @brief å �� ������ ���
     *
     * @param book  �� ������ ǥ���� Book ��ü ������
     *
     * å�� ����, ����, �帣, ������, �з�, ���� ����
     * ����ڿ��� �����ݴϴ�.
     */
    void displayBookDetail(const Book* book);

    /**
     * @brief å ����(Condition)�� ���
     *
     * @param bc  å ���� ������ ��(eBookCondition)
     *
     * eBookCondition ���� ���� "Perfect", "Worn", "Damaged" ����
     * ���� �޽��� �� �������� ǥ���մϴ�.
     */
    void displayBookCondition(eBookCondition bc);

    /**
     * @brief ���Ƽ ������ ���
     *
     * @param gold  ������ ��� ��
     * @param mp    ������ ���� ��
     *
     * NPC�� �Ҹ������� �� �߻��ϴ� ���Ƽ ������
     * �÷��̾�� �ȳ��մϴ�.
     */
    void displayPenaltyInfo(int gold, int mp);

    /**
     * @brief ASCII ��Ʈ�� ȭ�鿡 ���
     *
     * @param art  ����� ASCII ��Ʈ ���ڿ�
     *
     * ���� ��� ���� �ð��� ȿ���� ���� ����մϴ�.
     */
    void displayAsciiArt(const std::string& art);

    /**
     * @brief ������ �޽����� ���
     *
     * @param level  ���ο� ���� ��
     *
     * �÷��̾ ���������� �� ���� �޽����� �Բ�
     * ���ο� ������ ǥ���մϴ�.
     */
    void displayLevelUpMessage(int level);

    /**
     * @brief ����ڷκ��� �Է��� �޴� �Լ�
     *
     * @param prompt  �Է� ��û �޽���
     * @return int    ����ڰ� �Է��� ���� ��
     *
     * �޴� ���� �� ���� �Է��� �ʿ��� ��� ȣ���մϴ�.
     */
    int getUserInput(const std::string& prompt);

    /**
     * @brief ��� ���� ȭ���� ���
     *
     * �̴ϰ��� �Ǵ� ���� �� �÷��̾ ������ �� �ִ�
     * �پ��� ��带 �ȳ��մϴ�.
     */
    void displayModeSelection();

    /**
     * @brief �̴ϰ��� ����� ���
     *
     * @param result  ���� ��� �޽��� ("Win" �Ǵ� "Lose" ��)
     *
     * �̴ϰ��� ���� �� ����/���� ����� ����ڿ��� �˷��ݴϴ�.
     */
    void displayMiniGameResult(const std::string& result);

    void clearScreen();
};

#endif // UIMANAGER_H