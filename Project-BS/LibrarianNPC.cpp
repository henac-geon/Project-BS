#include "LibrarianNPC.h"
#include "Book.h"
#include <iostream>

bool LibrarianNPC::rateBook(Book* book) const {
    if (!book) return false;

    std::cout << name << " is rating the book...\n";

    // 장르와 무드가 일치할수록 높은 평가
    if (book->getGenre() == preferredGenre && book->getMood() == preferredMood) {
        std::cout << "This book is a perfect match for me!" << std::endl;
        return true;
    }
    else if (book->getGenre() == preferredGenre || book->getMood() == preferredMood) {
        std::cout << "This book is decent." << std::endl;
        return true;
    }
    else {
        std::cout << "Not quite my type..." << std::endl;
        return false;
    }
}

bool LibrarianNPC::borrowBook(Book* book) {
    if (!book) return false;

    std::cout << name << " is borrowing the book titled \"" << book->getTitle() << "\".\n";
    hasBook = true;
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* LibrarianNPC::returnBook() {
    if (!hasBook || !currentBook) return nullptr;

    std::cout << name << " is returning the book titled \"" << currentBook->getTitle() << "\".\n";
    currentBook->setAvailable(true);
    hasBook = false;
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool LibrarianNPC::isReturningBook() const {
    // 단순히 확률 기반으로 반환 여부 결정
    return hasBook && (rand() % 2 == 0);
}

bool LibrarianNPC::wantsRecommendation() const {
    // 사서 NPC는 대부분 추천을 원하지 않음
    return false;
}

void LibrarianNPC::compensateForDamage(Book* book) {
    if (!book) return;

    int damageCost = book->getConditionValue() * 2; // 예: 피해 정도 * 2골드
    std::cout << name << " is compensating " << damageCost << " gold for the damaged book.\n";
    gold -= damageCost;
}

void LibrarianNPC::debugPrint() const {
    std::cout << "=== Librarian NPC Debug Info ===\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Preferred Genre: " << static_cast<int>(preferredGenre) << "\n";
    std::cout << "Preferred Mood: " << static_cast<int>(preferredMood) << "\n";
    std::cout << "Gold: " << gold << "\n";
    //std::cout << "MP: " << mp << "\n";
    std::cout << "Currently Holding Book: " << (hasBook ? "Yes" : "No") << "\n";
    if (currentBook) {
        std::cout << "Book Title: " << currentBook->getTitle() << "\n";
    }
    std::cout << "===============================\n";
}
