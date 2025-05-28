#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>    // std::vector 사용을 위한 헤더
#include <string>    // std::string 사용을 위한 헤더
#include "Book.h"   // Book 클래스 정의 포함
#include "MiniGame.h"
#include "TypingGame.h"
#include "ReactionGame.h"

/**
 * @class Inventory
 * @brief 책(Book) 객체를 관리하는 인벤토리 클래스
 *
 * 책을 추가(addBook), 제거(removeBook), 검색(findBook)하는
 * 기능을 제공하며, 현재 보유 중인 책 목록을 반환(getBooks)합니다.
 */
class Inventory {
private:
    std::vector<Book*> books;  // 인벤토리에 보관된 Book 포인터 목록

public:
    /**
     * @brief 책을 인벤토리에 추가
     *
     * @param book  추가할 Book 객체의 포인터
     *
     * books 벡터의 끝에 전달된 book 포인터를 push_back 합니다.
     */
    void addBook(Book* book);

    /**
     * @brief 인덱스로 책을 인벤토리에서 제거
     *
     * @param index  제거할 책의 인덱스 (0부터 시작)
     *
     * 유효한 인덱스 범위(0 <= index < books.size())인 경우,
     * 해당 위치의 요소를 books 벡터에서 erase 합니다.
     * 경계 검사 및 예외 처리 로직은 구현부에서 추가할 수 있습니다.
     */
    bool safeRemoveBook(int index);

    /**
     * @brief 제목으로 책을 검색
     *
     * @param title  찾고자 하는 책의 제목
     * @return Book* - 제목이 일치하는 첫 번째 Book 포인터, 없으면 nullptr
     *
     * books 벡터를 순회하면서 getTitle()과 비교하여
     * 일치하는 책을 반환합니다.
     */
    Book* findBook(const std::string& title) const;

    /**
     * @brief 현재 보유 중인 책 목록 반환
     *
     * @return const std::vector<Book*>& - 내부 books 벡터에 대한 const 참조
     *
     * 외부에서 인벤토리에 담긴 모든 Book 포인터를 읽기 전용으로 접근할 때 사용합니다.
     */
    const std::vector<Book*>& getBooks() const;

    void removeBook(Book* book);

    bool attemptToRestoreDamagedBook(Book* book, MiniGame* game);
};

#endif // INVENTORY_H
