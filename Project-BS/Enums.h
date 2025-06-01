#pragma once

#ifndef ENUMS_H
#define ENUMS_H

#include <string>
#include <unordered_map>

//
// 책의 장르
//
enum class eBookGenre {
    Fantasy,     // 판타지
    Romance,     // 로맨스
    Horror,      // 공포
    Mystery,     // 미스터리
    SciFi,       // 공상 과학
    Apocalypse,  // 종말/디스토피아
    NonFiction   // 논픽션/실용서
};

//
// 책의 분위기
//
enum class eBookMood {
    Dark,        // 어두운 분위기
    Light,       // 밝은 분위기
    Emotional,   // 감성적인
    Tense,       // 긴장감 있는
    Whimsical    // 엉뚱하고 유쾌한
};

//
// 책의 상태 (퍼센트 기반)
//
enum class eBookCondition {
    Perfect = 100,   // 새것처럼 완벽한 상태 (100%)
    Worn = 80,       // 사용감 있음 (80~99%)
    Damaged = 40,    // 손상됨 (40~79%)
    Destroyed = 0    // 심하게 파손됨 (0~39%)
};

//
// 엣지 요소 - 특별한 요소
//
enum class eBookEdge {
    None,        // 없음
    Reversal     // 반전 있는 이야기
};

//
// 기타 태그
//
enum class eBookEtc {
    None     // 기타 없음
};

//
// 책 손상 타입
//
enum class eDamageType {
    Water,        // 물에 젖음
    Fire,         // 불에 탐
    MagicCurse,   // 마법의 저주
    Tear,         // 찢김
    Lost,         // 분실
    None          // 손상 없음
};

//
// NPC의 요청 조건 유형
//
enum class eRequestType {
    GenreOnly,       // 장르만 요구
    MoodOnly,        // 분위기만 요구
    GenreAndMood,    // 둘 다 요구
    AnyBook          // 아무 책이나 허용
};

//
// NPC 생성 방식
//
enum class eNPCGenerationMode {
    Local = 0,       // 로컬에서 직접 생성
    SimpleAI = 1,    // 단순한 AI 기반 생성
    CreativeAI = 2   // 창의적인 AI 기반 생성
};

#endif // ENUMS_H
