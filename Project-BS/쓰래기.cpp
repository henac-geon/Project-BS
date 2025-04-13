// text_game_system.cpp
// =======================================================
// Text-based RPG Book Game
// -------------------------------------------------------
// �� ������ å�� �����ϰ� �پ��� NPC���� å�� �����ϴ�
// �ؽ�Ʈ ����� �ܼ� RPG �ý����Դϴ�.
// -------------------------------------------------------
// �ֿ� ���� ���:
// - Book (�߻� Ŭ����): �پ��� å ������ ���
// - NPC (�߻� Ŭ����): å�� ��û�ϰ� ���ϴ� ĳ����
// - Inventory: �÷��̾ ������ å ����
// - UIManager: ����� �������̽� ��� ����
// - GameManager: ������ �ֿ� ���� �� �帧 ���
// =======================================================

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

// ======================= ENUM ======================= //

/// @brief å �帣�� �����մϴ�.
enum class eBookGenre { Fantasy, Romance, Horror, Mystery, SciFi, NonFiction };

/// @brief å�� �����⸦ �����մϴ�.
enum class eBookMood { Dark, Light, Emotional, Tense, Whimsical };

/// @brief å�� ���¸� ��Ÿ���ϴ�.
enum class eBookCondition { Perfect, Worn, Damaged, Destroyed };

/// @brief �ջ� ������ �����մϴ�.
enum class eDamageType { Water, Fire, MagicCurse, Tear, Lost };

// ===================== ABSTRACT CLASS: Book ===================== //

/// @brief �߻� å Ŭ����. ��� å�� ���� �Ӽ��� �޼��带 �����մϴ�.
class Book {
protected:
    string title;             ///< å ����
    string description;       ///< å ����
    eBookGenre genre;         ///< �帣
    eBookMood mood;           ///< ������
    int length;               ///< ������ ��
    bool isDamaged;           ///< �ջ� ����
    eDamageType damageType;   ///< �ջ� ����
    eBookCondition condition; ///< ���� (����Ʈ, ���� ��)

public:
    /// @brief ������
    Book(string t, string desc, eBookGenre g, eBookMood m, int l)
        : title(t), description(desc), genre(g), mood(m), length(l),
        isDamaged(false), damageType(eDamageType::Lost), condition(eBookCondition::Perfect) {
    }

    /// @brief ���� ���� �Լ� - å ���� ���
    virtual void displayInfo() = 0;

    /// @brief å ���� �Լ� - �ջ� ����
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

    // Getter �Լ���
    eBookCondition getCondition() const { return condition; }
    string getTitle() const { return title; }
    eBookGenre getGenre() const { return genre; }
    eBookMood getMood() const { return mood; }
};

// ===================== CONCRETE CLASS: FantasyBook ===================== //

/// @brief ��Ÿ�� �帣 å Ŭ����
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

/// @brief NPC �߻� Ŭ���� - å ��û �� ��
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

    /// @brief å ��û ����
    virtual shared_ptr<Book> requestBook(const vector<shared_ptr<Book>>& books) = 0;

    /// @brief å �� ����
    virtual bool rateBook(shared_ptr<Book> book) = 0;

    /// @brief �ջ� ���� ó��
    virtual void compensateForDamage(shared_ptr<Book> book) {
        cout << name << " compensates for the damage.\n";
    }

    string getName() const { return name; }
};

// ===================== CONCRETE CLASS: StudentNPC ===================== //

/// @brief �л� NPC Ŭ���� - ��Ÿ��, ��Ʈ ��ȣ
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

/// @brief å �κ��丮 ���� �ý���
class Inventory {
private:
    vector<shared_ptr<Book>> books; ///< å ���

public:
    /// @brief å �߰�
    void addBook(shared_ptr<Book> book) {
        books.push_back(book);
    }

    /// @brief �κ��丮 �� å ���
    void displayBooks() {
        for (size_t i = 0; i < books.size(); ++i) {
            cout << i + 1 << ". ";
            books[i]->displayInfo();
        }
    }

    /// @brief å ��� ��ȯ
    const vector<shared_ptr<Book>>& getBooks() const {
        return books;
    }
};

// ===================== SYSTEM CLASS: UIManager ===================== //

/// @brief ����� �������̽� ���� Ŭ����
class UIManager {
public:
    /// @brief ���� �޴� ���
    void displayMainMenu() {
        cout << "\n==== Book RPG Menu ====\n";
        cout << "1. View Inventory\n2. Serve NPC\n3. Exit\n> ";
    }

    /// @brief NPC ��ȣ�ۿ� ���
    void displayNPCInteraction(NPC& npc) {
        cout << npc.getName() << " has appeared!\n";
    }
};

// ===================== SYSTEM CLASS: GameManager ===================== //

/// @brief ������ �ٽ� ������ ����ϴ� �Ŵ���
class GameManager {
private:
    Inventory inventory;
    vector<shared_ptr<NPC>> npcs;
    UIManager ui;

public:
    /// @brief ������ - �ʱ� ���� ����
    GameManager() {
        srand((unsigned)time(0));
        inventory.addBook(make_shared<FantasyBook>("Wizard's Tale", "An epic journey.", 350));
        npcs.push_back(make_shared<StudentNPC>("Alice"));
    }

    /// @brief ���� ���� ����
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

    /// @brief NPC ó�� - ��û �� ����
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

/// @brief main �Լ� - ���� ���� ����
int main() {
    GameManager game;
    game.gameLoop();
    return 0;
}