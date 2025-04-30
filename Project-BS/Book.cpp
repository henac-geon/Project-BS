#include "Book.h"    // Book Ŭ���� ���� ��� ����

/**
 * @brief Book Ŭ���� ������ ����
 *
 * @param title        å ����
 * @param description  å ���� �Ǵ� ���
 * @param genre        å �帣 (Enums.h�� ���ǵ� eBookGenre)
 * @param mood         å ������ (Enums.h�� ���ǵ� eBookMood)
 * @param length       å �з� (������ �� Ȥ�� �б⿡ �ʿ��� �з�)
 *
 * �����ڿ����� ��� �ʱ�ȭ ����Ʈ�� ����Ͽ� ��� ����� �����ϰ� �ʱ�ȭ�մϴ�.
 * �⺻������ isDamaged�� false�� �����Ͽ� �ջ���� ���� ���·� �����ϸ�,
 * damageType�� eDamageType::Lost(�н�), condition�� eBookCondition::Perfect(����)�� �ʱ�ȭ�մϴ�.
 */
Book::Book(const std::string& title, const std::string& description, eBookGenre genre, eBookMood mood, int length)
    : title(title), description(description), genre(genre), mood(mood), length(length), isDamaged(false), damageType(eDamageType::None), condition(eBookCondition::Perfect)
{
    // TODO: �ʿ信 ���� ���� �� �߰� �ʱ�ȭ ���� �߰�
    // ��: �ʱ� ���� ���, ��� ���, �κ��丮�� �ڵ� �߰� ��
}

/**
 * @brief å ������ ��ȯ�ϴ� Getter
 *
 * @return std::string - å�� ����
 *
 * ������ �ζ��� �Լ���, ��� ���� title�� �б� �������� ��ȯ�մϴ�.
 */
std::string Book::getTitle() const {
    return title;  // title ��� ���� ��ȯ
}
