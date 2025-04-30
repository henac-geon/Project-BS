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
