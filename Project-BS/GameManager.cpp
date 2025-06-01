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

// 하루의 시작 단계
bool GameManager::startDay() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::getWelcomeArt());

    std::string start_command;
    ConsoleIO::print("텍스트 입력창이 보이도록 화면을 조정해 주세요. ");
    ConsoleIO::print("> \"시작\" \n입력: ");
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
        ConsoleIO::println("마법 기운을 소모하여 책을 만들어 보세요!");
        ConsoleIO::println("[텍스트 입력창]에 집필 요소를 입력하여 나만의 책을 집필할 수 있습니다.\n");
        AsciiArt::getLine();

        crud.displayStatus();
        ConsoleIO::println("\n\"(장르), (분위기), (분량), (엣지요소), (기타), (제목)\" 순서로 입력해주세요.");
        ConsoleIO::println("\"입력 예시: 판타지, 암울, 120, 반전, 없음, 다크소울\"\n");
        ConsoleIO::println("※ 책을 집필하지 않고 손님 응대로 바로 가려면 \"건너뛰기\"를 입력하세요.\n");

        ConsoleIO::println("[현재 사용 가능한 집필 요소]");
        crud.getBookFactory().displayAvailableElements();

        std::string ans;
        ConsoleIO::println("\n[집필 요소] 입력");
        std::cin.ignore();
        std::getline(std::cin, ans);

        // 건너뛰기 기능 추가
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

        Book* newBook = crud.getBookFactory().createBook(title, "수동 제작", genre, mood, length, edge, etc);
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
                break; // 인벤토리 보기 → 다시 루프 반복
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

// 재고 확인 단계
void GameManager::performShowInventoryPhase() {
    uiManager.clearScreen();
    uiManager.displayInventory(crud.getInventory());

    while (true) {
        std::string input;
        ConsoleIO::println("> 책 소각 마법: \"[책 제목] arDeat\" 입력         책 복구 마법: \"[책 제목] arRegen\" 입력          뒤로가기: \"뒤로가기\" 입력");
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
                        if (target->getCondition() != eBookCondition::Perfect) {
                            // 책 복구용 미니 게임 추가
                            // TODO: 책 복구 시 재화 소모 로직 추가
                            MiniGame* game = new TypingGame();  // 또는 ReactionGame
                            crud.getInventory().attemptToRestoreDamagedBook(target, game);
                            delete game;
                            target->repair();
                            ConsoleIO::println(AsciiArt::showRestoreBookArt());
                            ConsoleIO::println(target->getTitle() + " 복원 완료!");
                        }
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

// 손님 응대 단계
void GameManager::performNPCPhase() {
    uiManager.clearScreen();

    // NPC 리스트가 다 차 있지 않다면, 오늘 방문할 NPC들을 무작위 생성
    // TODO: api호출을 NPC를 기다릴때마다 사용하여 손님을 기다리고 있다는 느낌을 주기(+ api 사용 어필, 로딩창 구현 필요)
    //if (npcs.size() < MAX_NPC_COUNT) {
    //    int remain = MAX_NPC_COUNT - npcs.size();
    //    int numNPC = rand() % remain + 1; // 1 ~ remain 명 방문
    //    ConsoleIO::println("오늘 방문한 NPC 수: " + std::to_string(numNPC));

    //    for (int i = 0; i < numNPC; ++i) {
    //        NPC* npc = RandomNPC::create(eNPCGenerationMode::CreativeAI);
    //        npcs.push_back(npc);
    //    }
    //}
    // NPC 리스트가 다 차 있지 않다면, 오늘 방문할 NPC들을 무작위 생성
    if (npcs.size() < MAX_NPC_COUNT) {
        int remain = MAX_NPC_COUNT - npcs.size();
        int numNPC = rand() % remain + 1; // 1 ~ remain 명 방문

        ConsoleIO::println("손님을 기다리는 중입니다...");

        // 💡 로딩창 및 API 호출 시뮬레이션
        callNPCGenerationAPI();  // API 요청 흉내
        displayLoadingAnimation(3); // 3초간 로딩 애니메이션

        ConsoleIO::println("\n오늘 방문한 NPC 수: " + std::to_string(numNPC));

        for (int i = 0; i < numNPC; ++i) {
            NPC* npc = RandomNPC::create(eNPCGenerationMode::CreativeAI);
            npcs.push_back(npc);
        }
    }

    // 리스트에서 NPC를 순서대로 응대
    int i = 0;
    while (i < npcs.size()) {
        NPC* npc = npcs[i]; // 현재 NPC 포인터

        // 화면 초기화 및 현재 상태 출력
        uiManager.clearScreen();
        crud.displayStatus();
        ConsoleIO::println(npc->getArt());

        ConsoleIO::println("[NPC 접객 시작]");
        ConsoleIO::println("고객은 책을 반납하거나 대여하거나, 아무 말 없이 그냥 갈 수도 있습니다!");
        AsciiArt::getLine();
        for (const auto& line : npc->getDialogues()) {
            ConsoleIO::println(line);
        }


        bool shouldRemove = false; // 이 NPC를 리스트에서 삭제할지 여부

        // 1. 반납하는 경우
        if (npc->isReturningBook()) {
            Book* returnedBook = npc->returnBook();
            if (returnedBook) {
                ConsoleIO::println("고객이 \"" + returnedBook->getTitle() + "\" 책을 반납했습니다.");
                crud.getInventory().addBook(returnedBook);
                crud.addScore(5);
            }
            else {
                ConsoleIO::println("반납할 책이 없습니다.");
            }
            shouldRemove = true; // 반납 고객은 리스트에서 제거
        }
        // 2. 추천을 받으려는 경우
        else if (npc->wantsRecommendation()) {
            while (true) {
                ConsoleIO::println("책 추천: [책 제목] 입력    |    책 재고 확인: \"재고 확인\" 입력    |    아무 것도 하지 않기: \"패스\"");
                std::string input;
                ConsoleIO::print("> 입력: ");
                std::getline(std::cin, input);

                if (input == "재고 확인") {
                    performShowInventoryPhase();
                    break;
                }
                else if (input == "패스") {
                    ConsoleIO::println("NPC는 고개를 끄덕이고 떠났습니다.");
                    shouldRemove = true; // 아무것도 하지 않은 NPC는 제거
                    break;
                }

                // 책 추천 처리
                Book* selected = crud.getInventory().findBook(input);
                if (!selected) {
                    ConsoleIO::println("책 제목이 잘못되었습니다. 다시 입력해주세요.");
                    continue;
                }

                bool satisfied = npc->rateBook(selected);
                if (satisfied) {
                    ConsoleIO::println("고객이 만족해했습니다!");
                    // TODO: 고객 만족 시 보상 처리
                    /*crud.addScore(10);*/
                }
                else {
                    ConsoleIO::println("고객이 불만족해합니다...");
                    // TODO: 고객 불만족 시 패널티 처리
                    /*int gp = crud.calculateGoldPenalty(*selected);
                    int mp = crud.calculateMagicPenalty(*selected);
                    crud.getPlayer().useGold(gp);
                    crud.getPlayer().consumeMagicPower(mp);
                    crud.deductScore(5);
                    uiManager.displayPenaltyInfo(gp, mp);*/
                }

                // 책 대여 처리: 인벤토리에서 제거하고 NPC에 저장
                crud.getInventory().removeBook(selected);
                npc->borrowBook(selected);

                shouldRemove = false; // 대여한 NPC는 리스트에 유지
                break;
            }
        }
        // 3. 아무 요청도 하지 않는 경우(너무 자주 발생함)
        else {
            ConsoleIO::println("NPC는 조용히 둘러보더니 그냥 떠났습니다.");
            shouldRemove = true; // 아무 행동도 없는 NPC는 제거
        }

        // NPC 제거 또는 유지 처리
        if (shouldRemove) {
            delete npc;                   // 객체 메모리 해제
            npcs.erase(npcs.begin() + i); // 리스트에서 제거 (i는 증가 X)
        }
        else {
            ++i; // 다음 NPC로 넘어감
        }

        // 아직 남은 NPC가 있다면, 다음 손님을 받을지 물어봄
        if (i < npcs.size()) {
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
                            delete* it;                   // 메모리 해제
                            it = npcs.erase(it);         // 리스트에서 제거하고 반복자 갱신
                        }
                        else {
                            ++it;                         // 다음 NPC로
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


// ✨ API 호출 흉내 함수
void GameManager::callNPCGenerationAPI() {
    ConsoleIO::println("[API 호출] NPC 생성 요청 중...");
    // 여기에서 실제 API 호출이 있다면 REST 요청 등을 수행
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기
}

// ✨ 로딩 애니메이션 함수
void GameManager::displayLoadingAnimation(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        ConsoleIO::print(".");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    ConsoleIO::println(""); // 줄바꿈
}

// 정산 단계
void GameManager::performSettlementPhase() {
    uiManager.clearScreen();
    ConsoleIO::println("\n 정산 단계 시작!\n");

    for (auto& book : crud.getInventory().getBooks()) {
        // TODO: 복구를 할 것인지 여부를 물어보는 로직 추가
        if (book->getCondition() != eBookCondition::Perfect) {
            // 책 복구용 미니 게임 추가
            // TODO: 책 복구 시 재화 소모 로직 추가
            // 재화 소모 로직은 crud클레스에서 처리
            MiniGame* game = new TypingGame();  // 또는 ReactionGame
            crud.getInventory().attemptToRestoreDamagedBook(book, game);
            delete game;
            book->repair();
            ConsoleIO::println(AsciiArt::showRestoreBookArt());
            ConsoleIO::println(book->getTitle() + " 복원 완료!");
        }
    }

    // TODO: 플레이어의 스텟 정산
    // TODO: 서점 랭킹 업데이트

    std::string ans;
    ConsoleIO::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") performShowInventoryPhase();
}

// 하루의 마무리 단계
void GameManager::endDay() {
    uiManager.clearScreen();
    if (crud.checkLevelUp()) {
        uiManager.displayLevelUpMessage(crud.getLevel());
    }
    ConsoleIO::println(AsciiArt::showClosingArt());
    ++day;
}
