#pragma once

#include "enums.h"
#include <string>
#include <unordered_map>
#include <stdexcept>

template<typename T>
struct EnumConverter;

// === 매크로로 공통 구조 생성 ===
#define DEFINE_ENUM_CONVERTER(ENUM_TYPE, ENTRIES) \
template<> \
struct EnumConverter<ENUM_TYPE> { \
    static const std::unordered_map<ENUM_TYPE, std::string> to_string_map; \
    static const std::unordered_map<ENUM_TYPE, std::string> to_korean_map; \
    static const std::unordered_map<ENUM_TYPE, int> to_int_map; \
    static const std::unordered_map<std::string, ENUM_TYPE> from_string_map; \
    static const std::unordered_map<std::string, ENUM_TYPE> from_korean_map; \
    static const std::unordered_map<int, ENUM_TYPE> from_int_map; \
    static std::string toString(ENUM_TYPE v) { return to_string_map.at(v); } \
    static std::string toKorean(ENUM_TYPE v) { return to_korean_map.at(v); } \
    static int toInt(ENUM_TYPE v) { return to_int_map.at(v); } \
    static ENUM_TYPE fromString(const std::string& s) { return from_string_map.at(s); } \
    static ENUM_TYPE fromKorean(const std::string& s) { return from_korean_map.at(s); } \
    static ENUM_TYPE fromInt(int i) { return from_int_map.at(i); } \
};

// === 개별 Enum 정의 ===

/* eBookGenre */
DEFINE_ENUM_CONVERTER(eBookGenre, {
    {eBookGenre::Fantasy,     "Fantasy",     "판타지",     0},
    {eBookGenre::Romance,     "Romance",     "로맨스",     1},
    {eBookGenre::Horror,      "Horror",      "공포",       2},
    {eBookGenre::Mystery,     "Mystery",     "미스터리",   3},
    {eBookGenre::SciFi,       "SciFi",       "공상과학",   4},
    {eBookGenre::Apocalypse,  "Apocalypse",  "종말",       5},
    {eBookGenre::NonFiction,  "NonFiction",  "논픽션",     6}
    })

    /* eBookMood */
    DEFINE_ENUM_CONVERTER(eBookMood, {
        {eBookMood::Dark,       "Dark",       "어두움",     0},
        {eBookMood::Light,      "Light",      "밝음",       1},
        {eBookMood::Emotional,  "Emotional",  "감성적",     2},
        {eBookMood::Tense,      "Tense",      "긴장감",     3},
        {eBookMood::Whimsical,  "Whimsical",  "엉뚱함",     4}
        })

    /* eBookCondition */
    DEFINE_ENUM_CONVERTER(eBookCondition, {
        {eBookCondition::Perfect,   "Perfect",   "완벽",   100},
        {eBookCondition::Worn,      "Worn",      "낡음",    80},
        {eBookCondition::Damaged,   "Damaged",   "손상",    40},
        {eBookCondition::Destroyed, "Destroyed", "파괴",     0}
        })

    /* eBookEdge */
    DEFINE_ENUM_CONVERTER(eBookEdge, {
        {eBookEdge::None,     "None",     "없음",   0},
        {eBookEdge::Reversal, "Reversal", "반전",   1}
        })

    /* eBookEtc */
    DEFINE_ENUM_CONVERTER(eBookEtc, {
        {eBookEtc::None, "None", "없음", 0}
        })

    /* eDamageType */
    DEFINE_ENUM_CONVERTER(eDamageType, {
        {eDamageType::Water,      "Water",      "물",       0},
        {eDamageType::Fire,       "Fire",       "불",       1},
        {eDamageType::MagicCurse, "MagicCurse", "저주",     2},
        {eDamageType::Tear,       "Tear",       "찢김",     3},
        {eDamageType::Lost,       "Lost",       "분실",     4},
        {eDamageType::None,       "None",       "없음",     5}
        })

    /* eRequestType */
    DEFINE_ENUM_CONVERTER(eRequestType, {
        {eRequestType::GenreOnly,     "GenreOnly",     "장르만",      0},
        {eRequestType::MoodOnly,      "MoodOnly",      "무드만",      1},
        {eRequestType::GenreAndMood,  "GenreAndMood",  "둘다",        2},
        {eRequestType::AnyBook,       "AnyBook",       "아무거나",    3}
        })

    /* eNPCGenerationMode */
    DEFINE_ENUM_CONVERTER(eNPCGenerationMode, {
        {eNPCGenerationMode::Local,       "Local",       "로컬",       0},
        {eNPCGenerationMode::SimpleAI,    "SimpleAI",    "간단AI",     1},
        {eNPCGenerationMode::CreativeAI,  "CreativeAI",  "창의AI",     2}
        })

    namespace enum_utils {

    template <typename T>
    std::string toKoreanString(T value) {
        return EnumConverter<T>::toKorean(value);
    }

    template <typename T>
    std::string toEnglishString(T value) {
        return EnumConverter<T>::toString(value);
    }

    template <typename T>
    int toIntValue(T value) {
        return EnumConverter<T>::toInt(value);
    }

}
