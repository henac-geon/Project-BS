#include "npc.h"
#include <iostream>
#include <cstdlib>

NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name),
    preferredGenre(genre),
    preferredMood(mood),
    gold(gold),
    magicPower(magicPower),
    requestType(eRequestType::GenreOnly),
    borrowed(false)
{
    // 무작위 요청 유형 할당
    int r = rand() % 3;
    switch (r) {
    case 0: requestType = eRequestType::GenreOnly; break;
    case 1: requestType = eRequestType::MoodOnly; break;
    case 2: requestType = eRequestType::GenreAndMood; break;
    }

    // 대사 설정
    dialogue = "오늘은 뭔가 끌리는 책이 있을까요?";
}

// 책을 추천받았을 때 만족 여부 판단
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

// 책 대여
bool NPC::borrowBook(Book* book) {
    if (!book || borrowed) return false;
    inventory.push_back(book);
    borrowed = true;
    return true;
}

// 책 반납
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

// NPC가 오늘 반납할 의사가 있는지?
bool NPC::isReturningBook() const {
    return borrowed && (rand() % 2 == 0);  // 대여했고 50% 확률로 반납
}

// 추천받을 의사가 있는지?
bool NPC::wantsRecommendation() const {
    return !borrowed && (rand() % 2 == 0); // 책이 없고 50% 확률로 추천 요청
}

// 재화 처리
void NPC::payGold(int amount) {
    gold = std::max(0, gold - amount);
}

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
    return AsciiArt::showFemaleNPCArt();  // 현재 기본값
}
