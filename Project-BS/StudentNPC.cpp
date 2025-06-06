#include "StudentNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

bool StudentNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print("학생이 책의 교육적 가치를 평가합니다.");
    return true;
}

bool StudentNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 빌립니다.");
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* StudentNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 반납합니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool StudentNPC::isReturningBook() const {
    return currentBook ? true : false;  // 책을 빌렸는지 확인
}

bool StudentNPC::wantsRecommendation() const {
    return currentBook ? true : false;  // 책을 빌리지 않은 경우 추천을 원함
}

void StudentNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print("학생이 책 손상에 대해 5골드로 보상합니다.");
    gold -= 5;
}

void StudentNPC::debugPrint() const {
    ConsoleIO::print("=== 학생 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("마력 수치: " + std::to_string(magicPower));
    ConsoleIO::print("책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    ConsoleIO::print("현재 책: " + (currentBook ? currentBook->getTitle() : "없음"));
    ConsoleIO::print("===========================");
}

int StudentNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 아껴둔 용돈 중 " + std::to_string(paid) + " 골드를 지불합니다.");
    return paid;
}

int StudentNPC::payMagicPower(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < magicPower) ? amount : magicPower;
    magicPower -= paid;

    ConsoleIO::print(name + "이(가) 시험 공부로 " + std::to_string(paid) + " 마력을 소모합니다.");
    return paid;
}

int StudentNPC::payExp(int amount) {
    // 학생은 아직 성장 중이라 경험치를 소모하지 않고 축적만 한다고 가정
    ConsoleIO::print(name + "은(는) 아직 경험치를 지급 할 수 있는 나이가 아닙니다.");
    return 0;
}
