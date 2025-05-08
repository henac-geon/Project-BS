#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>      // std::string ����� ���� ���
#include <vector>      // std::vector ����� ���� ���
#include "Book.h"     // Book Ŭ���� ���� ����
#include "Enums.h"    // eBookGenre, eBookMood ������ ���� ����

// NPC(Non-Player Character) �߻� Ŭ����
// ���� ������ å�� ��û�ϰ� ���� �ű��, �ջ�� å�� ���� ������ ó���ϴ� �������̽� ������ �մϴ�.
class NPC {
protected:
    std::string name;               // NPC�� �̸�
    eBookGenre preferredGenre;      // NPC�� ��ȣ�ϴ� å �帣 (Enums.h ����)
    eBookMood preferredMood;        // NPC�� ���� ��п� ���� ��ȣ�ϴ� å ������
    std::vector<Book*> inventory;   // NPC�� �����ϰų� �뿩 ������ å ���
    int gold;                       // NPC�� ������ ��ȭ (���� �ý��ۿ��� ���)
    int magicPower;                 // NPC�� ������ (Ư�� ���� �Ǵ� ��ȣ�ۿ뿡 Ȱ��)
    eRequestType requestType = eRequestType::GenreAndMood;  // NPC�� ���ϴ� å ��õ ����

public:
    /**
     * @brief NPC ������
     * @param name        NPC�� �̸�
     * @param genre       NPC�� ��ȣ�ϴ� å �帣
     * @param mood        NPC�� ��ȣ�ϴ� å ������
     * @param gold        �ʱ� ��ȭ��
     * @param magicPower  �ʱ� ������
     */
    NPC(const std::string& name,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int magicPower);

    /**
     * @brief ���� �Ҹ���
     * �Ļ� Ŭ�������� ���� �Ҵ�� �ڿ��� �����ϰ� �����ϱ� ���� �����մϴ�.
     */
    virtual ~NPC() = default;

    /**
     * @brief NPC�� å�� ��û�ϴ� �Լ�
     * @param candidates  ��û ������ å �ĺ� ���
     * @return            ���õ� Book ������ (������ nullptr)
     * @note ���� ���� �Լ���, �Ļ� Ŭ�������� ��ü������ �����ؾ� �մϴ�.
     */
    virtual Book* requestBook(const std::vector<Book*>& candidates) = 0;

    /**
     * @brief NPC�� å�� ���ϴ� �Լ�
     * @param book  ���� å ������
     * @return      �� ��� (true: ����, false: �Ҹ���)
     * @note NPC�� ��ȣ���� ���� �� ������ �����մϴ�.
     */
    virtual bool rateBook(Book* book) const;

    /**
     * @brief NPC�� �ջ�� å�� ���� �����ϴ� �Լ�
     * @param book  �ջ�� å ������
     * @note å ���¿� ���� ��ȭ�� ���������� ������ ó���� ������ �����մϴ�.
     */
    virtual void compensateForDamage(Book* book) = 0;

    /**
    * 
    * �ܺο��� ���� �� �� �ְ� ������ִ� get �Լ��� set �Լ�
    * 
    */

    // �̸�
    std::string getName() const;
    void setName(const std::string& newName);

    // �帣
    eBookGenre getPreferredGenre() const;
    void setPreferredGenre(eBookGenre genre);

    // ����
    eBookMood getPreferredMood() const;
    void setPreferredMood(eBookMood mood);

    // �κ��丮 Ȯ��
    const std::vector<Book*>& getInventory() const;

    // ���
    int getGold() const;
    void setGold(int newGold);

    // ������
    int getMagicPower() const;
    void setMagicPower(int newMagicPower);

    // ��û Ÿ��
    eRequestType getRequestType() const;
    void setRequestType(eRequestType type);
};

#endif // NPC_H
