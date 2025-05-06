#include "BookFactory.h"
#include "FantasyBook.h"  // FantasyBook Ŭ���� ���� ��� ����
#include "ScienceBook.h"  // ScienceBook Ŭ���� ���� ��� ����
#include <cstdlib>  // rand() �Լ� ����� ���� ���

/**
 * @brief ������ å�� �����ϴ� ���丮 �Լ�
 *
 * @return Book* - ������ ���� å ��ü ������
 *
 * ���̴� 50~149 ������ ���� ������ �����Ǹ�,
 * �帣�� ��Ÿ��(Fantasy), ������� �����(Whimsical)���� �����մϴ�.
 */
Book* BookFactory::createRandomBook() {
    int len = rand() % 100 + 50;  // 0~99 ���� ���� +50 => 50~149
    // ������ �帣�� ������� å ����
    return createBook(eBookGenre::Fantasy, eBookMood::Whimsical, len, eBookEdge::None, eBookEtc::None);
}

/**
 * @brief ������ �Ӽ��� å�� �����ϴ� ���丮 �Լ�
 *
 * @param genre   ������ å�� �帣
 * @param mood    ������ å�� ������
 * @param length  å�� �з�(������ �� ��)
 * @return Book* - ������ å ��ü ������
 *
 * �帣�� ���� �Ļ� Ŭ����(FantasyBook, ScienceBook ��)�� �����Ͽ�
 * �ش� ��ü�� �������� �Ҵ� �� ��ȯ�մϴ�.
 * �������� �ʴ� �帣�� ��� �⺻ ��Ÿ�� å�� �����մϴ�.
 */
Book* BookFactory::createBook(eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc
    ) {
    switch (genre) {
    case eBookGenre::Fantasy:
        // ��Ÿ�� �帣�� å ����
        return new FantasyBook(
            "Random Fantasy",      // ����
            "A random fantasy book", // ����
            length
            );                // �з�

    case eBookGenre::SciFi:
        // ������� �帣�� å ����
        return new ScienceBook(
            "Random SciFi",         // ����
            "A random science book", // ����
            length);                // �з�

    default:
        // �������� �ʴ� �帣�� �⺻ ��Ÿ�� å���� ó��
        return new FantasyBook(
            "Default Fantasy",      // ����
            "Default",              // ����
            length);                // �з�
    }
}
