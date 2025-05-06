#pragma once

#ifndef ENUMS_H
#define ENUMS_H

enum class eBookGenre {
    Fantasy,
    Romance,
    Horror,
    Mystery,
    SciFi,
    NonFiction
};

enum class eBookMood {
    Dark,
    Light,
    Emotional,
    Tense,
    Whimsical
};

enum class eBookCondition {
    Perfect,   // 100% - like new
    Worn,      // 80-99%
    Damaged,   // 40-79%
    Destroyed  // 0-39%
};

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
