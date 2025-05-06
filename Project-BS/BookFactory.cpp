#include "BookFactory.h"
#include "FantasyBook.h"  // FantasyBook 클래스 정의 헤더 포함
#include "ScienceBook.h"  // ScienceBook 클래스 정의 헤더 포함
#include <cstdlib>  // rand() 함수 사용을 위한 헤더

/**
 * @brief 랜덤한 책을 생성하는 팩토리 함수
 *
 * @return Book* - 생성된 랜덤 책 객체 포인터
 *
 * 길이는 50~149 사이의 랜덤 값으로 설정되며,
 * 장르는 판타지(Fantasy), 분위기는 기발한(Whimsical)으로 고정합니다.
 */
Book* BookFactory::createRandomBook() {
    int len = rand() % 100 + 50;  // 0~99 사이 랜덤 +50 => 50~149
    // 고정된 장르와 분위기로 책 생성
    return createBook(eBookGenre::Fantasy, eBookMood::Whimsical, len, eBookEdge::None, eBookEtc::None);
}

/**
 * @brief 지정된 속성의 책을 생성하는 팩토리 함수
 *
 * @param genre   생성할 책의 장르
 * @param mood    생성할 책의 분위기
 * @param length  책의 분량(페이지 수 등)
 * @return Book* - 생성된 책 객체 포인터
 *
 * 장르에 따라 파생 클래스(FantasyBook, ScienceBook 등)를 결정하여
 * 해당 객체를 동적으로 할당 후 반환합니다.
 * 지원하지 않는 장르의 경우 기본 판타지 책을 생성합니다.
 */
Book* BookFactory::createBook(eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc
    ) {
    switch (genre) {
    case eBookGenre::Fantasy:
        // 판타지 장르용 책 생성
        return new FantasyBook(
            "Random Fantasy",      // 제목
            "A random fantasy book", // 설명
            length
            );                // 분량

    case eBookGenre::SciFi:
        // 공상과학 장르용 책 생성
        return new ScienceBook(
            "Random SciFi",         // 제목
            "A random science book", // 설명
            length);                // 분량

    default:
        // 지원하지 않는 장르는 기본 판타지 책으로 처리
        return new FantasyBook(
            "Default Fantasy",      // 제목
            "Default",              // 설명
            length);                // 분량
    }
}
