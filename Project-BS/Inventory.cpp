#include "Inventory.h"        // Inventory Ŭ���� ���� ��� ����
#include <algorithm>             // std::find_if ����� ���� �˰��� ���

/**
 * @brief �κ��丮�� å�� �߰��ϴ� �Լ�
 *
 * @param book  �߰��� Book ��ü�� ������
 *
 * books ������ ���� ���޹��� book �����͸� push_back �Ͽ� �κ��丮�� �߰��մϴ�.
 */
void Inventory::addBook(Book* book) {
    books.push_back(book);
}

/**
 * @brief ������ �ε����� å�� �κ��丮���� �����ϴ� �Լ�
 *
 * @param index  ������ å�� 0���� �����ϴ� �ε���
 *
 * index�� 0 �̻� books.size() �̸����� Ȯ���� ��,
 * ��ȿ�� �ε����� ��� �ش� ��ġ�� ��Ҹ� erase �մϴ�.
 */
void Inventory::removeBook(int index) {
    if (index >= 0 && index < static_cast<int>(books.size())) {
        books.erase(books.begin() + index);
    }
}

/**
 * @brief ������ �������� å�� �˻��ϴ� �Լ�
 *
 * @param title  ã���� �ϴ� å�� ����
 * @return Book* - ������ ��ġ�ϴ� ù ��° Book ������ (������ nullptr)
 *
 * std::find_if�� ���ٸ� ����Ͽ� books ���͸� ��ȸ�ϸ�,
 * getTitle()�� ���޵� title�� ��ġ�ϴ��� �˻��մϴ�.
 */
Book* Inventory::findBook(const std::string& title) const {
    auto it = std::find_if(books.begin(), books.end(), [&](Book* b) {
        return b->getTitle() == title;
        });
    if (it != books.end()) {
        return *it;
    }
    return nullptr;
}

/**
 * @brief ���� �κ��丮�� ���� ���� å ����� ��ȯ�ϴ� �Լ�
 *
 * @return const std::vector<Book*>& - ���� books ���Ϳ� ���� const ����
 *
 * �ܺο��� �κ��丮�� ��� ��� Book �����͸� �б� �������� ������ �� ����մϴ�.
 */
const std::vector<Book*>& Inventory::getBooks() const {
    return books;
}