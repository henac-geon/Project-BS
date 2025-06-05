#ifndef DICTATIONGAME_H
#define DICTATIONGAME_H

#include <string>
#include <vector>

// DictationGame Ŭ����: �޾ƾ��� ���� ����
class DictationGame {
public:
    // ������: allowBackspace ����
    explicit DictationGame(bool allowBackspace = false);

    // runSession: ���ο� ���ǵ� ���� ������� ���� ����
    //  - rounds: ������ ���� ��
    void runSession(int rounds);

private:
    bool allowBackspace;                  // �齺���̽� ��� ����
    std::vector<std::string> sentences;   // ���ӿ� ����� ���� ���

    // runSingle: �� ���� ���� �� ��Ÿ ����(int) ��ȯ
    //  - sentence: ����� ����
    int runSingle(const std::string& sentence);

    // countTypos: �� ���ڿ� ���Ͽ� ��Ÿ ��(int) ��ȯ
    static int countTypos(const std::string& original, const std::string& typed);

    // calculateTypoRate: ��Ÿ ������ ���� ���ڿ��� �������� ��Ÿ ���� ���
    //  - original: ���� ����
    //  - typoCount: �̹� ���� ��Ÿ ��
    //  - ��ȯ��: ��Ÿ ����(0.0 ~ 1.0)
    static double calculateTypoRate(const std::string& original, int typoCount);

    // calculateAccuracy: ��Ÿ ���� ���� ���ڿ��� �������� ��Ȯ�� ���
    //  - original: ���� ����
    //  - typoCount: �̹� ���� ��Ÿ ��
    //  - ��ȯ��: ��Ȯ��(0.0 ~ 1.0)
    static double calculateAccuracy(const std::string& original, int typoCount);

    // getInput: ���� ���� �Է� ���� (�齺���̽� ó��)
    std::string getInput();
};

#endif // DICTATIONGAME_H
