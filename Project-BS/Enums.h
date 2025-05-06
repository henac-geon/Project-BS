#pragma once

#ifndef ENUMS_H
#define ENUMS_H

//å�帣
enum class eBookGenre {
    Fantasy,
    Romance,
    Horror,
    Mystery,
    SciFi,
    NonFiction
};

//å������
enum class eBookMood {
    Dark,
    Light,
    Emotional,
    Tense,
    Whimsical
};

//å�����
enum class eBookCondition {
    Perfect,   // 100% - like new
    Worn,      // 80-99%
    Damaged,   // 40-79%
    Destroyed  // 0-39%
};

//�������
enum class eBookEdge {
    None,       //����
    Reversal    //����
};

//��Ÿ
enum class eBookEtc {
    None    //����
};

//�ջ�Ÿ��
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
