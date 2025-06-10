#include "WizardNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

// TODO: 아 이거 ai서서 더 자연스럽게 하고 싶은데...
int WizardNPC::rateBook(Book* book) const {
    if (!book) return 0;

    ConsoleIO::print("마법사가 책의 기운을 점치고 있습니다...");

    int matchCount = 0;

    bool genreMatch = book->getGenre() == preferredGenre;
    bool moodMatch = book->getMood() == preferredMood;
    bool isMagicalGenre = book->getGenre() == eBookGenre::Fantasy || book->getGenre() == eBookGenre::Mystery;
    bool lengthMatch = book->getLength() == preferredLength;
    bool edgeMatch = book->getEdge() == preferredEdge;
    bool etcMatch = book->getEtc() == preferredEtc;

    switch (requestType) {
    case eRequestType::GenreOnly:
        if (genreMatch || isMagicalGenre) {
            ConsoleIO::print("이 장르는 마법의 흐름과 공명합니다... 좋아요.");
            matchCount += 2;
        }
        else {
            ConsoleIO::print("지식은 있으나, 마법적 울림은 약하군요.");
        }
        break;

    case eRequestType::MoodOnly:
        if (moodMatch) {
            ConsoleIO::print("이 분위기 속에 마력이 흐르고 있어요. 흐음... 괜찮군.");
            matchCount += 2;
        }
        else {
            ConsoleIO::print("감정의 떨림이 부족하군요. 마법은 감정과 함께 흐르니까요.");
        }
        break;

    case eRequestType::GenreAndMood:
        if ((genreMatch || isMagicalGenre) && moodMatch) {
            ConsoleIO::print("이 책은 마법진 하나 없이도 강력한 기운을 품고 있군요. 훌륭합니다.");
            matchCount += 3;
        }
        else if (genreMatch || moodMatch || isMagicalGenre) {
            ConsoleIO::print("부분적으로는 기운이 느껴지나... 아직 완전하진 않습니다.");
            matchCount += 1;
        }
        else {
            ConsoleIO::print("이 책은 마법과는 인연이 없군요.");
        }
        break;

    case eRequestType::AnyBook:
        ConsoleIO::print("책이란 곧 주문서. 무엇이든 배움의 씨앗이 될 수 있지요.");
        if (genreMatch || isMagicalGenre) matchCount += 1;
        if (moodMatch) matchCount += 1;
        break;
    }

    // 보조 취향 요소는 항상 반영
    if (lengthMatch) matchCount += 1;
    if (edgeMatch)   matchCount += 1;
    if (etcMatch)    matchCount += 1;

    return matchCount;
}



bool WizardNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 조심스럽게 대출합니다.");
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* WizardNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 되돌려 놓습니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool WizardNPC::isReturningBook() const {
    return (currentBook != nullptr) && (magicPower % 2 == 0);
}


bool WizardNPC::wantsRecommendation() const {
    return magicPower > 50;  // 마력이 높을수록 새로운 지식을 갈망함
}

void WizardNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print("마법사가 손상된 책을 마법으로 수리하려 했지만... 실패했습니다.");
    ConsoleIO::print("보상으로 10골드를 지불합니다.");
    gold -= 10;
}

void WizardNPC::debugPrint() const {
    ConsoleIO::print("=== 마법사 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("마력: " + std::to_string(magicPower));
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    ConsoleIO::print("현재 책: " + (currentBook ? currentBook->getTitle() : "없음"));
    ConsoleIO::print("==============================");
}

int WizardNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 마법 상회에 " + std::to_string(paid) + " 골드를 전달합니다.");
    return paid;
}

int WizardNPC::payMagicPower(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < magicPower) ? amount : magicPower;
    magicPower -= paid;

    ConsoleIO::print(name + "이(가) 주문을 위해 " + std::to_string(paid) + "의 마력을 방출합니다.");
    return paid;
}

int WizardNPC::payExp(int amount) {
    if (amount <= 0) return 0;

    ConsoleIO::print(name + "이(가) 고대 주문을 완성하기 위해 " + std::to_string(amount) + " 경험치를 소모합니다.");
    return amount;
}
