// ===== DictationGame.cpp =====
#include "DictationGame.h"
#include <iostream>
#include <algorithm>    // std::min, std::shuffle
#include <cmath>        // std::abs
#include <random>       // std::mt19937
#include <chrono>       // system_clock
#include <conio.h>      // _getch()

// UTF-8 ���ڿ��� �ڵ�����Ʈ ������ �и��ϴ� ���� �Լ�
static std::vector<std::string> splitUTF8(const std::string& s) {
    std::vector<std::string> result;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        size_t len = 1;
        if ((c & 0x80) == 0x00) len = 1;         // ASCII (1����Ʈ)
        else if ((c & 0xE0) == 0xC0) len = 2;    // 2����Ʈ UTF-8
        else if ((c & 0xF0) == 0xE0) len = 3;    // 3����Ʈ UTF-8
        else if ((c & 0xF8) == 0xF0) len = 4;    // 4����Ʈ UTF-8
        if (i + len > s.size()) len = 1;         // ������ ����� 1����Ʈ�� ó��
        result.push_back(s.substr(i, len));      // �ڵ�����Ʈ �ϳ��� �߶� ����
        i += len;
    }
    return result;
}

// ������: �齺���̽� ���� �� ���� �ʱ�ȭ
DictationGame::DictationGame(bool allow)
    : allowBackspace(allow),
    sentences{
        "samPle"
        // �ʿ��ϴٸ� ���⿡ �ٸ� �����("�ȳ��ϼ���", "C++ ���α׷���" ��)�� �߰�
    }
{
}

// runSession: ���� ���� �� ���� Ƚ����ŭ ����
void DictationGame::runSession(int rounds) {
    auto pool = sentences;
    std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(pool.begin(), pool.end(), gen);

    for (int i = 0; i < rounds && i < static_cast<int>(pool.size()); ++i) {
        int typoCount = runSingle(pool[i]);
        (void)typoCount; // ���� ���ÿ����� �ܼ��� ����. �ʿ� �� �ٸ� ��� ���� ����.
    }
}

// runSingle: �� ���� ��� �� �Է� �ޱ� �� ��Ÿ �� ��� �� ��������Ȯ�� ��� �� ��� ���� �� ��� �� ��Ÿ ���� ��ȯ
int DictationGame::runSingle(const std::string& sentence) {
    std::cout << "[Ÿ���� ����]\n" << sentence << "\n> ";

    // 1) ����� �Է� �ޱ�
    std::string typed = getInput();

    // 2) ��Ÿ ���� ���
    int miss = countTypos(sentence, typed);

    // 3) ��Ÿ ���� ��� (���� ���� ���� ���)
    double typoRate = calculateTypoRate(sentence, miss);

    // 4) ��Ȯ�� ���
    double accuracy = calculateAccuracy(sentence, miss);

    // 5) ��� ����
    std::string grade;
    if (accuracy >= 0.90) {
        grade = "good";
    }
    else if (accuracy >= 0.70) {
        grade = "not bad";
    }
    else if (accuracy >= 0.50) {
        grade = "bad";
    }
    else {
        grade = "explosion";
    }

    // 6) ��� ���
    std::cout << "��Ÿ ��: " << miss << "\n";
    std::cout << "��Ÿ ����: " << (typoRate * 100.0) << "%\n";
    std::cout << "��Ȯ��: " << (accuracy * 100.0) << "%\n";
    std::cout << "����: " << grade << "\n\n";

    // 7) ��Ÿ ������ ��ȯ
    return miss;
}

// countTypos: �ڵ�����Ʈ ���� ���Ͽ� ��Ÿ ���
int DictationGame::countTypos(const std::string& original, const std::string& typed) {
    auto origCp = splitUTF8(original);
    auto typedCp = splitUTF8(typed);

    int typos = 0;
    size_t len = std::min(origCp.size(), typedCp.size());
    for (size_t i = 0; i < len; ++i) {
        if (origCp[i] != typedCp[i]) ++typos;
    }
    typos += std::abs(static_cast<int>(origCp.size() - typedCp.size()));
    return typos;
}

// calculateTypoRate: ���� ���� ��� ��Ÿ ���� ��� (0.0 ~ 1.0)
double DictationGame::calculateTypoRate(const std::string& original, int typoCount) {
    auto origCp = splitUTF8(original);
    size_t totalChars = origCp.size();
    if (totalChars == 0) return 0.0;  // �� ���ڿ��� ���
    return static_cast<double>(typoCount) / static_cast<double>(totalChars);
}

// calculateAccuracy: ���� ���� ��� ��Ȯ�� ��� (0.0 ~ 1.0)
double DictationGame::calculateAccuracy(const std::string& original, int typoCount) {
    auto origCp = splitUTF8(original);
    size_t totalChars = origCp.size();
    if (totalChars == 0) return 1.0;  // �� ���ڿ��̸� ��Ȯ�� 100%
    int correctCount = static_cast<int>(totalChars) - typoCount;
    if (correctCount < 0) correctCount = 0;  // ���� ����
    return static_cast<double>(correctCount) / static_cast<double>(totalChars);
}

// getInput: ���� ���� �Է�, �齺���̽� ��� �� ó��
std::string DictationGame::getInput() {
    std::string input;
    while (true) {
        int ch = _getch();
        if (ch == '\r' || ch == '\n') {
            std::cout << std::endl;
            break;
        }
        if (ch == '\b') {
            if (allowBackspace && !input.empty()) {
                input.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (ch == 0 || ch == 224) {
            _getch(); // ȭ��ǥŰ �� Ư��Ű�� �� �� ��° ����Ʈ ������
        }
        else {
            input.push_back(static_cast<char>(ch));
            std::cout << static_cast<char>(ch);
        }
    }
    return input;
}
