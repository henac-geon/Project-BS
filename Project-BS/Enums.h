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
    Perfect,   // 100% - like new
    Worn,      // 80-99%
    Damaged,   // 40-79%
    Destroyed  // 0-39%
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

#endif // ENUMS_H
