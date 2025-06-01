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
    borrowed = true;
    inventory.push_back(book);
    book->setAvailable(false);
    return true;
}

Book* StudentNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        ConsoleIO::print(name + "이(가) \"" + b->getTitle() + "\" 책을 반납합니다.");
        b->setAvailable(true);
        return b;
    }
    return nullptr;
}

bool StudentNPC::isReturningBook() const {
    return borrowed;  // 책을 빌렸으면 반납
}

bool StudentNPC::wantsRecommendation() const {
    return !borrowed;  // 책을 빌리지 않은 경우 추천을 원함
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
    ConsoleIO::print("책 보유 여부: " + std::string(borrowed ? "예" : "아니오"));
    if (!inventory.empty()) {
        ConsoleIO::print("보유한 책 수: " + std::to_string(inventory.size()));
        ConsoleIO::print("마지막 책 제목: " + inventory.back()->getTitle());
    }
    ConsoleIO::print("===========================");
}
