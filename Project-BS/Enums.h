#pragma once

#ifndef ENUMS_H
#define ENUMS_H

#include <string>
#include <unordered_map>

enum class WritingElementCategory {
    Genre,
    Mood,
    Length,
    Edge,
    Etc
};

// 책의 장르
enum class eBookGenre {
    Fantasy,     // 판타지
    Romance,     // 로맨스
    Horror,      // 호러
    Mystery,     // 미스터리
    SciFi,       // 공상 과학
    Apocalypse,  // 아포칼립스
    Documentary  // 다큐멘터리

};

// 책의 분위기
enum class eBookMood {
    Dark,        // 어두움
    Bright,      // 밝음
    Touching,    // 감동
    Tense,       // 긴장
    Strange      // 이상한
};

// 엣지 요소 - 특별한 요소
enum class eBookEdge {
    None,         // 없음
    Reversal,     // 반전 있는 이야기
    Cliché,       // 클리셰 요소
    Unprecedented // 새로운(전례 없는 요소)
};

// 기타 태그
enum class eBookEtc {
    None,         // 없음
    Fragrance,    // 향기
    Label,        // 표지
    Promotion,    // 프로모션
    Branding      // 브랜딩
};

// 책의 상태 (퍼센트 기반)
enum class eBookCondition {
    Perfect = 100,   // 새것처럼 완벽한 상태 (100%)
    Worn = 80,       // 사용감 있음 (80~99%)
    Damaged = 40,    // 손상됨 (40~79%)
    Destroyed = 0    // 심하게 파손됨 (0~39%)
};

// 책 손상 타입
enum class eDamageType {
    Water,        // 물에 젖음
    Fire,         // 불에 탐
    MagicCurse,   // 마법의 저주
    Tear,         // 찢김
    Lost,         // 분실
    None          // 손상 없음
};

// NPC의 요청 조건 유형
enum class eRequestType {
    ReturnBook,      // 책 반납
    GenreOnly,       // 장르만 요구
    MoodOnly,        // 분위기만 요구
    GenreAndMood,    // 둘 다 요구
    AnyBook          // 아무 책이나 허용
};


// NPC 생성 방식
enum class eNPCGenerationMode {
    Local = 0,       // 로컬에서 직접 생성
    SimpleAI = 1,    // 단순한 AI 기반 생성
    CreativeAI = 2   // 창의적인 AI 기반 생성
};

#endif // ENUMS_H
