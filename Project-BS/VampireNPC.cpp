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
    borrowed = true;
    inventory.push_back(book);
    book->setAvailable(false);
    return true;
}

Book* VampireNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        ConsoleIO::print(name + "이(가) \"" + b->getTitle() + "\" 책을 조용히 반납합니다.");
        b->setAvailable(true);
        return b;
    }
    return nullptr;
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
    ConsoleIO::print("현재 책 보유 여부: " + std::string(borrowed ? "예" : "아니오"));
    if (!inventory.empty()) {
        ConsoleIO::print("보유한 책 수: " + std::to_string(inventory.size()));
        ConsoleIO::print("마지막 책 제목: " + inventory.back()->getTitle());
    }
    ConsoleIO::print("===============================");
}
