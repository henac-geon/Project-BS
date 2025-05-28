#include "Book.h"    // Book 클래스 정의 헤더 포함

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
    etc(etc),                   // 기타 정보 초기화
    isDamaged(false),           // 기본 손상 여부: 없음
    damageType(eDamageType::None),       // 기본 손상 유형: 없음
    condition(eBookCondition::Perfect)   // 기본 상태: 완전
{
    // TODO: 필요에 따라 추가 초기화 로직 구현
}

std::string Book::getTitle() const {
    return title;  // title 멤버 반환
}

eBookCondition Book::getCondition() const {
    return condition;  // condition 멤버 반환
}

eBookGenre Book::getGenre() const {
    return genre;
}

eBookMood Book::getMood() const {
    return mood;
}

int Book::getDamage() const {
    switch (condition) {
    case eBookCondition::Perfect:
        return 100;
    case eBookCondition::Worn:
        return getRandomInRange(80, 99);
    case eBookCondition::Damaged:
        return getRandomInRange(40, 79);
    case eBookCondition::Destroyed:
        return getRandomInRange(0, 39);
    default:
        return -1;  // 에러 상황
    }
}

// 책의 상태를 범위 형태로 반환하는 함수
int Book::getRandomInRange(int min, int max) const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void Book::setTitle(const std::string& newTitle) {
    title = newTitle;
}
