#pragma once
#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

/**
 * @class ScoreSystem
 * @brief �÷��̾� �Ǵ� �ý����� ������ ����� �����ϴ� Ŭ����
 *
 * �� Ŭ������ ������� ���� ���ο� ���� ������ �����ϰ�,
 * ������ ����� ���(grade)�� �����Ͽ� �����մϴ�.
 */
class ScoreSystem {
private:
    int score;  // ���� ����: ������ �ൿ�� ���� ������ ����
    int grade;  // ���: ���� ������ ���� �����Ǵ� ���� (��: 1~10)

public:
    /**
     * @brief �⺻ ������
     *
     * score�� grade�� �ʱⰪ���� �����մϴ�.
     * - score: 0
     * - grade: 0 (��� �̼��� ����)
     */
    ScoreSystem();

    /**
     * @brief ������ ������Ʈ�ϴ� �Լ�
     *
     * @param satisfied  ����� �Ǵ� �ý����� ���������� ����� ������� ����
     * - true  : ������ ��� score�� ������Ű��, grade�� ����
     * - false : �Ҹ����� ��� �߰� ������ ������, �ʿ� �� �г�Ƽ ���� �߰� ����
     *
     * updateScore ȣ�� �� ���� score�� ������Ʈ�� ��,
     * ���ο� ���� ������ ���� grade�� �ٽ� �����մϴ�.
     */
    void updateScore(bool satisfied);

    /**
     * @brief ���� ���� ������ ��ȯ�ϴ� Getter
     * @return int - ���� score ��
     */
    int getScore() const;

    /**
     * @brief ���� ����� ��ȯ�ϴ� Getter
     * @return int - ���� grade ��
     *
     * grade�� score ���� ���� �������� �����Ǹ�,
     * ��: score >= 100 �̸� grade = 3, score >= 50 �̸� grade = 2 ������
     * ��ü���� ���� ������ updateScore���� �����մϴ�.
     */
    int getGrade() const;
};

#endif // SCORESYSTEM_H
