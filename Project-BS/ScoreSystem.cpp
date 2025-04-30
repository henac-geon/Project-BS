#include "ScoreSystem.h"  // ScoreSystem Ŭ���� ���� ��� ����

/**
 * @brief �⺻ ������
 *
 * score�� grade�� �⺻������ �ʱ�ȭ�մϴ�.
 * - score: 0 (�ʱ� ���� ����)
 * - grade: 0 (�ʱ� ���)
 */
ScoreSystem::ScoreSystem()
    : score(0),    // �ʱ� ���� ����
    grade(0)      // �ʱ� ��� ����
{
    // ������ ������ ���������, ��� �ʱ�ȭ ����Ʈ�θ� �ʱ�ȭ ����
}

/**
 * @brief ������ ������Ʈ�ϰ� ����� �����ϴ� �Լ�
 *
 * @param satisfied  ����ڰ� ���������� ����� ������� ����
 *
 * - true  : ���� �� score�� 10�� �߰�
 * - false : �Ҹ��� �� score���� 5�� ����
 *
 * ������Ʈ ��, grade�� score�� 10���� ���� ������ �����˴ϴ�.
 * ���� ��� score�� 25��� grade�� 2�� �˴ϴ�.
 */
void ScoreSystem::updateScore(bool satisfied) {
    if (satisfied) {
        score += 10;   // ���� �� 10�� ����
    }
    else {
        score -= 5;    // �Ҹ��� �� 5�� ����
    }
    // ���� ������ ����� ��� ��� (���� / 10)
    grade = score / 10;
}

/**
 * @brief ���� ���� ������ ��ȯ�ϴ� Getter
 * @return int - ���� score ��
 */
int ScoreSystem::getScore() const {
    return score;  // score ��� ��ȯ
}

/**
 * @brief ���� ����� ��ȯ�ϴ� Getter
 * @return int - ���� grade ��
 */
int ScoreSystem::getGrade() const {
    return grade;  // grade ��� ��ȯ
}
