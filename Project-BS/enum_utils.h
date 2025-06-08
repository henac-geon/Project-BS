#pragma once

#ifndef ENUM_UTILS_H
#define ENUM_UTILS_H

#include <string>
#include "Enums.h"

namespace Enum_Utils {

    // ----- eBookGenre -----
    std::string toKorean(eBookGenre v);
    std::string toEnglish(eBookGenre v);
    int toInt(eBookGenre v);
    eBookGenre fromKoreanGenre(const std::string& s);
    eBookGenre fromEnglishGenre(const std::string& s);
    eBookGenre fromIntGenre(int i);

    // ----- eBookMood -----
    std::string toKorean(eBookMood v);
    std::string toEnglish(eBookMood v);
    int toInt(eBookMood v);
    eBookMood fromKoreanMood(const std::string& s);
    eBookMood fromEnglishMood(const std::string& s);
    eBookMood fromIntMood(int i);

    // ----- eBookEdge -----
    std::string toKorean(eBookEdge v);
    std::string toEnglish(eBookEdge v);
    int toInt(eBookEdge v);
    eBookEdge fromKoreanEdge(const std::string& s);
    eBookEdge fromEnglishEdge(const std::string& s);
    eBookEdge fromIntEdge(int i);

    // ----- eBookEtc -----
    std::string toKorean(eBookEtc v);
    std::string toEnglish(eBookEtc v);
    int toInt(eBookEtc v);
    eBookEtc fromKoreanEtc(const std::string& s);
    eBookEtc fromEnglishEtc(const std::string& s);
    eBookEtc fromIntEtc(int i);

    // ----- eBookCondition -----
    std::string toKorean(eBookCondition v);
    std::string toEnglish(eBookCondition v);
    int toInt(eBookCondition v);
    eBookCondition fromKoreanCondition(const std::string& s);
    eBookCondition fromEnglishCondition(const std::string& s);
    eBookCondition fromIntCondition(int i);

} // namespace enum_utils

#endif // ENUM_UTILS_H
