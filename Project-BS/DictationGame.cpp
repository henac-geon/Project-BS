// ===== DictationGame.cpp =====
#include "DictationGame.h"
#include <iostream>
#include <algorithm>    // std::min, std::shuffle
#include <cmath>        // std::abs
#include <random>       // std::mt19937
#include <chrono>       // system_clock
#include <conio.h>      // _getch()

// UTF-8 문자열을 코드포인트 단위로 분리하는 헬퍼 함수
static std::vector<std::string> splitUTF8(const std::string& s) {
    std::vector<std::string> result;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        size_t len = 1;
        if ((c & 0x80) == 0x00) len = 1;         // ASCII (1바이트)
        else if ((c & 0xE0) == 0xC0) len = 2;    // 2바이트 UTF-8
        else if ((c & 0xF0) == 0xE0) len = 3;    // 3바이트 UTF-8
        else if ((c & 0xF8) == 0xF0) len = 4;    // 4바이트 UTF-8
        if (i + len > s.size()) len = 1;         // 범위를 벗어나면 1바이트로 처리
        result.push_back(s.substr(i, len));      // 코드포인트 하나를 잘라서 저장
        i += len;
    }
    return result;
}

// 생성자: 백스페이스 설정 및 문장 초기화
DictationGame::DictationGame(bool allow)
    : allowBackspace(allow),
    sentences{
        "samPle"
        // 필요하다면 여기에 다른 문장들("안녕하세요", "C++ 프로그래밍" 등)을 추가
    }
{
}

// runSession: 문장 섞기 후 지정 횟수만큼 실행
void DictationGame::runSession(int rounds) {
    auto pool = sentences;
    std::mt19937 gen(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::shuffle(pool.begin(), pool.end(), gen);

    for (int i = 0; i < rounds && i < static_cast<int>(pool.size()); ++i) {
        int typoCount = runSingle(pool[i]);
        (void)typoCount; // 현재 예시에서는 단순히 무시. 필요 시 다른 통계 집계 가능.
    }
}

// runSingle: 한 문장 출력 → 입력 받기 → 오타 수 계산 → 비율·정확도 계산 → 등급 판정 → 출력 → 오타 개수 반환
int DictationGame::runSingle(const std::string& sentence) {
    std::cout << "[타이핑 시작]\n" << sentence << "\n> ";

    // 1) 사용자 입력 받기
    std::string typed = getInput();

    // 2) 오타 개수 계산
    int miss = countTypos(sentence, typed);

    // 3) 오타 비율 계산 (원래 문장 길이 대비)
    double typoRate = calculateTypoRate(sentence, miss);

    // 4) 정확도 계산
    double accuracy = calculateAccuracy(sentence, miss);

    // 5) 등급 판정
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

    // 6) 결과 출력
    std::cout << "오타 수: " << miss << "\n";
    std::cout << "오타 비율: " << (typoRate * 100.0) << "%\n";
    std::cout << "정확도: " << (accuracy * 100.0) << "%\n";
    std::cout << "판정: " << grade << "\n\n";

    // 7) 오타 개수를 반환
    return miss;
}

// countTypos: 코드포인트 단위 비교하여 오타 계산
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

// calculateTypoRate: 원래 문장 대비 오타 비율 계산 (0.0 ~ 1.0)
double DictationGame::calculateTypoRate(const std::string& original, int typoCount) {
    auto origCp = splitUTF8(original);
    size_t totalChars = origCp.size();
    if (totalChars == 0) return 0.0;  // 빈 문자열일 경우
    return static_cast<double>(typoCount) / static_cast<double>(totalChars);
}

// calculateAccuracy: 원래 문장 대비 정확도 계산 (0.0 ~ 1.0)
double DictationGame::calculateAccuracy(const std::string& original, int typoCount) {
    auto origCp = splitUTF8(original);
    size_t totalChars = origCp.size();
    if (totalChars == 0) return 1.0;  // 빈 문자열이면 정확도 100%
    int correctCount = static_cast<int>(totalChars) - typoCount;
    if (correctCount < 0) correctCount = 0;  // 음수 방지
    return static_cast<double>(correctCount) / static_cast<double>(totalChars);
}

// getInput: 문자 단위 입력, 백스페이스 허용 시 처리
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
            _getch(); // 화살표키 등 특수키일 때 두 번째 바이트 버리기
        }
        else {
            input.push_back(static_cast<char>(ch));
            std::cout << static_cast<char>(ch);
        }
    }
    return input;
}
