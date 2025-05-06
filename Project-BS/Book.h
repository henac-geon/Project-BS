#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <string>     // std::string ����� ���� ���
#include "Enums.h"   // eBookGenre, eBookMood, eDamageType, eBookCondition ������ ���� ����

/**
 * @class Book
 * @brief å(Book) �߻� Ŭ����
 *
 * ���� �Ǵ� ���ø����̼� ������ å ��ü�� �𵨸��մϴ�.
 * ����, ����, �帣, ������, �з� ���� ��Ÿ�����Ϳ� �ջ� ���¸� �����ϸ�,
 * ����(repair) �� ���� ǥ��(displayInfo) ����� �Ļ� Ŭ�������� �����ϵ��� �մϴ�.
 */
class Book {
protected:
    std::string title;           // å ����
    std::string description;     // å ���� �Ǵ� ���
    eBookGenre genre;            // å �帣 (Enums.h ����)
    eBookMood mood;              // å�� �����ϴ� ������ (Enums.h ����)
    int length;                  // å�� �з� (������ �� �Ǵ� �б� �ҿ� �ð�)
    eBookEdge edge;              // å�� ���� ���
    eBookEtc etc;                // ��Ÿ
    bool isDamaged;              // å �ջ� ���� (true: �ջ��, false: ��ȣ)
    eDamageType damageType;      // �ջ� ���� (Enums.h�� ���ǵ� eDamageType)
    eBookCondition condition;    // å ���� (Enums.h�� ���ǵ� eBookCondition)

public:
    /**
     * @brief ������
     * @param title        å ����
     * @param description  å ���� �Ǵ� ���
     * @param genre        å �帣
     * @param mood         å ������
     * @param length       å �з�
     * @param edge         å �������
     * @param etc          å ��Ÿ
     *
     * �����ڿ����� ���޹��� ��Ÿ�����ͷ� ��� ������ �ʱ�ȭ�ϰ�,
     * �⺻������ �ջ� ���¸� "��ȣ"�� �����մϴ�.
     */
    Book(const std::string& title,
        const std::string& description,
        eBookGenre genre,
        eBookMood mood,
        int length,
        eBookEdge edge,
        eBookEtc etc);

    /**
     * @brief ���� �Ҹ���
     *
     * �Ļ� Ŭ�������� ���� �Ҵ�� �ڿ��� �����ϰ� �����ϱ� ���� �����մϴ�.
     */
    virtual ~Book() = default;

    /**
     * @brief å�� �����ϴ� �Լ�
     *
     * ���� ���� �Լ���, �Ļ� Ŭ�������� �ջ�� å�� �����ϴ� ��ü ������ �����ؾ� �մϴ�.
     */
    virtual void repair() = 0;

    /**
     * @brief å ������ ǥ���ϴ� �Լ�
     *
     * ���� ���� �Լ���, �Ļ� Ŭ�������� å�� ��Ÿ�����Ϳ� ���¸� ����ϴ� ��ü ������ �����ؾ� �մϴ�.
     */
    virtual void displayInfo() const = 0;

    /**
     * @brief å ������ ��ȯ�ϴ� getter
     * @return std::string - å�� ����
     */
    std::string getTitle() const;

    /**
     * @brief å ���¸� ��ȯ�ϴ� getter
     * @return eBookCondition - å�� ����
     */
    eBookCondition getCondition() const;

    /**
     * @brief å �帣�� ��ȯ�ϴ� getter
     * @return eBookGenre - å�� �帣
     */
    eBookGenre getGenre() const;

    /**
     * @brief å �����⸦ ��ȯ�ϴ� getter
     * @return eBookMood - å�� ������
     */
    eBookMood getMood() const;
};

#endif // BOOK_H