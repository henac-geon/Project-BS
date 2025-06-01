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
    else if (book->getGenre() == eBookGenre::Fantasy || book->getGenre() == eBookGenre::NonFiction) {
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
    borrowed = true;
    inventory.push_back(book);
    book->setAvailable(false);
    return true;
}

Book* KnightNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        ConsoleIO::print(name + "이(가) \"" + b->getTitle() + "\" 책을 충실히 반납합니다.");
        b->setAvailable(true);
        return b;
    }
    return nullptr;
}

bool KnightNPC::isReturningBook() const {
    return true;  // 항상 책을 반납
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
    ConsoleIO::print("현재 책 보유 여부: " + std::string(borrowed ? "예" : "아니오"));
    if (!inventory.empty()) {
        ConsoleIO::print("보유한 책 수: " + std::to_string(inventory.size()));
        ConsoleIO::print("마지막 책 제목: " + inventory.back()->getTitle());
    }
    ConsoleIO::print("============================");
}
