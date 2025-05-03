#pragma once
#ifndef LEVELSYSTEM_H
#define LEVELSYSTEM_H

/**
 * @class LevelSystem
 * @brief �÷��̾��� ����ġ(Experience)�� ����(Level)�� �����ϴ� Ŭ����
 *
 * ����ġ�� ȹ��(gainExp)�ϸ� ���������� ����ġ�� �����ϰ�,
 * ������ ������ �����ϴ��� Ȯ��(checkLevelUp)�Ͽ� ������ �ø��ϴ�.
 */
class LevelSystem {
private:
    int experience;  // ���� ���� ����ġ
    int level;       // ���� ���� (�⺻�� 1 �̻�)

public:
    /**
     * @brief �⺻ ������
     *
     * experience�� level�� �⺻������ �ʱ�ȭ�մϴ�:
     * - experience: 0 (���� ���� �� ����ġ ����)
     * - level: 1      (���� ���� �� ���� 1)
     */
    LevelSystem();

    /**
     * @brief ����ġ�� ȹ���Ͽ� �����ϴ� �Լ�
     *
     * @param amount  ȹ���� ����ġ ��
     *
     * amount��ŭ experience�� ������ŵ�ϴ�.
     * �ʿ� �� ���ο��� ��� ������ ������ Ȯ���ϰų�,
     * �ܺο��� checkLevelUp()�� ȣ���Ͽ� ������ ���θ� �Ǵ��� �� �ֽ��ϴ�.
     */
    void gainExp(int amount);

    /**
     * @brief ������ ���� ���θ� �˻��ϰ�, �����ϸ� �������� ����
     *
     * @return bool  �������� �߻������� true, �׷��� ������ false
     *
     * ���� ����ġ�� ������ �Ӱ谪(threshold)�� �Ѿ����� Ȯ���ϰ�,
     * �Ѿ��ٸ� level�� ������Ű�� �ʰ� ����ġ�� ���ܵ� �� �ֽ��ϴ�.
     * ��ü���� �Ӱ谪 �� ���ʽ� ������ �������� �����մϴ�.
     */
    bool checkLevelUp();

    /**
     * @brief ���� ������ ��ȯ�ϴ� Getter
     * @return int - ���� level ��
     */
    int getLevel() const;
};

#endif // LEVELSYSTEM_H