#include "MerchantNPC.h"
#include <iostream>

bool MerchantNPC::rateBook(Book* book) const {
    std::cout << "상인은 책의 시장 가치를 평가합니다.\n";
    return true;
}

bool MerchantNPC::borrowBook(Book* book) {
    borrowed = true;
    inventory.push_back(book);
    return true;
}

Book* MerchantNPC::returnBook() {
    if (borrowed && rand() % 4 == 0) {
        std::cout << "상인이 책을 도난당했다고 주장합니다!\n";
        return nullptr;
    }
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        return b;
    }
    return nullptr;
}

bool MerchantNPC::isReturningBook() const {
    return rand() % 2;
}

bool MerchantNPC::wantsRecommendation() const {
    return false;
}

void MerchantNPC::compensateForDamage(Book* book) {
    std::cout << "흥정 끝에 적은 금액으로 보상합니다.\n";
    gold -= 2;
}

void MerchantNPC::debugPrint() const {
    std::cout << "[Merchant] " << name << " (gold: " << gold << ")\n";
}
