#include "VampireNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

bool VampireNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print("뱀파이어는 어두운 분위기의 책을 좋아합니다.");

    if (book->getMood() == preferredMood && preferredMood == eBookMood::Dark) {
        ConsoleIO::print("이 책은 나의 어두운 영혼을 만족시켜주는군요...");
        return true;
    }
    else {
        ConsoleIO::print("이 책은 내 취향이 아닙니다.");
        return false;
    }
}

bool VampireNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 밤의 장막 속으로 빌려갑니다.");
    Book* b = currentBook;
    book->setAvailable(false);
    return true;
}

Book* VampireNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 조용히 반납합니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool VampireNPC::isReturningBook() const {
    return true;  // 항상 반납
}

bool VampireNPC::wantsRecommendation() const {
    return true;  // 추천을 원함
}

void VampireNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print("뱀파이어가 피의 계약서로 보상합니다. (골드 -5)");
    gold -= 5;
}

void VampireNPC::debugPrint() const {
    ConsoleIO::print("=== 뱀파이어 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("현재 책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    ConsoleIO::print("현재 책 제목: " + (currentBook ? currentBook->getTitle() : "없음"));
    ConsoleIO::print("===============================");
}

int VampireNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 인간 세계의 관습에 따라 " + std::to_string(paid) + " 골드를 지불합니다.");
    return paid;
}

int VampireNPC::payMagicPower(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < magicPower) ? amount : magicPower;
    magicPower -= paid;

    ConsoleIO::print(name + "이(가) 피의 주문으로 " + std::to_string(paid) + " 마력을 소모합니다.");
    return paid;
}

int VampireNPC::payExp(int amount) {
    if (amount <= 0) return 0;

    ConsoleIO::print(name + "이(가) 고대의 지식을 끌어내기 위해 " + std::to_string(amount) + " 경험치를 희생합니다.");
    return amount; // 그대로 지불
}
