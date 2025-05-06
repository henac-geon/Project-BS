#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <string>     // std::string 사용을 위한 헤더
#include "Enums.h"   // eBookGenre, eBookMood, eDamageType, eBookCondition 열거형 정의 포함

/**
 * @class Book
 * @brief 책(Book) 추상 클래스
 *
 * 게임 또는 애플리케이션 내에서 책 객체를 모델링합니다.
 * 제목, 설명, 장르, 분위기, 분량 등의 메타데이터와 손상 상태를 관리하며,
 * 수리(repair) 및 정보 표시(displayInfo) 기능을 파생 클래스에서 구현하도록 합니다.
 */
class Book {
protected:
    std::string title;           // 책 제목
    std::string description;     // 책 설명 또는 요약
    eBookGenre genre;            // 책 장르 (Enums.h 참고)
    eBookMood mood;              // 책이 전달하는 분위기 (Enums.h 참고)
    int length;                  // 책의 분량 (페이지 수 또는 읽기 소요 시간)
    eBookEdge edge;              // 책의 반전 요소
    eBookEtc etc;                // 기타
    bool isDamaged;              // 책 손상 여부 (true: 손상됨, false: 양호)
    eDamageType damageType;      // 손상 유형 (Enums.h에 정의된 eDamageType)
    eBookCondition condition;    // 책 상태 (Enums.h에 정의된 eBookCondition)

public:
    /**
     * @brief 생성자
     * @param title        책 제목
     * @param description  책 설명 또는 요약
     * @param genre        책 장르
     * @param mood         책 분위기
     * @param length       책 분량
     * @param edge         책 반전요소
     * @param etc          책 기타
     *
     * 생성자에서는 전달받은 메타데이터로 멤버 변수를 초기화하고,
     * 기본적으로 손상 상태를 "양호"로 설정합니다.
     */
    Book(const std::string& title,
        const std::string& description,
        eBookGenre genre,
        eBookMood mood,
        int length,
        eBookEdge edge,
        eBookEtc etc);

    /**
     * @brief 가상 소멸자
     *
     * 파생 클래스에서 동적 할당된 자원을 안전하게 해제하기 위해 선언합니다.
     */
    virtual ~Book() = default;

    /**
     * @brief 책을 수리하는 함수
     *
     * 순수 가상 함수로, 파생 클래스에서 손상된 책을 수리하는 구체 로직을 구현해야 합니다.
     */
    virtual void repair() = 0;

    /**
     * @brief 책 정보를 표시하는 함수
     *
     * 순수 가상 함수로, 파생 클래스에서 책의 메타데이터와 상태를 출력하는 구체 로직을 구현해야 합니다.
     */
    virtual void displayInfo() const = 0;

    /**
     * @brief 책 제목을 반환하는 getter
     * @return std::string - 책의 제목
     */
    std::string getTitle() const;

    /**
     * @brief 책 상태를 반환하는 getter
     * @return eBookCondition - 책의 상태
     */
    eBookCondition getCondition() const;

    /**
     * @brief 책 장르를 반환하는 getter
     * @return eBookGenre - 책의 장르
     */
    eBookGenre getGenre() const;

    /**
     * @brief 책 분위기를 반환하는 getter
     * @return eBookMood - 책의 분위기
     */
    eBookMood getMood() const;
};

#endif // BOOK_H