#include "Book.h"    // Book 클래스 정의 헤더 포함

/**
 * @brief Book 클래스 생성자 구현
 *
 * @param title        책 제목
 * @param description  책 설명 또는 요약
 * @param genre        책 장르 (Enums.h에 정의된 eBookGenre)
 * @param mood         책 분위기 (Enums.h에 정의된 eBookMood)
 * @param length       책 분량 (페이지 수 혹은 읽기에 필요한 분량)
 *
 * 생성자에서는 멤버 초기화 리스트를 사용하여 모든 멤버를 안전하게 초기화합니다.
 * 기본적으로 isDamaged는 false로 설정하여 손상되지 않은 상태로 시작하며,
 * damageType은 eDamageType::Lost(분실), condition은 eBookCondition::Perfect(완전)로 초기화합니다.
 */
Book::Book(const std::string& title, const std::string& description, eBookGenre genre, eBookMood mood, int length)
    : title(title), description(description), genre(genre), mood(mood), length(length), isDamaged(false), damageType(eDamageType::None), condition(eBookCondition::Perfect)
{
    // TODO: 필요에 따라 생성 시 추가 초기화 로직 추가
    // 예: 초기 설명 출력, 통계 기록, 인벤토리에 자동 추가 등
}

/**
 * @brief 책 제목을 반환하는 Getter
 *
 * @return std::string - 책의 제목
 *
 * 간단한 인라인 함수로, 멤버 변수 title을 읽기 전용으로 반환합니다.
 */
std::string Book::getTitle() const {
    return title;  // title 멤버 변수 반환
}
