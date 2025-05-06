#include "Book.h"    // Book 클래스 정의 헤더 포함

/**
 * @brief Book 클래스 생성자 구현
 *
 * @param title        책 제목
 * @param description  책 설명 또는 요약
 * @param genre        책 장르 (Enums.h에 정의된 eBookGenre)
 * @param mood         책 분위기 (Enums.h에 정의된 eBookMood)
 * @param length       책 분량 (페이지 수 혹은 읽기에 필요한 분량)
 * @param edge         책 앳지요소
 * @param etc          책 기타요소
 * 생성자에서는 멤버 초기화 리스트를 사용하여 모든 멤버를 안전하게 초기화합니다.
 * 기본적으로 isDamaged는 false로 설정하여 손상되지 않은 상태로 시작하며,
 * damageType은 eDamageType::None(손상 없음), condition은 eBookCondition::Perfect(완전)로 초기화합니다.
 */
Book::Book(const std::string& title,
    const std::string& description,
    eBookGenre genre,
    eBookMood mood,
    int length,
    eBookEdge edge,
    eBookEtc etc)
    : title(title),               // 제목 초기화
    description(description),   // 설명 초기화
    genre(genre),               // 장르 초기화
    mood(mood),                 // 분위기 초기화
    length(length),             // 분량 초기화
    edge(edge),
    etc(etc),
    isDamaged(false),           // 기본 손상 여부: 없음
    damageType(eDamageType::None),       // 기본 손상 유형: 없음
    condition(eBookCondition::Perfect)   // 기본 상태: 완전
{
    // TODO: 필요에 따라 추가 초기화 로직 구현
}

/**
 * @brief 책 제목을 반환하는 Getter
 *
 * @return std::string - 책의 제목
 */
std::string Book::getTitle() const {
    return title;  // title 멤버 반환
}

/**
 * @brief 책 상태를 반환하는 Getter
 *
 * @return eBookCondition - 책의 현재 상태
 *
 * condition 멤버 변수 값을 그대로 반환합니다.
 */
eBookCondition Book::getCondition() const {
    return condition;  // condition 멤버 반환
}
