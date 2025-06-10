#include "KnightNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

// TODO: 아 이거 ai서서 더 자연스럽게 하고 싶은데...
int KnightNPC::rateBook(Book* book) const {
    if (!book) return 0;

    ConsoleIO::print(name + "이(가) 책의 명예와 가치를 판단합니다...");

    int matchCount = 0;

    bool genreMatch = book->getGenre() == preferredGenre;
    bool moodMatch = book->getMood() == preferredMood;
    bool lengthMatch = book->getLength() == preferredLength;
    bool edgeMatch = book->getEdge() == preferredEdge;
    bool etcMatch = book->getEtc() == preferredEtc;

    switch (requestType) {
    case eRequestType::GenreOnly:
        if (genreMatch) {
            ConsoleIO::print("이 책은 나의 사명과 완벽히 맞아떨어집니다. 읽을 가치가 있지.");
            matchCount += 1;
        }
        else if (book->getGenre() == eBookGenre::Fantasy) {
            ConsoleIO::print("판타지라면 기사도 정신을 함양하는 데 부족함이 없지.");
            matchCount += 1;
        }
        else {
            ConsoleIO::print("이 장르는 기사의 길과는 거리가 멀다.");
        }
        break;

    case eRequestType::MoodOnly:
        if (moodMatch) {
            ConsoleIO::print("이 책은 내 마음을 불타오르게 만드는군!");
            matchCount += 1;
        }
        else {
            ConsoleIO::print("이런 분위기는 전장에서 도움이 되지 않는다.");
        }
        break;

    case eRequestType::GenreAndMood:
        if (genreMatch && moodMatch) {
            ConsoleIO::print("장르도 분위기도 나의 길에 부합한다. 명예로운 선택이군.");
            matchCount += 2;
        }
        else if (genreMatch || moodMatch) {
            ConsoleIO::print("부분적으로는 괜찮지만, 기사에겐 완전한 일치를 원한다.");
            matchCount += 1;
        }
        else {
            ConsoleIO::print("명예도 감성도 이 책엔 부족하군.");
        }
        break;

    case eRequestType::AnyBook:
        ConsoleIO::print("모든 지식은 검보다 강할 수 있다. 받아들이겠다.");
        if (genreMatch) matchCount += 1;
        if (moodMatch)  matchCount += 1;
        break;
    }

    // 보조 취향 요소는 무조건 반영
    if (lengthMatch) matchCount += 1;
    if (edgeMatch)   matchCount += 1;
    if (etcMatch)    matchCount += 1;

    return matchCount;
}


bool KnightNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 용맹하게 빌립니다.");
    Book* b = currentBook;
    book->setAvailable(false);
    return true;
}

Book* KnightNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 충실히 반납합니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool KnightNPC::isReturningBook() const {
    return currentBook ? true : false;  // 책을 빌렸으면 항상 반납
}

bool KnightNPC::wantsRecommendation() const {
    return true;  // 추천을 선호함
}

void KnightNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print(name + "이(가) 기사답게 손상된 책에 대해 즉시 10골드를 보상합니다.");
    gold -= 10;
}

void KnightNPC::debugPrint() const {
    ConsoleIO::print("=== 기사 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("현재 책 보유 여부: " + std::string(currentBook? "예" : "아니오"));
    ConsoleIO::print("현재 책 제목: " + (currentBook ? currentBook->getTitle() : "없음"));
    ConsoleIO::print("============================");
}

int KnightNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 기사도의 이름으로 " + std::to_string(paid) + " 골드를 지불합니다.");
    return paid;
}

int KnightNPC::payMagicPower(int amount) {
    // 기사는 마법에 능하지 않음 - 마법 포인트가 거의 없음 또는 제한
    ConsoleIO::print(name + "은(는) 마법보다는 검을 믿습니다. 마력은 사용하지 않습니다.");
    return 0;
}

int KnightNPC::payExp(int amount) {
    if (amount <= 0) return 0;

    // 경험치를 명예로운 훈련에 사용
    ConsoleIO::print(name + "이(가) 전투 훈련으로 " + std::to_string(amount) + " 경험치를 사용합니다.");
    return amount; // 단순히 요구한 양만큼 사용했다고 처리
}
