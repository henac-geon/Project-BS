#include "Enum_Utils.h"
#include <stdexcept>

// === eBookGenre ===
std::string Enum_Utils::toKorean(eBookGenre v) {
    switch (v) {
    case eBookGenre::Fantasy: return "판타지";
    case eBookGenre::Romance: return "로맨스";
    case eBookGenre::Horror: return "호러";
    case eBookGenre::Mystery: return "미스터리";
    case eBookGenre::SciFi: return "공상 과학";
    case eBookGenre::Apocalypse: return "아포칼립스";
    case eBookGenre::Documentary: return "다큐멘터리";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eBookGenre v) {
    switch (v) {
    case eBookGenre::Fantasy: return "Fantasy";
    case eBookGenre::Romance: return "Romance";
    case eBookGenre::Horror: return "Horror";
    case eBookGenre::Mystery: return "Mystery";
    case eBookGenre::SciFi: return "SciFi";
    case eBookGenre::Apocalypse: return "Apocalypse";
    case eBookGenre::Documentary: return "Documentary";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eBookGenre v) {
    return static_cast<int>(v);
}
eBookGenre Enum_Utils::fromKoreanGenre(const std::string& s) {
    if (s == "판타지") return eBookGenre::Fantasy;
    if (s == "로맨스") return eBookGenre::Romance;
    if (s == "호러") return eBookGenre::Horror;
    if (s == "미스터리") return eBookGenre::Mystery;
    if (s == "공상 과학") return eBookGenre::SciFi;
    if (s == "아포칼립스") return eBookGenre::Apocalypse;
    if (s == "다큐멘터리") return eBookGenre::Documentary;
    throw std::invalid_argument("Invalid eBookGenre Korean: " + s);
}
eBookGenre Enum_Utils::fromEnglishGenre(const std::string& s) {
    if (s == "Fantasy") return eBookGenre::Fantasy;
    if (s == "Romance") return eBookGenre::Romance;
    if (s == "Horror") return eBookGenre::Horror;
    if (s == "Mystery") return eBookGenre::Mystery;
    if (s == "SciFi") return eBookGenre::SciFi;
    if (s == "Apocalypse") return eBookGenre::Apocalypse;
    if (s == "Documentary") return eBookGenre::Documentary;
    throw std::invalid_argument("Invalid eBookGenre English: " + s);
}
eBookGenre Enum_Utils::fromIntGenre(int i) {
    if (i >= 0 && i <= 6) return static_cast<eBookGenre>(i);
    throw std::invalid_argument("Invalid eBookGenre int: " + std::to_string(i));
}

// === eBookMood ===
std::string Enum_Utils::toKorean(eBookMood v) {
    switch (v) {
    case eBookMood::Dark: return "어두움";
    case eBookMood::Bright: return "밝음";
    case eBookMood::Touching: return "감동";
    case eBookMood::Tense: return "긴장";
    case eBookMood::Strange: return "이상한";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eBookMood v) {
    switch (v) {
    case eBookMood::Dark: return "Dark";
    case eBookMood::Bright: return "Bright";
    case eBookMood::Touching: return "Touching";
    case eBookMood::Tense: return "Tense";
    case eBookMood::Strange: return "Strange";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eBookMood v) {
    return static_cast<int>(v);
}
eBookMood Enum_Utils::fromKoreanMood(const std::string& s) {
    if (s == "어두움") return eBookMood::Dark;
    if (s == "밝음") return eBookMood::Bright;
    if (s == "감동") return eBookMood::Touching;
    if (s == "긴장") return eBookMood::Tense;
    if (s == "이상한") return eBookMood::Strange;
    throw std::invalid_argument("Invalid eBookMood Korean: " + s);
}
eBookMood Enum_Utils::fromEnglishMood(const std::string& s) {
    if (s == "Dark") return eBookMood::Dark;
    if (s == "Bright") return eBookMood::Bright;
    if (s == "Touching") return eBookMood::Touching;
    if (s == "Tense") return eBookMood::Tense;
    if (s == "Strange") return eBookMood::Strange;
    throw std::invalid_argument("Invalid eBookMood English: " + s);
}
eBookMood Enum_Utils::fromIntMood(int i) {
    if (i >= 0 && i <= 4) return static_cast<eBookMood>(i);
    throw std::invalid_argument("Invalid eBookMood int: " + std::to_string(i));
}


// === eBookEdge ===
std::string Enum_Utils::toKorean(eBookEdge v) {
    switch (v) {
    case eBookEdge::None: return "없음";
    case eBookEdge::Reversal: return "반전 있는 이야기";
    case eBookEdge::Cliché: return "클리셰 요소";
    case eBookEdge::Unprecedented: return "전례 없는 요소";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eBookEdge v) {
    switch (v) {
    case eBookEdge::None: return "None";
    case eBookEdge::Reversal: return "Reversal";
    case eBookEdge::Cliché: return "Cliche";
    case eBookEdge::Unprecedented: return "Unprecedented";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eBookEdge v) {
    return static_cast<int>(v);
}
eBookEdge Enum_Utils::fromKoreanEdge(const std::string& s) {
    if (s == "없음") return eBookEdge::None;
    if (s == "반전 있는 이야기") return eBookEdge::Reversal;
    if (s == "클리셰 요소") return eBookEdge::Cliché;
    if (s == "전례 없는 요소") return eBookEdge::Unprecedented;
    throw std::invalid_argument("Invalid eBookEdge Korean: " + s);
}
eBookEdge Enum_Utils::fromEnglishEdge(const std::string& s) {
    if (s == "None") return eBookEdge::None;
    if (s == "Reversal") return eBookEdge::Reversal;
    if (s == "Cliche") return eBookEdge::Cliché;
    if (s == "Unprecedented") return eBookEdge::Unprecedented;
    throw std::invalid_argument("Invalid eBookEdge English: " + s);
}
eBookEdge Enum_Utils::fromIntEdge(int i) {
    if (i >= 0 && i <= 3) return static_cast<eBookEdge>(i);
    throw std::invalid_argument("Invalid eBookEdge int: " + std::to_string(i));
}

// === eBookEtc ===
std::string Enum_Utils::toKorean(eBookEtc v) {
    switch (v) {
    case eBookEtc::None: return "없음";
    case eBookEtc::Fragrance: return "향기";
    case eBookEtc::Label: return "표지";
    case eBookEtc::Promotion: return "프로모션";
    case eBookEtc::Branding: return "브랜딩";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eBookEtc v) {
    switch (v) {
    case eBookEtc::None: return "None";
    case eBookEtc::Fragrance: return "Fragrance";
    case eBookEtc::Label: return "Label";
    case eBookEtc::Promotion: return "Promotion";
    case eBookEtc::Branding: return "Branding";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eBookEtc v) {
    return static_cast<int>(v);
}
eBookEtc Enum_Utils::fromKoreanEtc(const std::string& s) {
    if (s == "없음") return eBookEtc::None;
    if (s == "향기") return eBookEtc::Fragrance;
    if (s == "표지") return eBookEtc::Label;
    if (s == "프로모션") return eBookEtc::Promotion;
    if (s == "브랜딩") return eBookEtc::Branding;
    throw std::invalid_argument("Invalid eBookEtc Korean: " + s);
}
eBookEtc Enum_Utils::fromEnglishEtc(const std::string& s) {
    if (s == "None") return eBookEtc::None;
    if (s == "Fragrance") return eBookEtc::Fragrance;
    if (s == "Label") return eBookEtc::Label;
    if (s == "Promotion") return eBookEtc::Promotion;
    if (s == "Branding") return eBookEtc::Branding;
    throw std::invalid_argument("Invalid eBookEtc English: " + s);
}
eBookEtc Enum_Utils::fromIntEtc(int i) {
    if (i >= 0 && i <= 4) return static_cast<eBookEtc>(i);
    throw std::invalid_argument("Invalid eBookEtc int: " + std::to_string(i));
}

// === eBookCondition ===
std::string Enum_Utils::toKorean(eBookCondition v) {
    switch (v) {
    case eBookCondition::Perfect: return "완벽함";
    case eBookCondition::Worn: return "중고";
    case eBookCondition::Damaged: return "손상됨";
    case eBookCondition::Destroyed: return "파괴됨";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eBookCondition v) {
    switch (v) {
    case eBookCondition::Perfect: return "Perfect";
    case eBookCondition::Worn: return "Worn";
    case eBookCondition::Damaged: return "Damaged";
    case eBookCondition::Destroyed: return "Destroyed";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eBookCondition v) {
    return static_cast<int>(v);
}
eBookCondition Enum_Utils::fromKoreanCondition(const std::string& s) {
    if (s == "완벽함") return eBookCondition::Perfect;
    if (s == "중고") return eBookCondition::Worn;
    if (s == "손상됨") return eBookCondition::Damaged;
    if (s == "파괴됨") return eBookCondition::Destroyed;
    throw std::invalid_argument("Invalid eBookCondition Korean: " + s);
}
eBookCondition Enum_Utils::fromEnglishCondition(const std::string& s) {
    if (s == "Perfect") return eBookCondition::Perfect;
    if (s == "Worn") return eBookCondition::Worn;
    if (s == "Damaged") return eBookCondition::Damaged;
    if (s == "Destroyed") return eBookCondition::Destroyed;
    throw std::invalid_argument("Invalid eBookCondition English: " + s);
}
eBookCondition Enum_Utils::fromIntCondition(int i) {
    switch (i) {
    case 100: return eBookCondition::Perfect;
    case 80:  return eBookCondition::Worn;
    case 40:  return eBookCondition::Damaged;
    case 0:   return eBookCondition::Destroyed;
    default: throw std::invalid_argument("Invalid eBookCondition int: " + std::to_string(i));
    }
}


// === eRequestType ===
std::string Enum_Utils::toKorean(eRequestType v) {
    switch (v) {
    case eRequestType::ReturnBook: return "책 반납";
    case eRequestType::GenreOnly: return "장르만 요구";
    case eRequestType::MoodOnly: return "분위기만 요구";
    case eRequestType::GenreAndMood: return "둘 다 요구";
    case eRequestType::AnyBook: return "아무 책이나 허용";
    default: return "<알 수 없음>";
    }
}
std::string Enum_Utils::toEnglish(eRequestType v) {
    switch (v) {
    case eRequestType::ReturnBook: return "책 반납";
    case eRequestType::GenreOnly: return "장르만 요구";
    case eRequestType::MoodOnly: return "분위기만 요구";
    case eRequestType::GenreAndMood: return "둘 다 요구";
    case eRequestType::AnyBook: return "아무 책이나 허용";
    default: return "Unknown";
    }
}
int Enum_Utils::toInt(eRequestType v) {
    return static_cast<int>(v);
}
eRequestType Enum_Utils::fromKoreanRequestType(const std::string& s) {
    if (s == "책 반납") return eRequestType::ReturnBook;
    if (s == "장르만 요구") return eRequestType::GenreOnly;
    if (s == "분위기만 요구") return eRequestType::MoodOnly;
    if (s == "둘 다 요구") return eRequestType::GenreAndMood;
    if (s == "아무 책이나 허용") return eRequestType::AnyBook;
    throw std::invalid_argument("Invalid eBookCondition Korean: " + s);
}
eRequestType Enum_Utils::fromEnglishRequestType(const std::string& s) {
    if (s == "책 반납") return eRequestType::ReturnBook;
    if (s == "GenreOnly") return eRequestType::GenreOnly;
    if (s == "MoodOnly") return eRequestType::MoodOnly;
    if (s == "GenreAndMood") return eRequestType::GenreAndMood;
    if (s == "AnyBook") return eRequestType::AnyBook;
    throw std::invalid_argument("Invalid eBookCondition English: " + s);
}
eRequestType Enum_Utils::fromIntRequestType(int i) {
    switch (i) {
    case 0: return eRequestType::ReturnBook;
    case 1:  return eRequestType::GenreOnly;
    case 2:  return eRequestType::MoodOnly;
    case 3:   return eRequestType::GenreAndMood;
    case 4:   return eRequestType::AnyBook;
    default: throw std::invalid_argument("Invalid eBookCondition int: " + std::to_string(i));
    }
}
