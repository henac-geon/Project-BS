#include "NPC.h"
#include "AsciiArtRepository.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

// 생성자: NPC 속성 초기화 및 랜덤 요청 타입 설정
NPC::NPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int gold, int magicPower, const std::vector<std::string>& dialogues)
    : name(name),
    isMale(isMale),
    preferredGenre(genre),
    preferredMood(mood),
    gold(gold),
    magicPower(magicPower),
    requestType(eRequestType::GenreOnly),
    dialogues(dialogues)
{
    // 요청 타입 무작위 설정
    int r = rand() % 3;
    switch (r) {
    case 0: requestType = eRequestType::GenreOnly; break;
    case 1: requestType = eRequestType::MoodOnly; break;
    case 2: requestType = eRequestType::GenreAndMood; break;
    }
}

/////////////////////////////
// 평가/대여/반환 관련 메서드
/////////////////////////////

// 추천된 책 평가
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

// 책 대여 시도
bool NPC::borrowBook(Book* book) {
    if (currentBook) return false;
    currentBook = book;
    return true;
}

// 책 반환
Book* NPC::returnBook() {
    if (!currentBook) return nullptr;

    Book* book = currentBook;
    currentBook = nullptr;
    return book;
}

// 책 반납 여부 결정 (80% 확률)
bool NPC::isReturningBook() const {
    return currentBook && (rand() % 10 < 8);
}

// 추천 요청 여부 결정 (책 미보유 + 90% 확률)
bool NPC::wantsRecommendation() const {
    return !currentBook && (rand() % 10 < 9);
}

/////////////////////////////
// 골드/경험치 관련 메서드
/////////////////////////////

// 책 손상 보상 처리 (기본 미구현)
void NPC::compensateForDamage(Book* book) {
    std::cout << "[주의] 이 NPC는 기본 보상 로직이 구현되지 않았습니다." << std::endl;
}

/////////////////////////////
// Getter
/////////////////////////////

std::string NPC::getName() const {
    return name;
}

bool NPC::getIsMale() const {
    return isMale;
}

eBookGenre NPC::getPreferredGenre() const {
    return preferredGenre;
}

eBookMood NPC::getPreferredMood() const {
    return preferredMood;
}

int NPC::getGold() const {
    return gold;
}

int NPC::getMagicPower() const {
    return magicPower;
}

eRequestType NPC::getRequestType() const {
    return requestType;
}

bool NPC::hasBorrowed() const {
    return currentBook ? true : false;
}

/////////////////////////////
// Setter
/////////////////////////////

void NPC::setGold(int amount) {
    gold = (amount < 0) ? 0 : amount;
}

void NPC::setMagicPower(int amount) {
    magicPower = (amount < 0) ? 0 : amount;
}

void NPC::setRequestType(eRequestType type) {
    requestType = type;
}

void NPC::setDialogues(const std::vector<std::string>& lines) {
    dialogues = lines;
}

/////////////////////////////
// 기타 유틸리티
/////////////////////////////

// 책 제거
void NPC::removeBook(Book* book) {
    currentBook = nullptr;
}

// 아트 반환
std::string NPC::getArt() const {
    return isMale ? AsciiArt::showMaleNPCArt() : AsciiArt::showFemaleNPCArt();
}

// 대사 반환
const std::vector<std::string>& NPC::getDialogues() const {
    return dialogues;
}

// 디버깅 정보 출력
void NPC::debugPrint() const {
    std::cout << "===== NPC DEBUG INFO =====" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Preferred Genre: " << static_cast<int>(preferredGenre) << std::endl;
    std::cout << "Preferred Mood: " << static_cast<int>(preferredMood) << std::endl;
    std::cout << "Request Type: " << static_cast<int>(requestType) << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Magic Power: " << magicPower << std::endl;
    std::cout << "Has Borrowed: " << (currentBook ? "Yes" : "No") << std::endl;
    std::cout << "Dialogues:" << std::endl;
    for (size_t i = 0; i < dialogues.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << dialogues[i] << std::endl;
    }
    std::cout << "==========================" << std::endl;
}
