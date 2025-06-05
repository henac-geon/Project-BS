#include "LibrarianNPC.h"
#include "Book.h"
#include "ConsoleIO.h"  // 추가
#include <cstdlib>      // rand()

bool LibrarianNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) 책을 평가하고 있습니다...");

    // 장르와 무드가 일치할수록 높은 평가
    if (book->getGenre() == preferredGenre && book->getMood() == preferredMood) {
        ConsoleIO::print("이 책은 저에게 완벽하게 어울립니다!");
        return true;
    }
    else if (book->getGenre() == preferredGenre || book->getMood() == preferredMood) {
        ConsoleIO::print("이 책도 나쁘지 않네요.");
        return true;
    }
    else {
        ConsoleIO::print("제 취향은 아닌 것 같습니다...");
        return false;
    }
}

bool LibrarianNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 대여합니다.");
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* LibrarianNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 반납합니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool LibrarianNPC::isReturningBook() const {
    return currentBook && (rand() % 2 == 0);
}

bool LibrarianNPC::wantsRecommendation() const {
    return false;  // 사서는 보통 추천을 원하지 않음
}

void LibrarianNPC::compensateForDamage(Book* book) {
    if (!book) return;

    int damageCost = book->getConditionValue() * 2;
    ConsoleIO::print(name + "이(가) 손상된 책에 대해 " + std::to_string(damageCost) + " 골드를 보상합니다.");
    gold -= damageCost;
}

void LibrarianNPC::debugPrint() const {
    ConsoleIO::print("=== 사서 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("선호 장르: " + std::to_string(static_cast<int>(preferredGenre)));
    ConsoleIO::print("선호 분위기: " + std::to_string(static_cast<int>(preferredMood)));
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("마력 수치: " + std::to_string(magicPower));
    ConsoleIO::print("현재 책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    if (currentBook) {
        ConsoleIO::print("현재 대여 중인 책: " + currentBook->getTitle());
    } else {
        ConsoleIO::print("현재 대여 중인 책: 없음");
    }
    ConsoleIO::print("===============================");
}


int LibrarianNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 도서관 운영비로 " + std::to_string(paid) + " 골드를 차감합니다.");
    return paid;
}

int LibrarianNPC::payMagicPower(int amount) {
    if (amount <= 0) return 0;

    // 사서는 마법을 통해 책을 보존하거나 복원한다고 가정
    int paid = (amount < magicPower) ? amount : magicPower;
    magicPower -= paid;

    ConsoleIO::print(name + "이(가) 고대 마법으로 " + std::to_string(paid) + "의 마력을 사용합니다.");
    return paid;
}

int LibrarianNPC::payExp(int amount) {
    // 사서는 경험치를 소모하여 서고 관리 기술을 습득하는 것으로 해석
    if (amount <= 0) return 0;

    ConsoleIO::print(name + "이(가) 기록 관리 향상을 위해 " + std::to_string(amount) + " 경험치를 소모합니다.");
    return amount;
}
