#include "Book.h"    // Book Ŭ���� ���� ��� ����

/**
 * @brief Book Ŭ���� ������ ����
 *
 * @param title        å ����
 * @param description  å ���� �Ǵ� ���
 * @param genre        å �帣 (Enums.h�� ���ǵ� eBookGenre)
 * @param mood         å ������ (Enums.h�� ���ǵ� eBookMood)
 * @param length       å �з� (������ �� Ȥ�� �б⿡ �ʿ��� �з�)
 * @param edge         å �������
 * @param etc          å ��Ÿ���
 * �����ڿ����� ��� �ʱ�ȭ ����Ʈ�� ����Ͽ� ��� ����� �����ϰ� �ʱ�ȭ�մϴ�.
 * �⺻������ isDamaged�� false�� �����Ͽ� �ջ���� ���� ���·� �����ϸ�,
 * damageType�� eDamageType::None(�ջ� ����), condition�� eBookCondition::Perfect(����)�� �ʱ�ȭ�մϴ�.
 */
Book::Book(const std::string& title,
    const std::string& description,
    eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc)
    : title(title),               // ���� �ʱ�ȭ
    description(description),   // ���� �ʱ�ȭ
    genre(genre),               // �帣 �ʱ�ȭ
    mood(mood),                 // ������ �ʱ�ȭ
    length(length),             // �з� �ʱ�ȭ
    edge(edge),
    etc(etc),
    isDamaged(false),           // �⺻ �ջ� ����: ����
    damageType(eDamageType::None),       // �⺻ �ջ� ����: ����
    condition(eBookCondition::Perfect)   // �⺻ ����: ����
{
    // TODO: �ʿ信 ���� �߰� �ʱ�ȭ ���� ����
}

/**
 * @brief å ������ ��ȯ�ϴ� Getter
 *
 * @return std::string - å�� ����
 */
std::string Book::getTitle() const {
    return title;  // title ��� ��ȯ
}

/**
 * @brief å ���¸� ��ȯ�ϴ� Getter
 *
 * @return eBookCondition - å�� ���� ����
 *
 * condition ��� ���� ���� �״�� ��ȯ�մϴ�.
 */
eBookCondition Book::getCondition() const {
    return condition;  // condition ��� ��ȯ
}
