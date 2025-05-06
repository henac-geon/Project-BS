#include "NPC.h"    // NPC Ŭ���� ���� ��� ����

/**
 * @brief NPC Ŭ���� ������ ����
 *
 * @param name        NPC�� ���� �̸�
 * @param genre       NPC�� ��ȣ�ϴ� å �帣 (Enums.h�� ���ǵ� eBookGenre)
 * @param mood        NPC�� ��ȣ�ϴ� å ������ (Enums.h�� ���ǵ� eBookMood)
 * @param gold        �ʱ� ��ȭ�� (���� �� ���� �ý��ۿ��� ���)
 * @param magicPower  �ʱ� ������ (Ư�� ��ȣ�ۿ��̳� ���� �ý��ۿ��� ���)
 *
 * �� �����ڿ����� ��� �ʱ�ȭ ����Ʈ�� ����Ͽ� �� ��� ������
 * ���޹��� �μ��� �����ϰ� �����ϰ� �ʱ�ȭ�մϴ�.
 */
NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name), preferredGenre(genre), preferredMood(mood), gold(gold), magicPower(magicPower)
{
    // TODO: �ʿ� �� �ʱ�ȭ �� �߰� ������ ���⿡ ����
    // ��: �⺻ �κ��丮(Book ������)�� �����ϰų�,
    //     �ʱ�ȭ �޽��� ���, ��� ���� ��
}

// NPC�� ���� å�� ���ϴ� �Լ�
bool NPC::rateBook(Book* book) const {
    if (!book) return false;    // ��õ �� �޾��� ���

    switch (requestType) {
    case eRequestType::GenreOnly:    // �帣�� ��õ�޴� Ÿ��
        return book->getGenre() == preferredGenre;
    case eRequestType::MoodOnly:     // ���常 ��õ�޴� Ÿ��
        return book->getMood() == preferredMood;
    case eRequestType::GenreAndMood:     // �Ѵ� ��õ�޴� Ÿ��
        return book->getGenre() == preferredGenre && book->getMood() == preferredMood;
    case eRequestType::AnyBook: // �帣, ���� ������� ��õ�� ������ OK
        return true;
    }

    return false;   // ����
}

/**
* 
* NPC.h���� ������� get �Լ��� set �Լ� ����
* 
*/

std::string NPC::getName() const {
    return name;
}

void NPC::setName(const std::string& newName) {
    name = newName;
}

eBookGenre NPC::getPreferredGenre() const {
    return preferredGenre;
}

void NPC::setPreferredGenre(eBookGenre genre) {
    preferredGenre = genre;
}

eBookMood NPC::getPreferredMood() const {
    return preferredMood;
}

void NPC::setPreferredMood(eBookMood mood) {
    preferredMood = mood;
}

const std::vector<Book*>& NPC::getInventory() const {
    return inventory;
}

int NPC::getGold() const {
    return gold;
}

void NPC::setGold(int newGold) {
    gold = newGold;
}

int NPC::getMagicPower() const {
    return magicPower;
}

void NPC::setMagicPower(int newMagicPower) {
    magicPower = newMagicPower;
}

eRequestType NPC::getRequestType() const {
    return requestType;
}

void NPC::setRequestType(eRequestType type) {
    requestType = type;
}
