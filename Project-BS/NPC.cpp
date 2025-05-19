#include "NPC.h"    // NPC 클래스 정의 헤더 포함

/**
 * @brief NPC 클래스 생성자 구현
 *
 * @param name        NPC의 고유 이름
 * @param genre       NPC가 선호하는 책 장르 (Enums.h에 정의된 eBookGenre)
 * @param mood        NPC가 선호하는 책 분위기 (Enums.h에 정의된 eBookMood)
 * @param gold        초기 금화량 (게임 내 경제 시스템에서 사용)
 * @param magicPower  초기 마법력 (특정 상호작용이나 보상 시스템에서 사용)
 *
 * 본 생성자에서는 멤버 초기화 리스트를 사용하여 각 멤버 변수를
 * 전달받은 인수로 간결하고 안전하게 초기화합니다.
 */
NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name), preferredGenre(genre), preferredMood(mood), gold(gold), magicPower(magicPower)
{
    // TODO: 필요 시 초기화 후 추가 로직을 여기에 구현
    // 예: 기본 인벤토리(Book 포인터)를 설정하거나,
    //     초기화 메시지 출력, 통계 증가 등
}

// NPC가 받은 책을 평가하는 함수
bool NPC::rateBook(Book* book) const {
    if (!book) return false;    // 추천 못 받았을 경우

    switch (requestType) {
    case eRequestType::GenreOnly:    // 장르만 추천받는 타입
        return book->getGenre() == this->preferredGenre;
    case eRequestType::MoodOnly:     // 무드만 추천받는 타입
        return book->getMood() == this->preferredMood;
    case eRequestType::GenreAndMood:     // 둘다 추천받는 타입
        return book->getGenre() == this->preferredGenre && book->getMood() == this->preferredMood;
    case eRequestType::AnyBook: // 장르, 무드 상관없이 추천만 받으면 OK
        return true;
    }

    return false;   // 예외
}

/**
* 
* NPC.h에서 만들었던 get 함수와 set 함수 정의
* 
*/

std::string NPC::getName() const {
    return name;
}

void NPC::setName(const std::string& newName) {
    name = newName;
}

eBookGenre NPC::getPreferredGenre() const {
    return preferredGenre;
}

void NPC::setPreferredGenre(eBookGenre genre) {
    preferredGenre = genre;
}

eBookMood NPC::getPreferredMood() const {
    return preferredMood;
}

void NPC::setPreferredMood(eBookMood mood) {
    preferredMood = mood;
}

const std::vector<Book*>& NPC::getInventory() const {
    return inventory;
}

int NPC::getGold() const {
    return gold;
}

void NPC::setGold(int newGold) {
    gold = newGold;
}

int NPC::getMagicPower() const {
    return magicPower;
}

void NPC::setMagicPower(int newMagicPower) {
    magicPower = newMagicPower;
}

eRequestType NPC::getRequestType() const {
    return requestType;
}

void NPC::setRequestType(eRequestType type) {
    requestType = type;
}

std::string NPC::getArt() const {
    // 기본적으로 여성 NPC 아트를 반환하되, 필요시 오버라이드 가능
    return AsciiArt::showFemaleNPCArt(); // 또는 showRandomNPCArt()
}

std::string NPC::getDialogue() const {
    return name + ": 좋은 책 하나 추천해 주실 수 있나요?";
}
