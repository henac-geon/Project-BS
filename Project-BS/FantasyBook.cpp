#include "FantasyBook.h"


//�帣���� �׷����� �ϴµ� ���峪 ���Ŵ� ��� ���ܿ��� �����غ�����.
FantasyBook::FantasyBook(const std::string& title, const std::string& description, int length)
    : Book(title, description, eBookGenre::Fantasy, eBookMood::Whimsical, length, eBookEdge::None, eBookEtc::None) {
}

void FantasyBook::repair() {
    condition = eBookCondition::Perfect;
    isDamaged = false;
}

void FantasyBook::displayInfo() const {
    std::cout << "Fantasy Book: " << title << " - " << description << " (" << length << " pages)" << std::endl;
}
