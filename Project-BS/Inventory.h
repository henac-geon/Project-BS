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
    void addBook(Book* book);
    bool safeRemoveBook(int index);
    Book* findBook(const std::string& title) const;
    const std::vector<Book*>& getBooks() const;
    void removeBook(Book* book);
    bool attemptToRestoreDamagedBook(Book* book, MiniGame* game);
};

#endif // INVENTORY_H
