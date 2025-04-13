// text_game_system.cpp
// =======================================================
// Text-based RPG Book Game
// -------------------------------------------------------
// 이 게임은 책을 관리하고 다양한 NPC에게 책을 제공하는
// 텍스트 기반의 콘솔 RPG 시스템입니다.
// -------------------------------------------------------
// 주요 구성 요소:
// - Book (추상 클래스): 다양한 책 구현의 기반
// - NPC (추상 클래스): 책을 요청하고 평가하는 캐릭터
// - Inventory: 플레이어가 소유한 책 관리
// - UIManager: 사용자 인터페이스 출력 전담
// - GameManager: 게임의 주요 루프 및 흐름 담당
// =======================================================

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

// ======================= ENUM ======================= //

/// @brief 책 장르를 정의합니다.
enum class eBookGenre { Fantasy, Romance, Horror, Mystery, SciFi, NonFiction };

/// @brief 책의 분위기를 정의합니다.
enum class eBookMood { Dark, Light, Emotional, Tense, Whimsical };

/// @brief 책의 상태를 나타냅니다.
enum class eBookCondition { Perfect, Worn, Damaged, Destroyed };

/// @brief 손상 유형을 정의합니다.
enum class eDamageType { Water, Fire, MagicCurse, Tear, Lost };

// ===================== ABSTRACT CLASS: Book ===================== //

/// @brief 추상 책 클래스. 모든 책의 공통 속성과 메서드를 정의합니다.
class Book {
protected:
    string title;             ///< 책 제목
    string description;       ///< 책 설명
    eBookGenre genre;         ///< 장르
    eBookMood mood;           ///< 분위기
    int length;               ///< 페이지 수
    bool isDamaged;           ///< 손상 여부
    eDamageType damageType;   ///< 손상 종류
    eBookCondition condition; ///< 상태 (퍼펙트, 낡음 등)

public:
    /// @brief 생성자
    Book(string t, string desc, eBookGenre g, eBookMood m, int l)
        : title(t), description(desc), genre(g), mood(m), length(l),
        isDamaged(false), damageType(eDamageType::Lost), condition(eBookCondition::Perfect) {
    }

    /// @brief 순수 가상 함수 - 책 정보 출력
    virtual void displayInfo() = 0;

    /// @brief 책 수리 함수 - 손상 복구
    void repair() {
        if (isDamaged) {
            isDamaged = false;
            condition = eBookCondition::Worn;
            cout << title << " has been repaired to worn condition.\n";
        }
        else {
            cout << title << " does not need repair.\n";
        }
    }

    // Getter 함수들
    eBookCondition getCondition() const { return condition; }
    string getTitle() const { return title; }
    eBookGenre getGenre() const { return genre; }
    eBookMood getMood() const { return mood; }
};

// ===================== CONCRETE CLASS: FantasyBook ===================== //

/// @brief 판타지 장르 책 클래스
class FantasyBook : public Book {
public:
    FantasyBook(string t, string desc, int len)
        : Book(t, desc, eBookGenre::Fantasy, eBookMood::Whimsical, len) {
    }

    void displayInfo() override {
        cout << "[Fantasy Book] " << title << " - " << description << ", " << length << " pages\n";
    }
};

// ===================== ABSTRACT CLASS: NPC ===================== //

/// @brief NPC 추상 클래스 - 책 요청 및 평가
class NPC {
protected:
    string name;
    eBookGenre preferredGenre;
    eBookMood preferredMood;
    int gold;
    int magicPower;

public:
    NPC(string n, eBookGenre g, eBookMood m)
        : name(n), preferredGenre(g), preferredMood(m), gold(100), magicPower(50) {
    }

    /// @brief 책 요청 로직
    virtual shared_ptr<Book> requestBook(const vector<shared_ptr<Book>>& books) = 0;

    /// @brief 책 평가 로직
    virtual bool rateBook(shared_ptr<Book> book) = 0;

    /// @brief 손상 보상 처리
    virtual void compensateForDamage(shared_ptr<Book> book) {
        cout << name << " compensates for the damage.\n";
    }

    string getName() const { return name; }
};

// ===================== CONCRETE CLASS: StudentNPC ===================== //

/// @brief 학생 NPC 클래스 - 판타지, 위트 선호
class StudentNPC : public NPC {
public:
    StudentNPC(string n)
        : NPC(n, eBookGenre::Fantasy, eBookMood::Whimsical) {
    }

    shared_ptr<Book> requestBook(const vector<shared_ptr<Book>>& books) override {
        for (auto& book : books) {
            if (book->getGenre() == preferredGenre && book->getMood() == preferredMood)
                return book;
        }
        return nullptr;
    }

    bool rateBook(shared_ptr<Book> book) override {
        cout << name << " liked the book " << book->getTitle() << "!\n";
        return true;
    }
};

// ===================== SYSTEM CLASS: Inventory ===================== //

/// @brief 책 인벤토리 관리 시스템
class Inventory {
private:
    vector<shared_ptr<Book>> books; ///< 책 목록

public:
    /// @brief 책 추가
    void addBook(shared_ptr<Book> book) {
        books.push_back(book);
    }

    /// @brief 인벤토리 내 책 출력
    void displayBooks() {
        for (size_t i = 0; i < books.size(); ++i) {
            cout << i + 1 << ". ";
            books[i]->displayInfo();
        }
    }

    /// @brief 책 목록 반환
    const vector<shared_ptr<Book>>& getBooks() const {
        return books;
    }
};

// ===================== SYSTEM CLASS: UIManager ===================== //

/// @brief 사용자 인터페이스 관리 클래스
class UIManager {
public:
    /// @brief 메인 메뉴 출력
    void displayMainMenu() {
        cout << "\n==== Book RPG Menu ====\n";
        cout << "1. View Inventory\n2. Serve NPC\n3. Exit\n> ";
    }

    /// @brief NPC 상호작용 출력
    void displayNPCInteraction(NPC& npc) {
        cout << npc.getName() << " has appeared!\n";
    }
};

// ===================== SYSTEM CLASS: GameManager ===================== //

/// @brief 게임의 핵심 로직을 담당하는 매니저
class GameManager {
private:
    Inventory inventory;
    vector<shared_ptr<NPC>> npcs;
    UIManager ui;

public:
    /// @brief 생성자 - 초기 상태 설정
    GameManager() {
        srand((unsigned)time(0));
        inventory.addBook(make_shared<FantasyBook>("Wizard's Tale", "An epic journey.", 350));
        npcs.push_back(make_shared<StudentNPC>("Alice"));
    }

    /// @brief 게임 루프 시작
    void gameLoop() {
        while (true) {
            ui.displayMainMenu();
            int choice;
            cin >> choice;

            if (choice == 1) {
                inventory.displayBooks();
            }
            else if (choice == 2) {
                serveNPCs();
            }
            else {
                cout << "Goodbye!\n";
                break;
            }
        }
    }

    /// @brief NPC 처리 - 요청 및 응답
    void serveNPCs() {
        for (auto& npc : npcs) {
            ui.displayNPCInteraction(*npc);
            auto book = npc->requestBook(inventory.getBooks());
            if (book) {
                cout << npc->getName() << " borrowed " << book->getTitle() << ".\n";
                npc->rateBook(book);
            }
            else {
                cout << "No suitable book found.\n";
            }
        }
    }
};

// ===================== MAIN ===================== //

/// @brief main 함수 - 게임 실행 시작
int main() {
    GameManager game;
    game.gameLoop();
    return 0;
}