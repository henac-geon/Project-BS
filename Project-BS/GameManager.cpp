#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "CrudStore.h"
#include "RandomNPC.h"
#include "ConsoleIO.h"
#include <string>
#include <sstream>
#include <algorithm>

GameManager::GameManager()
    : day(1) {
    // 초기화 작업
    crud = CrudStore();
}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
}

void GameManager::run() {
    std::string command;

    while (true) {
        if (!startDay()) break;

        performWritingPhase();
        performNPCPhase();
        performSettlementPhase();
        endDay();

        ConsoleIO::print("다음 날로 진행하시겠습니까? (y/n): ");
        std::cin >> command;
        if (command != "y" && command != "Y") break;
    }
}

bool GameManager::startDay() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::getWelcomeArt());

    std::string command;
    ConsoleIO::print("텍스트 입력창이 보이도록 화면을 조정해 주세요. ");
    ConsoleIO::print("> \"시작\" \n입력: ");
    std::cin >> command;

    if (command != "시작") {
        ConsoleIO::println("올바른 명령이 아닙니다. 게임을 종료합니다.");
        return false;
    }

    ConsoleIO::println("\nDay " + std::to_string(day) + " 시작!\n");
    return true;
}

// return: 1 = 인벤토리 보기, 2 = 손님 응대
void GameManager::performWritingPhase() {
    while (true) {
        uiManager.clearScreen();
        ConsoleIO::println(AsciiArt::generate_book_art());
        ConsoleIO::println("마법 기운을 소모하여 책을 만들어 보세요!");
        ConsoleIO::println("[텍스트 입력창]에 집필 요소를 입력하여 나만의 책을 집필할 수 있습니다.\n");
        AsciiArt::getLine();

        crud.getBookFactory().displayPlayerStatus();
        ConsoleIO::println("\n\"(장르), (분위기), (분량), (엣지요소), (기타), (제목)\" 순서로 입력해주세요.");
        ConsoleIO::println("\"입력 예시: 판타지, 암울, 120, 반전, 없음, 다크소울\"\n");

        ConsoleIO::println("[현재 사용 가능한 집필 요소]");
        crud.getBookFactory().displayAvailableElements();

        std::string ans;
        ConsoleIO::println("\n[집필 요소] 입력");
        std::cin.ignore();
        std::getline(std::cin, ans);

        std::vector<std::string> tokens;
        std::stringstream ss(ans);
        std::string token;
        while (std::getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }

        if (tokens.size() != 6) {
            ConsoleIO::println("입력 형식이 잘못되었습니다. 다시 시도해주세요.");
            continue;
        }

        std::string genreStr = tokens[0], moodStr = tokens[1], edgeStr = tokens[3], etcStr = tokens[4], title = tokens[5];
        int length = std::stoi(tokens[2]);

        eBookGenre genre = (genreStr == "공상과학") ? eBookGenre::SciFi :
            (genreStr == "공포") ? eBookGenre::Horror :
            (genreStr == "미스터리") ? eBookGenre::Mystery :
            (genreStr == "로맨스") ? eBookGenre::Romance :
            (genreStr == "논픽션") ? eBookGenre::NonFiction :
            eBookGenre::Fantasy;

        eBookMood mood = (moodStr == "명랑") ? eBookMood::Light :
            (moodStr == "감성") ? eBookMood::Emotional :
            (moodStr == "긴장감") ? eBookMood::Tense :
            (moodStr == "엉뚱") ? eBookMood::Whimsical :
            eBookMood::Dark;

        eBookEdge edge = (edgeStr == "반전") ? eBookEdge::Reversal : eBookEdge::None;
        eBookEtc  etc = (etcStr == "없음") ? eBookEtc::None : eBookEtc::None;

        Book* newBook = crud.getBookFactory().createBook(genre, mood, length, edge, etc);
        if (newBook) newBook->setTitle(title);
        crud.getInventory().addBook(newBook);

        ConsoleIO::println("책이 성공적으로 집필되었습니다: " + title);

        // 다음 행동 선택
        std::string command;
        while (true) {
            ConsoleIO::println("\n무엇을 하시겠습니까?");
            ConsoleIO::println("- 다시 책을 집필하려면: \"집필\"");
            ConsoleIO::println("- 인벤토리를 보려면: \"인벤토리\"");
            ConsoleIO::println("- 손님 응대로 가려면: \"응대\"");
            ConsoleIO::print("입력: ");
            std::getline(std::cin >> std::ws, command);

            if (command == "집필") {
                break;  // 루프 반복 → 다시 집필
            }
            else if (command == "인벤토리") {
                performShowInventoryPhase();
                continue; // 인벤토리 보기 → 다시 루프 반복
            }
            else if (command == "응대") {
                return; // 응대로 넘어감
            }
            else {
                ConsoleIO::println("올바른 명령어가 아닙니다. 다시 입력해주세요.");
            }
        }
    }
}


void GameManager::performShowInventoryPhase() {
    uiManager.clearScreen();
    ConsoleIO::println("[책 재고]");
    ConsoleIO::println("[텍스트 입력창]에 희망하는 행동을 텍스트로 작성해주세요.");
    AsciiArt::getLine();
    ConsoleIO::println("번호 | 제목 | 장르 | 분위기 | 분량 | 엣지 요소 | 기타 | 재고 상태 | 품질");
    uiManager.displayInventory(crud.getInventory());

    while (true) {
        std::string input;
        ConsoleIO::println("> 책 소각 마법: \"[책 제목] arDeat\" 입력");
        ConsoleIO::println("> 책 복구 마법: \"[책 제목] arRegen\" 입력");
        ConsoleIO::println("> 재고 확인 종료 후 장사 시작: \"장사 시작\" 입력");
        ConsoleIO::println("> 뒤로가기: \"뒤로가기\" 입력");
        ConsoleIO::print("입력: ");
        std::getline(std::cin, input);

        if (input == "뒤로가기") return;

        if (input.size() > 7) {
            std::string suffix = input.substr(input.size() - 6);
            std::string title = input.substr(0, input.size() - 7);

            if (suffix == "arDeat") {
                Book* target = crud.getInventory().findBook(title);
                if (target) {
                    crud.getInventory().removeBook(target);
                    ConsoleIO::println("\"" + title + "\" 책이 소각되었습니다.");
                }
                else {
                    ConsoleIO::println("해당 제목의 책을 찾을 수 없습니다: \"" + title + "\"");
                }
            }
            else if (suffix == "arRege") { // arRegen에서 마지막 n이 잘리므로 주의
                if (input.size() >= 8 && input.substr(input.size() - 7) == "arRegen") {
                    title = input.substr(0, input.size() - 8);
                    Book* target = crud.getInventory().findBook(title);
                    if (target) {
                        crud.getInventory().removeBook(target);
                        crud.getInventory().addBook(target);
                        ConsoleIO::println("\"" + title + "\" 책이 복구되었습니다.");
                    }
                    else {
                        ConsoleIO::println("복구할 수 있는 책이 없습니다: \"" + title + "\"");
                    }
                }
                else {
                    ConsoleIO::println("올바른 명령어 형식이 아닙니다.");
                }
            }
            else {
                ConsoleIO::println("올바른 명령어 형식이 아닙니다.");
            }
        }
        else {
            ConsoleIO::println("올바른 명령어 형식이 아닙니다.");
        }
    }
}


void GameManager::performNPCPhase() {
    uiManager.clearScreen();

    if (npcs.empty()) {
        int numNPC = rand() % 3 + 1;
        ConsoleIO::println("오늘 방문한 NPC 수: " + std::to_string(numNPC));
        for (int i = 0; i < numNPC; ++i) {
            npcs.push_back(RandomNPC::create());
        }
    }

    while (!npcs.empty()) {
        int index = rand() % npcs.size();
        NPC* npc = npcs[index];

        uiManager.clearScreen();
        crud.displayStatus();
        ConsoleIO::println(npc->getArt());

        ConsoleIO::println("[NPC 접객 시작]");
        ConsoleIO::println("다양한 고객을 만나보세요! 누군간 책을 대여할 수도 반납할 수 도 있습니다!");
        ConsoleIO::println("[텍스트 입력창]에 반드시 올바른 마법을 사용하세요!");
        AsciiArt::getLine();
        ConsoleIO::println(npc->getDialogue());

        bool validInputReceived = false;
        while (!validInputReceived) {
            ConsoleIO::println("책 추천: [책 제목] 입력    |    책 재고 확인: \"재고 확인\" 입력");
            std::string input;
            ConsoleIO::print("> 입력: ");
            std::getline(std::cin, input);

            if (input == "재고 확인") {
                performShowInventoryPhase();
                continue;
            }

            Book* selected = crud.getInventory().findBook(input);
            if (!selected) {
                ConsoleIO::println("책 제목이 잘못되었습니다. 다시 입력해주세요.");
                continue;
            }

            bool satisfied = npc->rateBook(selected);
            if (satisfied) {
                ConsoleIO::println("고객이 만족해했습니다!");
                crud.addScore(10);
            }
            else {
                ConsoleIO::println("고객이 불만족해합니다...");
                int gp = crud.calculateGoldPenalty(*selected);
                int mp = crud.calculateMagicPenalty(*selected);
                crud.getPlayer().useGold(gp);
                crud.getPlayer().consumeMagicPower(mp);
                crud.deductScore(5);
                uiManager.displayPenaltyInfo(gp, mp);
            }

            validInputReceived = true;
        }

        delete npc;
        npcs.erase(npcs.begin() + index);

        if (!npcs.empty()) {
            std::string decision;
            while (true) {
                ConsoleIO::println("다음 손님을 받으시겠습니까? (yes / no)");
                ConsoleIO::print("> 입력: ");
                std::getline(std::cin, decision);
                if (decision == "yes") break;
                else if (decision == "no") {
                    ConsoleIO::println("오늘의 장사를 마감합니다...");
                    for (NPC* remaining : npcs) delete remaining;
                    npcs.clear();
                    return;
                }
                else {
                    ConsoleIO::println("올바른 입력이 아닙니다. 'yes' 또는 'no'를 입력해주세요.");
                }
            }
        }
    }

    ConsoleIO::println("모든 NPC 응대가 완료되었습니다.");
}

void GameManager::performSettlementPhase() {
    uiManager.clearScreen();
    ConsoleIO::println("\n 정산 단계 시작!\n");

    for (auto& book : crud.getInventory().getBooks()) {
        if (book->getCondition() == eBookCondition::Damaged) {
            book->repair();
            ConsoleIO::println(AsciiArt::showRestoreBookArt());
            ConsoleIO::println(book->getTitle() + " 복원 완료!");
        }
    }

    std::string ans;
    ConsoleIO::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") performShowInventoryPhase();
}

void GameManager::endDay() {
    uiManager.clearScreen();
    if (crud.checkLevelUp()) {
        uiManager.displayLevelUpMessage(crud.getLevel());
    }
    ConsoleIO::println(AsciiArt::showClosingArt());
    ++day;
}
