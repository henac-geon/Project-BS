#include "Inventory.h"        // Inventory 클래스 정의 헤더 포함
#include <algorithm>             // std::find_if 사용을 위한 알고리즘 헤더

/**
 * @brief 인벤토리에 책을 추가하는 함수
 *
 * @param book  추가할 Book 객체의 포인터
 *
 * books 벡터의 끝에 전달받은 book 포인터를 push_back 하여 인벤토리에 추가합니다.
 */
void Inventory::addBook(Book* book) {
    books.push_back(book);
}

/**
 * @brief 지정한 인덱스의 책을 인벤토리에서 제거하는 함수
 *
 * @param index  제거할 책의 0부터 시작하는 인덱스
 *
 * index가 0 이상 books.size() 미만인지 확인한 후,
 * 유효한 인덱스일 경우 해당 위치의 요소를 erase 합니다.
 */
void Inventory::removeBook(int index) {
    if (index >= 0 && index < static_cast<int>(books.size())) {
        books.erase(books.begin() + index);
    }
}

/**
 * @brief 제목을 기준으로 책을 검색하는 함수
 *
 * @param title  찾고자 하는 책의 제목
 * @return Book* - 제목이 일치하는 첫 번째 Book 포인터 (없으면 nullptr)
 *
 * std::find_if와 람다를 사용하여 books 벡터를 순회하며,
 * getTitle()이 전달된 title과 일치하는지 검사합니다.
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
 * @brief 현재 인벤토리에 보유 중인 책 목록을 반환하는 함수
 *
 * @return const std::vector<Book*>& - 내부 books 벡터에 대한 const 참조
 *
 * 외부에서 인벤토리에 담긴 모든 Book 포인터를 읽기 전용으로 접근할 때 사용합니다.
 */
const std::vector<Book*>& Inventory::getBooks() const {
    return books;
}


void Inventory::removeBook(Book* book) {
    books.erase(std::remove(books.begin(), books.end(), book), books.end());
    delete book; // 소각 처리
}
