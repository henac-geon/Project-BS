#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>    // std::vector ����� ���� ���
#include <string>    // std::string ����� ���� ���
#include "Book.h"   // Book Ŭ���� ���� ����

/**
 * @class Inventory
 * @brief å(Book) ��ü�� �����ϴ� �κ��丮 Ŭ����
 *
 * å�� �߰�(addBook), ����(removeBook), �˻�(findBook)�ϴ�
 * ����� �����ϸ�, ���� ���� ���� å ����� ��ȯ(getBooks)�մϴ�.
 */
class Inventory {
private:
    std::vector<Book*> books;  // �κ��丮�� ������ Book ������ ���

public:
    /**
     * @brief å�� �κ��丮�� �߰�
     *
     * @param book  �߰��� Book ��ü�� ������
     *
     * books ������ ���� ���޵� book �����͸� push_back �մϴ�.
     */
    void addBook(Book* book);

    /**
     * @brief �ε����� å�� �κ��丮���� ����
     *
     * @param index  ������ å�� �ε��� (0���� ����)
     *
     * ��ȿ�� �ε��� ����(0 <= index < books.size())�� ���,
     * �ش� ��ġ�� ��Ҹ� books ���Ϳ��� erase �մϴ�.
     * ��� �˻� �� ���� ó�� ������ �����ο��� �߰��� �� �ֽ��ϴ�.
     */
    void removeBook(int index);

    /**
     * @brief �������� å�� �˻�
     *
     * @param title  ã���� �ϴ� å�� ����
     * @return Book* - ������ ��ġ�ϴ� ù ��° Book ������, ������ nullptr
     *
     * books ���͸� ��ȸ�ϸ鼭 getTitle()�� ���Ͽ�
     * ��ġ�ϴ� å�� ��ȯ�մϴ�.
     */
    Book* findBook(const std::string& title) const;

    /**
     * @brief ���� ���� ���� å ��� ��ȯ
     *
     * @return const std::vector<Book*>& - ���� books ���Ϳ� ���� const ����
     *
     * �ܺο��� �κ��丮�� ��� ��� Book �����͸� �б� �������� ������ �� ����մϴ�.
     */
    const std::vector<Book*>& getBooks() const;
};

#endif // INVENTORY_H
