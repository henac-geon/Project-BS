#pragma once

#ifndef ENUMS_H
#define ENUMS_H

//책장르
enum class eBookGenre {
    Fantasy,
    Romance,
    Horror,
    Mystery,
    SciFi,
    Apocalypse,
    NonFiction
};

//책분위기
enum class eBookMood {
    Dark,
    Light,
    Emotional,
    Tense,
    Whimsical
};

//책컨디션
enum class eBookCondition {
    Perfect = 100,   // 100% - like new
    Worn = 80,      // 80-99%
    Damaged = 40,   // 40-79%
    Destroyed = 0  // 0-39%
};

//엣지요소
enum class eBookEdge {
    None,       //없음
    Reversal    //반전
};

//기타
enum class eBookEtc {
    None    //없음
};

//손상타입
enum class eDamageType {
    Water,
    Fire,
    MagicCurse,
    Tear,
    Lost,
    None
};


enum class eNPCType {
    Student,
    Wizard,
    Merchant,
    Librarian
};

// NPC 요청 타입
enum class eRequestType {       
    GenreOnly,       // 장르만 요구
    MoodOnly,        // 무드만 요구
    GenreAndMood,    // 둘 다 요구
    AnyBook          // 아무거나
};

#endif // ENUMS_H
