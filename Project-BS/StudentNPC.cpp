#include "StudentNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

// TODO: 아 이거 ai서서 더 자연스럽게 하고 싶은데...
bool StudentNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print("학생이 책의 교육적 가치와 흥미도를 판단합니다...");

    bool genreMatch = book->getGenre() == preferredGenre;
    bool moodMatch = book->getMood() == preferredMood;

    switch (requestType) {
    case eRequestType::GenreOnly:
        if (genreMatch) {
            ConsoleIO::print("이 장르는 제가 좋아하는 과목과 관련이 있어요! 공부에 도움 되겠네요.");
            return true;
        }
        else {
            ConsoleIO::print("음... 과제랑은 관련 없지만 재미는 있을지도?");
            return true;
        }

    case eRequestType::MoodOnly:
        if (moodMatch) {
            ConsoleIO::print("분위기가 재밌어 보여요. 이건 읽기 쉬울 것 같아요!");
            return true;
        }
        else {
            ConsoleIO::print("좀 지루해 보이긴 하는데... 시도는 해볼게요.");
            return true;
        }

    case eRequestType::GenreAndMood:
        if (genreMatch && moodMatch) {
            ConsoleIO::print("완전 제 스타일이에요! 이걸로 독후감 써도 좋겠어요.");
            return true;
        }
        else if (genreMatch || moodMatch) {
            ConsoleIO::print("조금 애매하긴 하지만... 시간 나면 읽어볼게요.");
            return true;
        }
        else {
            ConsoleIO::print("이건 좀 어려워 보여요. 수업 시간에 졸 것 같아요...");
            return false;
        }

    case eRequestType::AnyBook:
        ConsoleIO::print("선생님이 읽으라고 했으면 읽어야죠! 어떤 책이든 도움이 될 거예요.");
        return true;
    }

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
