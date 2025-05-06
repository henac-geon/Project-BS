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

// NPC ��û Ÿ��
enum class eRequestType {       
    GenreOnly,       // �帣�� �䱸
    MoodOnly,        // ���常 �䱸
    GenreAndMood,    // �� �� �䱸
    AnyBook          // �ƹ��ų�
};

#endif // ENUMS_H
