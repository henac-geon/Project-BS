#include "WizardNPC.h"
#include "ConsoleIO.h"
#include <cstdlib>

bool WizardNPC::rateBook(Book* book) const {
    if (!book) return false;

    ConsoleIO::print("마법사는 책에서 마법적 에너지를 감지하려 합니다.");
    ConsoleIO::print("흐름이 느껴지는군요... (평가 통과)");
    return true;
}

bool WizardNPC::borrowBook(Book* book) {
    if (!book) return false;

    ConsoleIO::print(name + "이(가) \"" + book->getTitle() + "\" 책을 조심스럽게 대출합니다.");
    borrowed = true;
    inventory.push_back(book);
    book->setAvailable(false);
    return true;
}

Book* WizardNPC::returnBook() {
    if (!inventory.empty()) {
        Book* b = inventory.back();
        inventory.pop_back();
        borrowed = false;
        ConsoleIO::print(name + "이(가) \"" + b->getTitle() + "\" 책을 되돌려 놓습니다.");
        b->setAvailable(true);
        return b;
    }
    return nullptr;
}

bool WizardNPC::isReturningBook() const {
    // 마법력 수치가 짝수일 경우에만 반납
    return borrowed && (magicPower % 2 == 0);
}

bool WizardNPC::wantsRecommendation() const {
    return magicPower > 50;  // 마력이 높을수록 새로운 지식을 갈망함
}

void WizardNPC::compensateForDamage(Book* book) {
    if (!book) return;

    ConsoleIO::print("마법사가 손상된 책을 마법으로 수리하려 했지만... 실패했습니다.");
    ConsoleIO::print("보상으로 10골드를 지불합니다.");
    gold -= 10;
}

void WizardNPC::debugPrint() const {
    ConsoleIO::print("=== 마법사 NPC 디버그 정보 ===");
    ConsoleIO::print("이름: " + name);
    ConsoleIO::print("마력: " + std::to_string(magicPower));
    ConsoleIO::print("보유 골드: " + std::to_string(gold));
    ConsoleIO::print("책 보유 여부: " + std::string(borrowed ? "예" : "아니오"));
    if (!inventory.empty()) {
        ConsoleIO::print("보유한 책 수: " + std::to_string(inventory.size()));
        ConsoleIO::print("마지막 책 제목: " + inventory.back()->getTitle());
    }
    ConsoleIO::print("==============================");
}
