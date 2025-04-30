#ifndef MINIGAME_H
#define MINIGAME_H

#include "Book.h"  // Book 클래스 정의를 포함하여, 미니게임에서 사용할 책 객체 참조

/**
 * @class MiniGame
 * @brief 책(Book)을 활용한 다양한 미니게임 인터페이스
 *
 * 파생 클래스에서 구체적인 미니게임 로직을 구현하기 위해
 * 인터페이스 역할을 수행합니다. play() 메서드를 통해
 * 책 객체를 활용한 게임 진행 및 결과 반환을 처리합니다.
 */
class MiniGame {
public:
    /**
     * @brief 가상 소멸자
     *
     * 파생 클래스에서 동적 자원을 안전하게 해제하기 위해 선언합니다.
     */
    virtual ~MiniGame() = default;

    /**
     * @brief 미니게임 실행 함수
     *
     * @param book  게임에 사용할 Book 객체 포인터
     * @return bool - 게임 성공 여부 (true: 성공/이김, false: 실패/짐)
     *
     * 순수 가상 함수로, 파생 클래스에서 책 데이터를 기반으로
     * 구체적인 게임 로직을 구현하여 성공/실패를 판단합니다.
     */
    virtual bool play(Book* book) = 0;
};

#endif // MINIGAME_H