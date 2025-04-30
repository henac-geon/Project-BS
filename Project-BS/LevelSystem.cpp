#include "LevelSystem.h"  // LevelSystem Ŭ���� ���� ��� ����

/**
 * @brief �⺻ ������
 *
 * experience�� 0����, level�� 1�� �ʱ�ȭ�մϴ�.
 * - experience: 0 (���� ���� �� ����ġ ����)
 * - level: 1      (���� ���� �� �⺻ ����)
 */
LevelSystem::LevelSystem()
    : experience(0),  // �ʱ� ����ġ ����
    level(1)        // �ʱ� ���� ����
{
    // ������ ������ ��� ������, ��� �ʱ�ȭ ����Ʈ�θ� �ʱ�ȭ ����
}

/**
 * @brief ����ġ�� ȹ���Ͽ� �����ϴ� �Լ�
 *
 * @param amount  ȹ���� ����ġ ��
 *
 * ���޵� amount ��ŭ experience�� ���մϴ�.
 * �� �Լ��� �ܼ� ���� ��ɸ� �����ϸ�,
 * ������ ���δ� checkLevelUp() ȣ��� �Ǵ��մϴ�.
 */
void LevelSystem::gainExp(int amount) {
    experience += amount;  // ����ġ ����
}

/**
 * @brief ������ ���� ���θ� �˻��ϰ�, ���� �� ������ ����
 *
 * @return bool  �������� �߻������� true, �׷��� ������ false
 *
 * - threshold: ���� ������ 100�� ���� ������ ���� (��: ���� 2�̸� 200)
 * - experience�� threshold �̻��̸�:
 *     1) level�� 1 ������Ŵ
 *     2) experience���� threshold�� �����Ͽ� �ʰ� ����ġ�� ���� ������ �ݿ�
 *     3) true ��ȯ
 * - �׷��� ������ false ��ȯ
 */
bool LevelSystem::checkLevelUp() {
    int threshold = level * 100;            // ���� ���� ��� �Ӱ谪 ���
    if (experience >= threshold) {
        level++;                            // ������
        experience -= threshold;           // �ʰ� ����ġ �����
        return true;                       // ������ �߻�
    }
    return false;                          // ������ ����
}

/**
 * @brief ���� ������ ��ȯ�ϴ� Getter
 *
 * @return int - ���� level ��
 */
int LevelSystem::getLevel() const {
    return level;  // level ��� ��ȯ
}
