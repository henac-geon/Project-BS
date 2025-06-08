#include "LibrarianNPC.h"
#include "Book.h"
#include "ConsoleIO.h"  // 추가
#include <cstdlib>      // rand()

// TODO: 아 이거 ai서서 더 자연스럽게 하고 싶은데...
bool LibrarianNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) 책을 꼼꼼히 평가하고 있습니다...");

    bool genreMatch = book->getGenre() == preferredGenre;
    bool moodMatch = book->getMood() == preferredMood;

    switch (requestType) {
    case eRequestType::GenreOnly:
        if (genreMatch) {
            ConsoleIO::print("장르가 제 전문 분야와 일치하네요. 인상 깊습니다.");
            return true;
        }
        else {
            ConsoleIO::print("장르가 다소 생소하군요. 연구에는 부적절할 수도 있겠습니다.");
            return false;
        }

    case eRequestType::MoodOnly:
        if (moodMatch) {
            ConsoleIO::print("이 분위기는 읽는 즐거움을 줍니다. 괜찮네요.");
            return true;
        }
        else {
            ConsoleIO::print("분위기가 제 취향과는 조금 다릅니다.");
            return false;
        }

    case eRequestType::GenreAndMood:
        if (genreMatch && moodMatch) {
            ConsoleIO::print("장르와 분위기 모두 제가 선호하는 기준에 완벽하게 부합합니다.");
            return true;
        }
        else if (genreMatch || moodMatch) {
            ConsoleIO::print("부분적으로는 만족스럽지만 완벽하다고 보긴 어렵네요.");
            return true;
        }
        else {
            ConsoleIO::print("이 책은 제 연구 주제와는 관련이 없습니다.");
            return false;
        }

    case eRequestType::AnyBook:
        ConsoleIO::print("모든 책에는 배울 점이 있죠. 긍정적으로 평가하겠습니다.");
        return true;
    }

    return false;
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
