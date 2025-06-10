#include "MerchantNPC.h"
#include "ConsoleIO.h"
#include <cstdlib> // for rand()

// TODO: 아 이거 ai서서 더 자연스럽게 하고 싶은데...
int MerchantNPC::rateBook(Book* book) const {
    if (!book) return 1;  // 무조건 최소 1점은 줌 (상인의 특성)

    ConsoleIO::print("상인이 책의 시장 가치를 계산하고 있습니다...");

    int matchCount = 0;

    bool genreMatch = book->getGenre() == preferredGenre;
    bool moodMatch = book->getMood() == preferredMood;
    bool lengthMatch = book->getLength() == preferredLength;
    bool edgeMatch = book->getEdge() == preferredEdge;
    bool etcMatch = book->getEtc() == preferredEtc;

    switch (requestType) {
    case eRequestType::GenreOnly:
        if (genreMatch) {
            ConsoleIO::print("이 장르의 책은 요즘 잘 팔립니다. 수익이 나겠군요.");
            matchCount += 2;
        }
        else {
            ConsoleIO::print("수요는 좀 떨어지지만, 팔 수는 있겠네요.");
            matchCount += 1;
        }
        break;

    case eRequestType::MoodOnly:
        if (moodMatch) {
            ConsoleIO::print("이 분위기의 책이 최근 인기입니다. 거래 가치가 있군요.");
            matchCount += 2;
        }
        else {
            ConsoleIO::print("흐름을 잘 타진 못하겠지만, 가격만 맞으면 팔립니다.");
            matchCount += 1;
        }
        break;

    case eRequestType::GenreAndMood:
        if (genreMatch && moodMatch) {
            ConsoleIO::print("완벽한 조합입니다! 이건 분명히 이윤이 남을 상품이에요.");
            matchCount += 3;
        }
        else if (genreMatch || moodMatch) {
            ConsoleIO::print("절반의 조건만 맞지만, 괜찮은 딜이 될 수 있겠군요.");
            matchCount += 2;
        }
        else {
            ConsoleIO::print("시장성이 떨어지긴 하지만... 어쩌면 틈새시장이 있을지도?");
            matchCount += 1;
        }
        break;

    case eRequestType::AnyBook:
        ConsoleIO::print("모든 책은 상품입니다. 가격만 맞으면 뭐든 환영이죠.");
        matchCount += (genreMatch + moodMatch);  // 추가 취향 일치 반영
        break;
    }

    // 항상 부가 요소도 반영
    if (lengthMatch) matchCount += 1;
    if (edgeMatch)   matchCount += 1;
    if (etcMatch)    matchCount += 1;

    // 항상 최소 1점 이상 보장
    return (matchCount > 1) ? matchCount : 1;   
}



bool MerchantNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 빌려갑니다.");
    currentBook = book;
    book->setAvailable(false);
    return true;
}

Book* MerchantNPC::returnBook() {
    if (currentBook && rand() % 4 == 0) {
        ConsoleIO::print("상인이 책을 도난당했다고 주장합니다!");
        currentBook = nullptr;
        return nullptr;
    }

    if (currentBook) {
        ConsoleIO::print(name + "이(가) \"" + currentBook->getTitle() + "\" 책이 형편없다며 반납합니다.");
        Book* b = currentBook;
        currentBook = nullptr;
        b->setAvailable(true);
        return b;
    }

    return nullptr;
}

bool MerchantNPC::isReturningBook() const {
    return rand() % 2;  // 50% 확률로 반납
}

bool MerchantNPC::wantsRecommendation() const {
    return false;  // 상인은 추천을 원하지 않음
}

void MerchantNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print("흥정 끝에 적은 금액으로 손상된 책을 보상합니다.");
    gold -= 2;
}

void MerchantNPC::debugPrint() const {
    ConsoleIO::print("=== 상인 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("책 보유 여부: " + std::string(currentBook ? "예" : "아니오"));
    ConsoleIO::print("현재 책: " + (currentBook ? currentBook->getTitle() : "없음"));
    ConsoleIO::print("===========================");
}

int MerchantNPC::payGold(int amount) {
    if (amount <= 0) return 0;

    // 상인은 항상 협상하려 들므로 최대 지불량을 줄임
    int paid = (amount > gold / 2) ? gold / 2 : amount;
    gold -= paid;

    ConsoleIO::print(name + "이(가) 교묘하게 " + std::to_string(paid) + " 골드만 지불합니다.");
    return paid;
}

int MerchantNPC::payMagicPower(int amount) {
    // 상인은 마법을 거의 사용하지 않음
    ConsoleIO::print(name + "은(는) 마법을 믿지 않습니다. 마력 지불 없음.");
    return 0;
}

int MerchantNPC::payExp(int amount) {
    if (amount <= 0) return 0;

    // 경험치는 교섭술 향상에 활용
    ConsoleIO::print(name + "이(가) 협상 능력을 키우기 위해 " + std::to_string(amount) + " 경험치를 소모합니다.");
    return amount;
}
