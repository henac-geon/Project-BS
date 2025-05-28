#include "NPC.h"
#include <iostream>
#include <cstdlib>

NPC::NPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name),
    isMale(isMale),
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
    dialogues = { "오늘은 뭔가 끌리는 책이 있을까요?" };
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

// 책 손상에 대한 보상 처리
void NPC::compensateForDamage(Book* book) {
}


// Getters/Setters
eRequestType NPC::getRequestType() const { return requestType; }
void NPC::setRequestType(eRequestType type) { requestType = type; }

void NPC::setDialogues(const std::vector<std::string>& lines) {
    dialogues = lines;
}

const std::vector<std::string>& NPC::getDialogues() const {
    return dialogues;
}

// 성별에 따라 아트 반환
std::string NPC::getArt() const {
    return isMale ? AsciiArt::showMaleNPCArt() : AsciiArt::showFemaleNPCArt();  // 성별에 따라 아트 반환
}


// 디버깅용 출력 함수
void NPC::debugPrint() const {
    std::cout << "===== NPC DEBUG INFO =====" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Preferred Genre: " << static_cast<int>(preferredGenre) << std::endl;
    std::cout << "Preferred Mood: " << static_cast<int>(preferredMood) << std::endl;
    std::cout << "Request Type: " << static_cast<int>(requestType) << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Magic Power: " << magicPower << std::endl;
    std::cout << "Has Borrowed: " << (borrowed ? "Yes" : "No") << std::endl;
    std::cout << "Inventory Size: " << inventory.size() << std::endl;

    std::cout << "Dialogues:" << std::endl;
    for (size_t i = 0; i < dialogues.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << dialogues[i] << std::endl;
    }

    std::cout << "==========================" << std::endl;
}

