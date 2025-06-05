#include "ElfScholarNPC.h"
#include "ConsoleIO.h"  // 새로 추가
#include <cstdlib>      // rand()

bool ElfScholarNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) 책의 문학적 깊이를 평가합니다...");

    if (book->getMood() == preferredMood) {
        ConsoleIO::print("이 책은 엘프의 영혼에 완벽히 울려 퍼집니다.");
        return true;
    }
    else {
        ConsoleIO::print("이 책은 엘프의 감성에 부족합니다.");
        return false;
    }
}

bool ElfScholarNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 조심스럽게 빌립니다.");
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* ElfScholarNPC::returnBook() {
    if (!currentBook) return nullptr;

    ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책을 정중하게 반납합니다.");
    currentBook->setAvailable(true);
    Book* returned = currentBook;
    currentBook = nullptr;
    return returned;
}

bool ElfScholarNPC::isReturningBook() const {
    return currentBook ? true : false;  // 엘프는 항상 반납함
}

bool ElfScholarNPC::wantsRecommendation() const {
    return preferredMood == eBookMood::Whimsical;
}

void ElfScholarNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print(name + "이(가) 희귀한 약초로 손상된 책을 보상합니다.");
    gold -= 3;
}

void ElfScholarNPC::debugPrint() const {
    ConsoleIO::print("=== 엘프 학자 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("선호 장르: " + std::to_string(static_cast<int>(preferredGenre)));
    ConsoleIO::print("선호 분위기: " + std::to_string(static_cast<int>(preferredMood)));
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("마력 수치: " + std::to_string(magicPower));
    ConsoleIO::print("현재 책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    if (currentBook) {
        ConsoleIO::print("책 제목: " + currentBook->getTitle());
    }
    ConsoleIO::print("===============================");
}

int ElfScholarNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < gold) ? amount : gold;
    gold -= paid;

    ConsoleIO::print(name + "이(가) " + std::to_string(paid) + " 골드를 정중하게 지불합니다.");
    return paid;
}

int ElfScholarNPC::payMagicPower(int amount) {
    if (amount <= 0) return 0;

    int paid = (amount < magicPower) ? amount : magicPower;
    magicPower -= paid;

    ConsoleIO::print(name + "의 마법 기운이 " + std::to_string(paid) + "만큼 소모되었습니다.");
    return paid;
}

int ElfScholarNPC::payExp(int amount) {
    // 엘프는 경험치를 소모하지 않고, 지식의 축적만을 추구한다고 가정
    ConsoleIO::print(name + "은(는) 경험치를 소모하는 대신, 명상으로 지혜를 얻습니다.");
    return 0; // 경험치 소모하지 않음
}
