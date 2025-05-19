#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "BookFactory.h"
#include "PenaltySystem.h"
#include "RandomNPC.h"
#include "ConsolePrinter.h"
#include <string>
#include <algorithm>

/**
 * @brief 기본 생성자
 *
 * - day를 1로 초기화하여 1일차부터 시작
 * - gold 및 magicPower는 0으로 초기화
 * - actions 및 actionNames 초기화
 */
GameManager::GameManager()
    : day(1), gold(0), magicPower(0) {

}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
}

void GameManager::run() {
    std::string command;
    //ConsolePrinter::print("게임을 시작하려면 '시작'을 입력하세요: ");
    //std::cin >> command;
    //if (command != "시작") return;

    while (true) {
        if (!startDay()) break;
        performWritingPhase();
        performNPCPhase();
        performSettlementPhase();
        endDay();

        ConsolePrinter::print("다음 날로 진행하시겠습니까? (y/n): ");
        std::cin >> command;
        if (command != "y" && command != "Y") break;
    }
}

bool GameManager::startDay() {
    uiManager.clearScreen();
    ConsolePrinter::println(AsciiArt::getWelcomeArt());

    std::string command;
    ConsolePrinter::print("텍스트 입력창이 보이도록 화면을 조정해 주세요. ");
    ConsolePrinter::print("> \"시작\" \n입력: ");
    std::cin >> command;

    if (command != "시작") {
        ConsolePrinter::println("⚠️ 올바른 명령이 아닙니다. 게임을 종료합니다.");
        return false;
    }

    ConsolePrinter::println("\n📅 Day " + std::to_string(day) + " 시작!\n");
    return true;
}


void GameManager::performWritingPhase() {
    uiManager.clearScreen();
    ConsolePrinter::println(AsciiArt::generate_book_art());
    ConsolePrinter::println("마법 기운을 소모하여 책을 만들어 보세요!");
    ConsolePrinter::println("[택스트 입력창]에 집필 요소를 입력하여 나만의 책을 집필할 수 있습니다.");
    AsciiArt::getLine();

    // TODO: 플레이어가 가지고 있는 재화 출력

    ConsolePrinter::println("\"(장르), (분위기), (분량), (엣지요소), (기타), (제목)\" 순서로 입력해주세요.");
    ConsolePrinter::println("\"입력 예시: 판타지, 암울, 120, 반전, 없음, 다크소울");

    // TODO: 현재 집필할 수 있는 요소들 출력

    std::string ans;
    ConsolePrinter::println("[집필 요소] 입력");
    std::cin >> ans;
    // TODO: 입력된 요소를 파싱하여 책 생성


    // 책을 생성하고 인벤토리에 추가 -> 확인
    performShowInventoryPhase();
}

void GameManager::performShowInventoryPhase() {
    uiManager.clearScreen();
    ConsolePrinter::println("[책 재고]");
    ConsolePrinter::println("[텍스트 입력창]에 희망하는 행동을 텍스트로 작성해주세요.");
    AsciiArt::getLine();
    ConsolePrinter::println("번호 | 제목 | 장르 | 분위기 | 분량 | 엣지 요소 | 기타 | 재고 상태 | 품질");
    uiManager.displayInventory(inventory);

    while (true) {
        std::string input;
        ConsolePrinter::println("> 책 소각 마법: \"[책 제목] arDeat\" 입력          재고 확인 종료 후 장사 시작: \"장사 시작\" 입력"); // 재고 확인 종료: \"다음날 시작\" 입력");
        ConsolePrinter::print("입력: ");
        std::cin.ignore(); // 이전 입력 버퍼 비우기 (필요 시)
        std::getline(std::cin, input);

        if (input == "장사 시작") {
            break;
        }

        // 입력이 '... arDeat' 형식인지 확인
        if (input.size() > 7 && input.substr(input.size() - 6) == "arDeat") {
            std::string title = input.substr(0, input.size() - 7); // ' arDeat' 제거
            Book* target = inventory.findBook(title);
            if (target) {
                inventory.removeBook(target);
                ConsolePrinter::println("🔥 \"" + title + "\" 책이 소각되었습니다.");
            }
            else {
                ConsolePrinter::println("⚠️ 해당 제목의 책을 찾을 수 없습니다: \"" + title + "\"");
            }
        }
        else {
            ConsolePrinter::println("⚠️ 올바른 명령어 형식이 아닙니다.");
        }
    }
}


void GameManager::performNPCPhase() {
    uiManager.clearScreen();

    // NPC 리스트가 비어 있는 경우, 새 NPC들을 준비
    if (npcs.empty()) {
        int numNPC = rand() % 3 + 1;
        ConsolePrinter::println("오늘 방문한 NPC 수: " + std::to_string(numNPC));

        for (int i = 0; i < numNPC; ++i) {
            npcs.push_back(RandomNPC::create());
        }
    }

    while (!npcs.empty()) {
        int index = rand() % npcs.size();
        NPC* npc = npcs[index];

        uiManager.clearScreen();

        // TODO: 플레이어가 가지고 있는 재화 출력
        ConsolePrinter::println(npc->getArt());

        // 안내 메시지
        ConsolePrinter::println("[NPC 접객 시작]");
        ConsolePrinter::println("다양한 고객을 만나보세요! 누군간 책을 대여할 수도 반납할 수 도 있습니다!");
        ConsolePrinter::println("[텍스트 입력창]에 반드시 올바른 마법을 사용하세요!");
        AsciiArt::getLine();

        // TODO: NPC의 대사 출력, 책 대여/반납 여부에 따라 다르게 출력, 없는 책도 고려해야 함
        ConsolePrinter::println(npc->getDialogue());


        bool validInputReceived = false;
        while (!validInputReceived) {
            ConsolePrinter::println("책 추천: [책 제목] 입력    |    책 재고 확인: \"재고 확인\" 입력");
            std::string input;
            ConsolePrinter::print("> 입력: ");
            std::getline(std::cin, input);

            if (input == "재고 확인") {
                uiManager.displayInventory(inventory);
                continue;
            }

            Book* selected = inventory.findBook(input);
            if (!selected) {
                ConsolePrinter::println("⚠️ 책 제목이 잘못되었습니다. 다시 입력해주세요.");
                continue;
            }

            // TODO: QA 필요
            bool satisfied = npc->rateBook(selected);
            if (satisfied) {
                ConsolePrinter::println("🎉 고객이 만족해했습니다!");
            }
            else {
                ConsolePrinter::println("😠 고객이 불만족해합니다...");
                int gp = PenaltySystem::calculateGoldPenalty(*selected);
                int mp = PenaltySystem::calculateMagicPenalty(*selected);
                gold = (gold - gp < 0) ? 0 : (gold - gp);
                magicPower = (magicPower - mp < 0) ? 0 : (magicPower - mp);
                uiManager.displayPenaltyInfo(gp, mp);
            }

            scoreSystem.updateScore(satisfied);
            validInputReceived = true;
        }

        delete npc;
        npcs.erase(npcs.begin() + index);
    }

    ConsolePrinter::println("✨ 모든 NPC 응대가 완료되었습니다.");
}

void GameManager::performSettlementPhase() {
    ConsolePrinter::println("\n 정산 단계 시작!\n");

    for (auto& book : inventory.getBooks()) {
        if (book->getCondition() == eBookCondition::Damaged) {
            book->repair();
            ConsolePrinter::println(AsciiArt::showRestoreBookArt());
            ConsolePrinter::println(book->getTitle() + " 복원 완료!");
        }
    }

    auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
    ConsolePrinter::println("마지막 책 집필 완료: " + book->getTitle());

    std::string ans;
    ConsolePrinter::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ConsolePrinter::println(AsciiArt::showClosingArt());
    ++day;
}
