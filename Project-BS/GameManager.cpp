#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "CrudStore.h"
#include "RandomNPC.h"
#include "ConsoleIO.h"
#include <string>
#include <sstream>
#include <algorithm>

GameManager::GameManager() : day(1) {
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

// 하루의 시작 단계
bool GameManager::startDay() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::getWelcomeArt());

    ConsoleIO::print("텍스트 입력창이 보이도록 화면을 조정해 주세요. ");
    ConsoleIO::print("> \"시작\" \n입력: ");
    std::string start_command;
    std::cin >> start_command;

    if (start_command != "시작") {
        ConsoleIO::println("올바른 명령이 아닙니다. 게임을 종료합니다.");
        return false;
    }

    ConsoleIO::println("\nDay " + std::to_string(day) + " 시작!\n");
    return true;
}

// 책 집필 단계
void GameManager::performWritingPhase() {
    while (true) {
        uiManager.clearScreen();
        ConsoleIO::println(AsciiArt::generate_book_art());
        ConsoleIO::println("\n[책 집필]\n");
        ConsoleIO::println("마법 기운을 소모하여 책을 만들어 보세요!");
        ConsoleIO::println("[텍스트 입력창]에 집필 요소를 입력하여 나만의 책을 집필할 수 있습니다.\n");
        ConsoleIO::println(AsciiArt::getLine('='));

        crud.displayStatus();
        ConsoleIO::println("\n\"(장르), (분위기), (분량), (엣지요소), (기타), (제목)\" 순서로 입력해주세요.");
        ConsoleIO::println("\"입력 예시: 판타지, 어두움, 120, 반전, 없음, 다크소울\"\n");
        //ConsoleIO::println("※ 책을 집필하지 않고 손님 응대로 바로 가려면 \"건너뛰기\"를 입력하세요.\n");

        ConsoleIO::println("[현재 사용 가능한 집필 요소]");
        crud.displayAvailableElements(); // 현재 사용 가능한 집필 요소를 출력

        std::string ans;
        ConsoleIO::println("\n\n\n > [집필 요소] 입력");
        std::cin.ignore();
        std::getline(std::cin, ans);

        // 건너뛰기 기능
        if (ans == "건너뛰기") {
            ConsoleIO::println("책 집필을 건너뛰고 손님 응대로 이동합니다.");
            return;
        }

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

        std::string genreStr = tokens[0];
        std::string moodStr = tokens[1];
        std::string lengthStr = tokens[2];
        std::string edgeStr = tokens[3];
        std::string etcStr = tokens[4];
        std::string title = tokens[5];
        int length;

        try {
            length = std::stoi(lengthStr);
        }
        catch (const std::exception& e) {
            ConsoleIO::println("분량은 정수로 입력해주세요. 예외: " + std::string(e.what()));
            continue;
        }
        catch (...) {
            ConsoleIO::println("분량 변환 중 알 수 없는 예외가 발생했습니다.");
            continue;
        }

        eBookGenre genre;
        eBookMood mood;
        eBookEdge edge;
        eBookEtc etc;

        try {
            genre = Enum_Utils::fromKoreanGenre(genreStr);
            mood = Enum_Utils::fromKoreanMood(moodStr);
            edge = Enum_Utils::fromKoreanEdge(edgeStr);
            etc = Enum_Utils::fromKoreanEtc(etcStr);
            Book* newBook = crud.getBookFactory().createBook(title, "수동 제작", genre, mood, length, edge, etc);

            if (crud.getBookStock() >= crud.getMaxBookStock()) {
                ConsoleIO::println("※ 재고 한도 초과! 책을 더 이상 보관할 수 없습니다.");
                return;
            }

            crud.getInventory().addBook(newBook);
            crud.setBookStock(crud.getInventory().getTotalBookCount());
            ConsoleIO::println("책이 성공적으로 집필되었습니다: " + title);
        }
        catch (const std::exception& e) {
            ConsoleIO::println("입력값 중 올바르지 않은 항목이 있습니다. 예외: " + std::string(e.what()));
            continue;
        }
        catch (...) {
            ConsoleIO::println("입력값 처리 중 알 수 없는 예외가 발생했습니다.");
            continue;
        }

        // 다음 행동 선택
        std::string command;
        while (true) {
            ConsoleIO::println("\n무엇을 하시겠습니까? (집필 / 인벤토리 / 응대)");
            ConsoleIO::print("입력: ");
            std::getline(std::cin >> std::ws, command);

            if (command == "집필") break;
            else if (command == "인벤토리") performShowInventoryPhase();
            else if (command == "응대") return;
            else ConsoleIO::println("올바른 명령어가 아닙니다. 다시 입력해주세요.");
        }
    }
}


// 재고 확인 단계
void GameManager::performShowInventoryPhase() {
    uiManager.clearScreen();
    uiManager.displayInventory(crud.getInventory());

    while (true) {
        // TODO: 책 복원 페이즈 만들기
        ConsoleIO::println("> 책 소각: \"[제목] 소각\"  |  복원: \"[제목] RepARARe\"  |  뒤로가기: \"뒤로가기\"");
        ConsoleIO::print("입력: ");
        std::string input;
        std::getline(std::cin, input);

        if (input == "뒤로가기") return;

        if (input.size() > 4 && input.substr(input.size() - 4) == "소각") {
            std::string title = input.substr(0, input.size() - 4);
            Book* target = crud.getInventory().findBook(title);
            if (target) {
                crud.getInventory().removeBook(target);
                crud.setBookStock(crud.getInventory().getTotalBookCount());
                ConsoleIO::println("\"" + title + "\" 책이 소각되었습니다.");
            }
            else {
                ConsoleIO::println("해당 제목의 책을 찾을 수 없습니다.");
            }
        }
        else if (input.size() > 8 && input.substr(input.size() - 8) == " RepARARe") {
            std::string title = input.substr(0, input.size() - 8);
            Book* target = crud.getInventory().findBook(title);
            if (target && target->getCondition() != eBookCondition::Perfect) {
                MiniGame* game = new TypingGame();
                if (crud.getInventory().attemptToRestoreDamagedBook(target, game)) {
                    delete game;
                    target->repair();
                    ConsoleIO::println(AsciiArt::showRestoreBookArt());
                    ConsoleIO::println(target->getTitle() + " 복원 완료!");
                }
                else {
                    delete game;
                    crud.setBookStock(crud.getInventory().getTotalBookCount());
                    ConsoleIO::println("복원 실패! 책이 너무 손상되어 복구할 수 없습니다.");
                }
            }
            else {
                ConsoleIO::println("복구할 수 있는 책이 없습니다: \"" + title + "\"");
            }
        }
        else {
            ConsoleIO::println("올바른 명령어 형식이 아닙니다.");
        }
    }
}


void GameManager::performNPCPhase() {
    uiManager.clearScreen();
    ConsoleIO::println("손님을 기다리는 중입니다...");

    while (npcs.size() < MAX_NPC_COUNT) {
        // 1. API 호출 및 로딩 애니메이션
        //callNPCGenerationAPI();
        //displayLoadingAnimation(3);
        //ConsoleIO::println("\n곧 손님이 방문할 것 같습니다.");

        // 2. NPC 생성 및 리스트 추가
        NPC* npc = RandomNPC::create(eNPCGenerationMode::CreativeAI);
        npcs.push_back(npc);

        // 3. 응대 시작
        uiManager.clearScreen();
        crud.displayStatus();
        ConsoleIO::println(npc->getArt());

        ConsoleIO::println("[NPC 접객 시작]");
        ConsoleIO::println("고객은 책을 반납하거나 대여하거나, 아무 말 없이 그냥 갈 수도 있습니다!");
        ConsoleIO::println(AsciiArt::getLine('='));

        for (const auto& line : npc->getDialogues()) {
            ConsoleIO::println(line);
        }

        bool shouldRemove = false;

        if (npc->hasBorrowed()) {
            Book* returnedBook = npc->returnBook();
            if (returnedBook) {
                // TODO: 고객 책 반납 시 처리, 책의 상태에 따라 재화 획득량이 달라짐
                ConsoleIO::println("고객이 \"" + returnedBook->getTitle() + "\" 책을 반납했습니다.");
                crud.getInventory().addBook(returnedBook);
                crud.addDailyGold(npc->payGold(10));       // 일일 골드
                crud.addDailyMagicPower(npc->payMagicPower(10)); // 마법력 증가
                crud.addDailyExperience(npc->payExp(20)); // 일일 경험치, 일부 NPC는 경험치 지급 로직이 다름
            }
            else {
                ConsoleIO::println("반납할 책이 없습니다.");
            }
            shouldRemove = true;
        }
        else if (npc->wantsRecommendation()) {
            while (true) {
                ConsoleIO::println("책 추천: [책 제목] 입력    |    책 재고 확인: \"재고 확인\" 입력    |    아무 것도 하지 않기: \"패스\"");
                std::string input;
                ConsoleIO::print("> 입력: ");
                std::getline(std::cin, input);

                if (input == "재고 확인") {
                    performShowInventoryPhase();
                    continue; // 빠져 나오면 다시 입력 대기
                }
                else if (input == "패스") {
                    ConsoleIO::println("NPC는 고개를 끄덕이고 떠났습니다.");
                    shouldRemove = true;
                    break;
                }

                Book* selected = crud.getInventory().findBook(input);
                if (!selected) {
                    ConsoleIO::println("책 제목이 잘못되었습니다. 다시 입력해주세요.");
                    continue;
                }

                bool satisfied = npc->rateBook(selected);
                if (satisfied) {
                    ConsoleIO::println("고객이 만족해했습니다!");
                    // 고객 만족 시 보상 처리, 책의 상태에 따라 재화 획득량이 달라짐
                    npc->borrowBook(selected);
                    selected->setAvailable(false); // 책을 대여 상태로 변경
                    crud.addDailyGold(npc->payGold(10));       // 일일 골드
                    crud.addDailyMagicPower(npc->payMagicPower(10)); // 마법력 증가
                    crud.addDailyExperience(npc->payExp(10)); // 일일 경험치, 일부 NPC는 경험치 지급 로직이 다름
                    crud.addDailyRankPoints(5); //랭킹 포인트 추가
                }
                else {
                    ConsoleIO::println("고객이 불만족해합니다...");
                    // 고객 불만족 시 패널티 처리, 책의 상태에 따라 재화 획득량이 달라짐
                    crud.addDailyExperience(npc->payExp(5)); // 일일 경험치, 일부 NPC는 경험치 지급 로직이 다름
                }

                // crud.getInventory().removeBook(selected);

                shouldRemove = false;
                break;
            }
        }
        else {
            ConsoleIO::println("NPC는 조용히 둘러보더니 그냥 떠났습니다.");
            shouldRemove = true;
        }

        if (shouldRemove) {
            delete npc;
            npcs.pop_back(); // 방금 추가한 NPC 제거
        }

        // 4. 다음 손님 받을지 확인
        if (npcs.size() < MAX_NPC_COUNT) {
            std::string decision;
            while (true) {
                ConsoleIO::println("다음 손님을 받으시겠습니까? (yes / no)");
                ConsoleIO::print("> 입력: ");
                std::getline(std::cin, decision);
                if (decision == "yes") break;
                else if (decision == "no") {
                    ConsoleIO::println("오늘의 장사를 마감합니다...");

                    // 책을 빌린 NPC는 제외하고 나머지 NPC 제거
                    for (auto it = npcs.begin(); it != npcs.end(); ) {
                        if (!(*it)->hasBorrowed()) {  // 책을 빌리지 않은 경우
                            delete* it;               // 메모리 해제
                            it = npcs.erase(it);     // 리스트에서 제거하고 반복자 갱신
                        }
                        else {
                            ++it;                     // 다음 NPC로
                        }
                    }
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

void GameManager::promptMagicCommand() {
    ConsoleIO::println("<STSTEM> 접객을 종료할 시간입니다. 정리 마법을 사용해 주세요");
    ConsoleIO::println("> 정리 마법 사용: \"MeraM\"");
    std::string response;
    ConsoleIO::print("입력: ");
    std::cin.ignore();
    while (true) {
        std::cin >> response;
        if (response == "MeraM") {
            ConsoleIO::println("<STSTEM> 마법이 불러일으킨 바람이 어질러진 서고를 정리합니다.");
            ConsoleIO::println("<STSTEM> 무거운 쇠사슬이 뱀처럼 움직여 정문을 굳게 잠굽니다.");
            ConsoleIO::println("<STSTEM> 깃펜이 스스로 움직여 오늘 하루를 전산합니다.");
            break;
        }
        else {
            ConsoleIO::println("정리 마법이 취소되었습니다. 다시 시도해 주세요");
        }
    }
}

void GameManager::promptSettlementConfirmation() {
    ConsoleIO::println("> \"정산 결과 확인\" 입력:");
    std::string response;
    ConsoleIO::print("입력: ");
    std::cin.ignore();
    while (true) {
        std::cin >> response;
        if (response == "정산 결과 확인") {
            crud.displayDailySummary();

            ConsoleIO::println("- 획득 랭킹 포인트: " + std::to_string(crud.getDailyRankPointsEarned()));
            ConsoleIO::println("- 총 랭킹 포인트: " + std::to_string(crud.getRankPoints()));

            crud.checkupRankUP(); // 랭킹 포인트 확인 및 랭킹 업데이트

            crud.resetDailyEarnings();
            if (crud.checkLevelUp()) {
                uiManager.displayLevelUpMessage(crud.getLevel());
            }
            break;
        }
        else {
            ConsoleIO::println("정산 결과 확인이 취소 되었습니다. 다시 시도해 주세요");
        }
    }
}

void GameManager::promptSatisfactionCheck() {
    ConsoleIO::println("> \"만족도 확인\" 입력:");
    std::string response;
    ConsoleIO::print("입력: ");
    std::cin.ignore();
    while (true) {
        std::cin >> response;
        if (response == "만족도 확인") {
            // TODO: 만족도 출력 로직 구현
            ConsoleIO::println("오늘 하루 고객들의 만족도를 확인합니다.");

            break;
        }
        else {
            ConsoleIO::println("만족도 확인이 취소 되었습니다. 다시 시도해 주세요");
        }
    }
}

void GameManager::promptBookRestoration() {
    ConsoleIO::println("> \"책 복원 시작\" 입력:               다음날로 넘기기: \"다음 날\" 입력               재고 확인: \"재고 확인\" 입력");
    std::string response;
    ConsoleIO::print("입력: ");
    std::cin.ignore();
    std::cin >> response;
    if (response == "책 복원 시작") {
        for (auto& book : crud.getInventory().getBooks()) {
            if (book->getCondition() != eBookCondition::Perfect) {
                ConsoleIO::println("책 \"" + book->getTitle() + "\"이 손상되었습니다. 복구를 시도하시겠습니까? (y/n)");
                ConsoleIO::print("입력: ");
                std::string res;
                std::cin >> res;
                if (res == "y" || res == "Y") {
                    MiniGame* game = new TypingGame();
                    crud.getInventory().attemptToRestoreDamagedBook(book, game);
                    delete game;
                    book->repair();
                    ConsoleIO::println(AsciiArt::showRestoreBookArt());
                    ConsoleIO::println(book->getTitle() + " 복원 완료!");
                }
            }
        }
    }
}

void GameManager::promptInventoryView() {
    std::string ans;
    ConsoleIO::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") performShowInventoryPhase();
}

// 정산 단계
void GameManager::performSettlementPhase() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::showClosingArt());
    ConsoleIO::println("[NPC 접객 종료]");
    ConsoleIO::println("\n 오늘 하루도 고생 많으셨습니다! 오늘의 수익은 얼마나 될까요?");
    ConsoleIO::println("수익과 재고 현황, 나의 레벨 그리고 서점 랭킹을 확인하는 시간입니다.");

    ConsoleIO::println(AsciiArt::getLine('='));
    crud.displayStatus();

    promptMagicCommand();
    promptSettlementConfirmation();
    promptSatisfactionCheck();
    promptBookRestoration();
    promptInventoryView();
}

void GameManager::endDay() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::showClosingArt());
    ConsoleIO::println("[NPC 접객 종료]");
    ConsoleIO::println("\n 오늘 하루도 고생 많으셨습니다! 오늘의 수익은 얼마나 될까요?");
    ConsoleIO::println("수익과 재고 현황, 나의 레벨 그리고 서점 랭킹을 확인하는 시간입니다.");

    if (crud.checkLevelUp()) {
        uiManager.displayLevelUpMessage(crud.getLevel());
    }
    ++day;
}
