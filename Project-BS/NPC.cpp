#include "NPC.h"
#include "AsciiArtRepository.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

// 생성자: NPC 속성 초기화 및 랜덤 요청 타입 설정
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
    // 요청 타입 무작위 설정
    int r = rand() % 3;
    switch (r) {
    case 0: requestType = eRequestType::GenreOnly; break;
    case 1: requestType = eRequestType::MoodOnly; break;
    case 2: requestType = eRequestType::GenreAndMood; break;
    }

    // 기본 대사 설정
    dialogues = { "오늘은 뭔가 끌리는 책이 있을까요?" };
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
    if (!book || borrowed) return false;
    inventory.push_back(book);
    borrowed = true;
    return true;
}

// 책 반환
Book* NPC::returnBook() {
    if (!borrowed || inventory.empty()) return nullptr;

    Book* book = inventory.back();
    inventory.pop_back();
    borrowed = false;
    return book;
}

// 책 반납 여부 결정 (50% 확률)
bool NPC::isReturningBook() const {
    return borrowed && (rand() % 2 == 0);
}

// 추천 요청 여부 결정 (책 미보유 + 50% 확률)
bool NPC::wantsRecommendation() const {
    return !borrowed && (rand() % 2 == 0);
}

/////////////////////////////
// 골드/경험치 관련 메서드
/////////////////////////////

// 골드 차감
void NPC::payGold(int amount) {
    gold = ((gold - amount) < 0) ? 0 : (gold - amount);
}

// 경험치(마법력) 증가
void NPC::gainExp(int amount) {
    magicPower += amount;
}

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

Book* NPC::getCurrentBook() const {
    return currentBook;
}

bool NPC::isHoldingBook() const {
    return hasBook;
}

const std::vector<Book*>& NPC::getInventory() const {
    return inventory;
}

bool NPC::hasBookInInventory(const Book* book) const {
    return std::find(inventory.begin(), inventory.end(), book) != inventory.end();
}

bool NPC::hasBorrowed() const {
    return borrowed;
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
void NPC::removeBookFromInventory(Book* book) {
    auto it = std::find(inventory.begin(), inventory.end(), book);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
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
    std::cout << "Has Borrowed: " << (borrowed ? "Yes" : "No") << std::endl;
    std::cout << "Inventory Size: " << inventory.size() << std::endl;
    std::cout << "Dialogues:" << std::endl;
    for (size_t i = 0; i < dialogues.size(); ++i) {
        std::cout << "  [" << i + 1 << "] " << dialogues[i] << std::endl;
    }
    std::cout << "==========================" << std::endl;
}
