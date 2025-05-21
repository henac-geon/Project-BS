#include "GameManager.h"
#include "AsciiArtRepository.h"
#include "BookFactory.h"
#include "PenaltySystem.h"
#include "RandomNPC.h"
#include "ConsoleIO.h"
#include <string>
#include <sstream>
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
    // 초기화 작업
}

GameManager::~GameManager() {
    for (auto npc : npcs) delete npc;
}

void GameManager::run() {
    std::string command;
    //ConsoleIO::print("게임을 시작하려면 '시작'을 입력하세요: ");
    //std::cin >> command;
    //if (command != "시작") return;

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


void GameManager::performWritingPhase() {
    uiManager.clearScreen();
    ConsoleIO::println(AsciiArt::generate_book_art());
    ConsoleIO::println("마법 기운을 소모하여 책을 만들어 보세요!");
    ConsoleIO::println("[택스트 입력창]에 집필 요소를 입력하여 나만의 책을 집필할 수 있습니다.\n");
    AsciiArt::getLine();

    // TODO: 플레이어가 가지고 있는 재화 출력
    bookFactory.displayPlayerStatus();

    ConsoleIO::println("\n\"(장르), (분위기), (분량), (엣지요소), (기타), (제목)\" 순서로 입력해주세요.");
    ConsoleIO::println("\"입력 예시: 판타지, 암울, 120, 반전, 없음, 다크소울\n");

    // TODO: 현재 집필할 수 있는 요소들 출력
    ConsoleIO::println("[현재 사용 가능한 집필 요소]");
    bookFactory.displayAvailableElements();


    std::string ans;
    ConsoleIO::println("\n[집필 요소] 입력");
    std::cin.ignore(); // 버퍼 정리
    std::getline(std::cin, ans);

    ConsoleIO::println("입력한 집필 요소: " + ans); // 디버깅용

    // TODO: 입력된 요소를 파싱하여 책 생성
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(ans);  // string 기반 스트림

    while (std::getline(ss, token, ',')) {
        // 앞뒤 공백 제거
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        tokens.push_back(token);
    }

    // 디버깅용: 파싱된 요소 개수 및 내용 출력
    ConsoleIO::println("파싱된 요소 개수: " + std::to_string(tokens.size()));
    ConsoleIO::println("파싱된 요소: ");
    for (const auto& t : tokens) {
        ConsoleIO::println(t);
    }

    if (tokens.size() != 6) {
        ConsoleIO::println("입력 형식이 잘못되었습니다. 다시 시도해주세요.");
        return;
    }

    // 입력값 파싱 이후
    std::string genreStr = tokens[0];
    std::string moodStr = tokens[1];
    int length = std::stoi(tokens[2]);
    std::string edgeStr = tokens[3];
    std::string etcStr = tokens[4];
    std::string title = tokens[5];

    // 문자열 → enum 변환
    eBookGenre genre;
    eBookMood mood;
    eBookEdge edge;
    eBookEtc etc;


    // TODO: 배열을 이용한 변환으로 개선 예정
    if (genreStr == "판타지") genre = eBookGenre::Fantasy;
    else if (genreStr == "로맨스") genre = eBookGenre::Romance;
    else if (genreStr == "공포") genre = eBookGenre::Horror;
    else if (genreStr == "미스터리") genre = eBookGenre::Mystery;
    else if (genreStr == "공상과학") genre = eBookGenre::SciFi;
    else if (genreStr == "논픽션") genre = eBookGenre::NonFiction;
    else genre = eBookGenre::Fantasy; // 기본값

    if (moodStr == "암울") mood = eBookMood::Dark;
    else if (moodStr == "명랑") mood = eBookMood::Light;
    else if (moodStr == "감성") mood = eBookMood::Emotional;
    else if (moodStr == "긴장감") mood = eBookMood::Tense;
    else if (moodStr == "엉뚱") mood = eBookMood::Whimsical;
    else mood = eBookMood::Dark;

    if (edgeStr == "반전") edge = eBookEdge::Reversal;
    else edge = eBookEdge::None;

    if (etcStr == "없음") etc = eBookEtc::None;
    else etc = eBookEtc::None; // 기타는 추후 확장 가능

    // BookFactory를 통해 책 생성 (마법 기운 차감 포함)
    Book* newBook = bookFactory.createBook(genre, mood, length, edge, etc);

    // 생성된 책의 제목 덮어쓰기
    if (newBook != nullptr) {
        newBook->setTitle(title); // setTitle 함수가 Book 클래스에 필요
    }

    // 집필 결과 출력
    ConsoleIO::println("책이 성공적으로 집필되었습니다: " + title);

    // 디버깅용: 책 정보 출력
    ConsoleIO::println("장르: " + genreStr);
    ConsoleIO::println("분위기: " + moodStr);
    ConsoleIO::println("분량: " + std::to_string(length) + "페이지");
    ConsoleIO::println("엣지 요소: " + edgeStr);
    ConsoleIO::println("기타 요소: " + etcStr);
    ConsoleIO::println("제목: " + title);

    // TODO: 인벤토리에 추가
    inventory.addBook(newBook);

    // 책을 생성하고 인벤토리에 추가 -> 확인
    performShowInventoryPhase();
}

void GameManager::performShowInventoryPhase() {
    uiManager.clearScreen();
    ConsoleIO::println("[책 재고]");
    ConsoleIO::println("[텍스트 입력창]에 희망하는 행동을 텍스트로 작성해주세요.");
    AsciiArt::getLine();
    ConsoleIO::println("번호 | 제목 | 장르 | 분위기 | 분량 | 엣지 요소 | 기타 | 재고 상태 | 품질");
    uiManager.displayInventory(inventory);

    while (true) {
        std::string input;
        ConsoleIO::println("> 책 소각 마법: \"[책 제목] arDeat\" 입력          재고 확인 종료 후 장사 시작: \"장사 시작\" 입력"); // 재고 확인 종료: \"다음날 시작\" 입력");
        ConsoleIO::print("입력: ");
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
                ConsoleIO::println("\"" + title + "\" 책이 소각되었습니다.");
            }
            else {
                ConsoleIO::println("해당 제목의 책을 찾을 수 없습니다: \"" + title + "\"");
            }
        }
        else {
            ConsoleIO::println("올바른 명령어 형식이 아닙니다.");
        }
    }
}


void GameManager::performNPCPhase() {
    uiManager.clearScreen();

    // NPC 리스트가 비어 있는 경우, 새 NPC들을 준비
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

        // TODO: 플레이어가 가지고 있는 재화 출력
        bookFactory.displayPlayerStatus();

        ConsoleIO::println(npc->getArt());

        // 안내 메시지
        ConsoleIO::println("[NPC 접객 시작]");
        ConsoleIO::println("다양한 고객을 만나보세요! 누군간 책을 대여할 수도 반납할 수 도 있습니다!");
        ConsoleIO::println("[텍스트 입력창]에 반드시 올바른 마법을 사용하세요!");
        AsciiArt::getLine();

        // TODO: NPC의 대사 출력, 책 대여/반납 여부에 따라 다르게 출력, 없는 책도 고려해야 함
        ConsoleIO::println(npc->getDialogue());


        bool validInputReceived = false;
        while (!validInputReceived) {
            ConsoleIO::println("책 추천: [책 제목] 입력    |    책 재고 확인: \"재고 확인\" 입력");
            std::string input;
            ConsoleIO::print("> 입력: ");
            std::getline(std::cin, input);

            if (input == "재고 확인") {
                uiManager.displayInventory(inventory);
                continue;
            }

            Book* selected = inventory.findBook(input);
            if (!selected) {
                ConsoleIO::println("책 제목이 잘못되었습니다. 다시 입력해주세요.");
                continue;
            }

            // TODO: QA 필요
            bool satisfied = npc->rateBook(selected);
            if (satisfied) {
                ConsoleIO::println("고객이 만족해했습니다!");
            }
            else {
                ConsoleIO::println("고객이 불만족해합니다...");
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

    ConsoleIO::println("모든 NPC 응대가 완료되었습니다.");
}

void GameManager::performSettlementPhase() {
    ConsoleIO::println("\n 정산 단계 시작!\n");

    for (auto& book : inventory.getBooks()) {
        if (book->getCondition() == eBookCondition::Damaged) {
            book->repair();
            ConsoleIO::println(AsciiArt::showRestoreBookArt());
            ConsoleIO::println(book->getTitle() + " 복원 완료!");
        }
    }

    // TODO: 추가 정산 과정 필요
    /*auto book = BookFactory::createRandomBook();
    inventory.addBook(book);
    ConsoleIO::println("마지막 책 집필 완료: " + book->getTitle());*/

    std::string ans;
    ConsoleIO::print("인벤토리를 확인하시겠습니까? (y/n): ");
    std::cin >> ans;
    if (ans == "y") uiManager.displayInventory(inventory);
}

void GameManager::endDay() {
    if (levelSystem.checkLevelUp()) {
        uiManager.displayLevelUpMessage(levelSystem.getLevel());
    }
    ConsoleIO::println(AsciiArt::showClosingArt());
    ++day;
}
