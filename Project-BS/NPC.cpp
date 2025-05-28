#include "NPC.h"
#include <iostream>

NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name),
    preferredGenre(genre),
    preferredMood(mood),
    gold(gold),
    magicPower(magicPower),
    borrowed(false)
{
}

// 책을 추천받았을 때 선호와 비교
bool NPC::rateBook(Book* book) const {
    if (!book) return false;

    switch (requestType) {
    case eRequestType::GenreOnly:
        return book->getGenre() == preferredGenre;
    case eRequestType::MoodOnly:
        return book->getMood() == preferredMood;
    case eRequestType::GenreAndMood:
        return book->getGenre() == preferredGenre && book->getMood() == preferredMood;
    case eRequestType::AnyBook:
        return true;
    }
    return false;
}

// 책 빌리기
bool NPC::borrowBook(Book* book) {
    if (!book || borrowed) return false;

    inventory.push_back(book);
    borrowed = true;
    return true;
}

// 책 반납하기
Book* NPC::returnBook() {
    if (!borrowed || inventory.empty()) return nullptr;

    Book* book = inventory.back();
    inventory.pop_back();
    borrowed = false;
    return book;
}

bool NPC::hasBorrowed() const {
    return borrowed;
}

// 골드 지불
void NPC::payGold(int amount) {
    gold = std::max(0, gold - amount);
}

// 경험치 증가
void NPC::gainExp(int amount) {
    magicPower += amount;
}

// Getters/Setters
std::string NPC::getName() const { return name; }
void NPC::setName(const std::string& newName) { name = newName; }

eBookGenre NPC::getPreferredGenre() const { return preferredGenre; }
void NPC::setPreferredGenre(eBookGenre genre) { preferredGenre = genre; }

eBookMood NPC::getPreferredMood() const { return preferredMood; }
void NPC::setPreferredMood(eBookMood mood) { preferredMood = mood; }

const std::vector<Book*>& NPC::getInventory() const { return inventory; }

int NPC::getGold() const { return gold; }
void NPC::setGold(int newGold) { gold = newGold; }

int NPC::getMagicPower() const { return magicPower; }
void NPC::setMagicPower(int newMagicPower) { magicPower = newMagicPower; }

eRequestType NPC::getRequestType() const { return requestType; }
void NPC::setRequestType(eRequestType type) { requestType = type; }

std::string NPC::getDialogue() const { return dialogue; }
void NPC::setDialogue(const std::string& line) { dialogue = line; }

std::string NPC::getArt() const {
    return AsciiArt::showFemaleNPCArt();  // 기본값
}
