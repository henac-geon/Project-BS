﻿#include "MerchantNPC.h"
#include "ConsoleIO.h"
#include <cstdlib> // for rand()

bool MerchantNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print("상인이 책의 시장 가치를 평가합니다.");
    return true;  // 모든 책을 구매 대상으로 간주
}

bool MerchantNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 빌려갑니다.");
    borrowed = true;
    inventory.push_back(book);
    book->setAvailable(false);
    return true;
}

Book* MerchantNPC::returnBook() {
    if (borrowed && rand() % 4 == 0) {
        ConsoleIO::print("상인이 책을 도난당했다고 주장합니다!");
        borrowed = false;
        return nullptr;
    }

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
    ConsoleIO::print("책 보유 여부: " + std::string(borrowed ? "예" : "아니오"));
    if (!inventory.empty()) {
        ConsoleIO::print("보유한 책 수: " + std::to_string(inventory.size()));
        ConsoleIO::print("마지막 책 제목: " + inventory.back()->getTitle());
    }
    ConsoleIO::print("===========================");
}
