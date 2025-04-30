#pragma once

#ifndef MINIGAME_H
#define MINIGAME_H

#include "Book.h"  // Book Ŭ���� ���Ǹ� �����Ͽ�, �̴ϰ��ӿ��� ����� å ��ü ����

/**
 * @class MiniGame
 * @brief å(Book)�� Ȱ���� �پ��� �̴ϰ��� �������̽�
 *
 * �Ļ� Ŭ�������� ��ü���� �̴ϰ��� ������ �����ϱ� ����
 * �������̽� ������ �����մϴ�. play() �޼��带 ����
 * å ��ü�� Ȱ���� ���� ���� �� ��� ��ȯ�� ó���մϴ�.
 */
class MiniGame {
public:
    /**
     * @brief ���� �Ҹ���
     *
     * �Ļ� Ŭ�������� ���� �ڿ��� �����ϰ� �����ϱ� ���� �����մϴ�.
     */
    virtual ~MiniGame() = default;

    /**
     * @brief �̴ϰ��� ���� �Լ�
     *
     * @param book  ���ӿ� ����� Book ��ü ������
     * @return bool - ���� ���� ���� (true: ����/�̱�, false: ����/��)
     *
     * ���� ���� �Լ���, �Ļ� Ŭ�������� å �����͸� �������
     * ��ü���� ���� ������ �����Ͽ� ����/���и� �Ǵ��մϴ�.
     */
    virtual bool play(Book* book) = 0;
};

#endif // MINIGAME_H