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
    condition(eBookCondition::Perfect),   // 기본 상태: 완전
    conditionValue(100)  // 새 책으로 초기화
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

int Book::getConditionValue() const {
    return conditionValue;
}

std::string Book::getConditionPercentText() const {
    return std::to_string(conditionValue) + "%";
}


std::string Book::getGenreName() const {
    switch (genre) {
    case eBookGenre::Fantasy: return "판타지";
    case eBookGenre::Romance: return "로맨스";
    case eBookGenre::Horror: return "공포";
    case eBookGenre::Mystery: return "미스터리";
    case eBookGenre::SciFi: return "SF";
    case eBookGenre::Apocalypse: return "종말";
    case eBookGenre::NonFiction: return "논픽션";
    default: return "기타";
    }
}

std::string Book::getMoodName() const {
    switch (mood) {
    case eBookMood::Dark: return "암울";
    case eBookMood::Light: return "밝음";
    case eBookMood::Emotional: return "감정적";
    case eBookMood::Tense: return "긴장감";
    case eBookMood::Whimsical: return "기발함";
    default: return "중립";
    }
}

std::string Book::getEdgeName() const {
    switch (edge) {
    //case eBookEdge::Twist: return "반전";
    case eBookEdge::None: return "없음";
    default: return "기타";
    }
}

std::string Book::getEtcName() const {
    switch (etc) {
    case eBookEtc::None: return "없음";
    //case eBookEtc::Adult: return "성인";
    //case eBookEtc::Illustrated: return "삽화";
    default: return "기타";
    }
}

//std::string Book::getStockSymbol() const {
//    switch (condition) {
//    case eBookCondition::Good: return "●";
//    case eBookCondition::Fair: return "○";
//    case eBookCondition::Bad: return "×";
//    default: return "?";
//    }
//}

int Book::getVolume() const {
    return length;
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

void Book::setCondition(eBookCondition newCondition) {
    condition = newCondition;

    // 선택: 수치화 값도 자동 조정 (일관성 유지용)
    switch (condition) {
        case eBookCondition::Perfect:
            conditionValue = 100;
        case eBookCondition::Worn:
            conditionValue = getRandomInRange(80, 99);
        case eBookCondition::Damaged:
            conditionValue = getRandomInRange(40, 79);
        case eBookCondition::Destroyed:
            conditionValue = getRandomInRange(0, 39);
        default:
            conditionValue = -1;  // 에러 상황
    }
}

void Book::setIsDamaged(bool damaged) {
    isDamaged = damaged;

    // 선택: 손상 상태에 따라 자동으로 condition 조정
    if (!damaged) {
        condition = eBookCondition::Perfect;
        conditionValue = 100;
        damageType = eDamageType::None;
    }
}

void Book::setDamageType(eDamageType type) {
    damageType = type;

    // 선택: damageType에 따라 손상 여부 자동 처리
    if (type != eDamageType::None) {
        isDamaged = true;
    }
}
