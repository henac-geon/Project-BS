// main.cpp
#include "DictationGame.h"

int main() {
    // �齺���̽� ��� ���� ����(false�� �齺���̽��� �۵����� ����)
    DictationGame game(false);

    // 5���� ���带 ����(���� ���� ������ 1�����, �� ���� ���� �����)
    game.runSession(5);

    return 0;
}
