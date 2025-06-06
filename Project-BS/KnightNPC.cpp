#include "KnightNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

bool KnightNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) 책의 가치와 명예를 평가합니다...");

    if (book->getGenre() == preferredGenre) {
        ConsoleIO::print("이 책은 나의 사명과 잘 어울립니다!");
        return true;
    }
    else if (book->getGenre() == eBookGenre::Fantasy) {
        ConsoleIO::print("이 장르는 기사 정신에 부합합니다.");
        return true;
    }
    else {
        ConsoleIO::print("기사가 읽기에는 적절치 않습니다.");
        return false;
    }
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
