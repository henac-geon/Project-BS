#include "AINPC.h"
#include <iostream>
#include <cstdlib>


// 추천된 책 평가
int AINPC::rateBook(Book* book) const {
    if (!book) return 0;

    int matchCount = 0;

    // 5가지 요소 각각 비교
    if (book->getGenre() == preferredGenre) ++matchCount;
    if (book->getMood() == preferredMood) ++matchCount;
    if (book->getLength() == preferredLength) ++matchCount;
    if (book->getEdge() == preferredEdge) ++matchCount;
    if (book->getEtc() == preferredEtc) ++matchCount;

    return matchCount;
}


bool AINPC::borrowBook(Book* book) {
    if (currentBook) return false;
    currentBook = book;
    return true;
}

Book* AINPC::returnBook() {
    if (!currentBook) return nullptr;
    Book* book = currentBook;
    currentBook = nullptr;
    return book;
}

bool AINPC::isReturningBook() const {
    return currentBook && (rand() % 10 < 8); // 80%
}

bool AINPC::wantsRecommendation() const {
    return !currentBook && (rand() % 10 < 9); // 90%
}

int AINPC::payGold(int amount) {
    int paid = (amount == 0) ? (gold / 10) : ((gold < amount) ? gold : amount);
    gold -= paid;
    return paid;
}

int AINPC::payMagicPower(int amount) {
    int paid = (amount == 0) ? (magicPower / 5) : ((magicPower < amount) ? magicPower : amount);
    magicPower -= paid;
    return paid;
}

int AINPC::payExp(int amount) {
    int gained = (amount == 0) ? 10 : amount;
    experience += gained;
    return gained;
}

void AINPC::compensateForDamage(Book* book) {
    int compensation = 5;
    gold = (gold < compensation) ? 0 : (gold - compensation);
    std::cout << "[AI NPC] 책 손상으로 " << compensation << " 골드를 보상했습니다.\n";
}
void AINPC::debugPrint() const {
    std::cout << "===== AI NPC DEBUG INFO =====\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Gold: " << gold << ", MagicPower: " << magicPower << ", Exp: " << experience << "\n";
    std::cout << "Preferred Genre: " << static_cast<int>(preferredGenre)
        << ", Mood: " << static_cast<int>(preferredMood) << "\n";
    std::cout << "Dialogues:\n";
    for (const auto& line : dialogues) {
        std::cout << "  - " << line << "\n";
    }
    std::cout << "=============================\n";
}

void AINPC::setExperience(int exp) {
    experience = exp;
}

int AINPC::getExperience() const {
    return experience;
}
