#ifndef DICTATIONGAME_H
#define DICTATIONGAME_H

#include <string>
#include <vector>

// DictationGame 클래스: 받아쓰기 게임 로직
class DictationGame {
public:
    // 생성자: allowBackspace 설정
    explicit DictationGame(bool allowBackspace = false);

    // runSession: 내부에 정의된 문장 목록으로 세션 실행
    //  - rounds: 제시할 문장 수
    void runSession(int rounds);

private:
    bool allowBackspace;                  // 백스페이스 허용 여부
    std::vector<std::string> sentences;   // 게임에 사용할 문장 목록

    // runSingle: 한 문장 실행 후 오타 개수(int) 반환
    //  - sentence: 출력할 문장
    int runSingle(const std::string& sentence);

    // countTypos: 두 문자열 비교하여 오타 수(int) 반환
    static int countTypos(const std::string& original, const std::string& typed);

    // calculateTypoRate: 오타 개수와 원래 문자열을 기준으로 오타 비율 계산
    //  - original: 원래 문장
    //  - typoCount: 이미 계산된 오타 수
    //  - 반환값: 오타 비율(0.0 ~ 1.0)
    static double calculateTypoRate(const std::string& original, int typoCount);

    // calculateAccuracy: 오타 수와 원래 문자열을 기준으로 정확도 계산
    //  - original: 원래 문장
    //  - typoCount: 이미 계산된 오타 수
    //  - 반환값: 정확도(0.0 ~ 1.0)
    static double calculateAccuracy(const std::string& original, int typoCount);

    // getInput: 문자 단위 입력 수집 (백스페이스 처리)
    std::string getInput();
};

#endif // DICTATIONGAME_H
