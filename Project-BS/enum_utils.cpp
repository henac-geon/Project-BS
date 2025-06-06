#include "enum_utils.h"

// -------------------- eBookGenre --------------------
const std::unordered_map<eBookGenre, std::string> EnumConverter<eBookGenre>::to_string_map = {
    {eBookGenre::Fantasy, "Fantasy"},
    {eBookGenre::Romance, "Romance"},
    {eBookGenre::Horror, "Horror"},
    {eBookGenre::Mystery, "Mystery"},
    {eBookGenre::SciFi, "SciFi"},
    {eBookGenre::Apocalypse, "Apocalypse"},
    {eBookGenre::Documentary, "Documentary"}
};

const std::unordered_map<eBookGenre, std::string> EnumConverter<eBookGenre>::to_korean_map = {
    {eBookGenre::Fantasy, "판타지"},
    {eBookGenre::Romance, "로맨스"},
    {eBookGenre::Horror, "공포"},
    {eBookGenre::Mystery, "미스터리"},
    {eBookGenre::SciFi, "공상과학"},
    {eBookGenre::Apocalypse, "종말"},
    {eBookGenre::Documentary, "다큐멘터리"}
};

const std::unordered_map<eBookGenre, int> EnumConverter<eBookGenre>::to_int_map = {
    {eBookGenre::Fantasy, 0},
    {eBookGenre::Romance, 1},
    {eBookGenre::Horror, 2},
    {eBookGenre::Mystery, 3},
    {eBookGenre::SciFi, 4},
    {eBookGenre::Apocalypse, 5},
    {eBookGenre::Documentary, 6}
};

const std::unordered_map<std::string, eBookGenre> EnumConverter<eBookGenre>::from_string_map = {
    {"Fantasy", eBookGenre::Fantasy},
    {"Romance", eBookGenre::Romance},
    {"Horror", eBookGenre::Horror},
    {"Mystery", eBookGenre::Mystery},
    {"SciFi", eBookGenre::SciFi},
    {"Apocalypse", eBookGenre::Apocalypse},
    {"Documentary", eBookGenre::Documentary}
};

const std::unordered_map<std::string, eBookGenre> EnumConverter<eBookGenre>::from_korean_map = {
    {"판타지", eBookGenre::Fantasy},
    {"로맨스", eBookGenre::Romance},
    {"공포", eBookGenre::Horror},
    {"미스터리", eBookGenre::Mystery},
    {"공상과학", eBookGenre::SciFi},
    {"종말", eBookGenre::Apocalypse},
    {"다큐멘터리", eBookGenre::Documentary}
};

const std::unordered_map<int, eBookGenre> EnumConverter<eBookGenre>::from_int_map = {
    {0, eBookGenre::Fantasy},
    {1, eBookGenre::Romance},
    {2, eBookGenre::Horror},
    {3, eBookGenre::Mystery},
    {4, eBookGenre::SciFi},
    {5, eBookGenre::Apocalypse},
    {6, eBookGenre::Documentary}
};

// -------------------- eBookMood --------------------
const std::unordered_map<eBookMood, std::string> EnumConverter<eBookMood>::to_string_map = {
    {eBookMood::Dark, "Dark"},
    {eBookMood::Bright, "Bright"},
    {eBookMood::Touching, "Touching"},
    {eBookMood::Tense, "Tense"},
    {eBookMood::Strange, "Strange"}
};

const std::unordered_map<eBookMood, std::string> EnumConverter<eBookMood>::to_korean_map = {
    {eBookMood::Dark, "어두움"},
    {eBookMood::Bright, "밝음"},
    {eBookMood::Touching, "감성"},
    {eBookMood::Tense, "긴장감"},
    {eBookMood::Strange, "엉뚱"}
};

const std::unordered_map<eBookMood, int> EnumConverter<eBookMood>::to_int_map = {
    {eBookMood::Dark, 0},
    {eBookMood::Bright, 1},
    {eBookMood::Touching, 2},
    {eBookMood::Tense, 3},
    {eBookMood::Strange, 4}
};

const std::unordered_map<std::string, eBookMood> EnumConverter<eBookMood>::from_string_map = {
    {"Dark", eBookMood::Dark},
    {"Bright", eBookMood::Bright},
    {"Touching", eBookMood::Touching},
    {"Tense", eBookMood::Tense},
    {"Strange", eBookMood::Strange}
};

const std::unordered_map<std::string, eBookMood> EnumConverter<eBookMood>::from_korean_map = {
    {"어두움", eBookMood::Dark},
    {"밝음", eBookMood::Bright},
    {"감성", eBookMood::Touching},
    {"긴장감", eBookMood::Tense},
    {"엉뚱", eBookMood::Strange}
};

const std::unordered_map<int, eBookMood> EnumConverter<eBookMood>::from_int_map = {
    {0, eBookMood::Dark},
    {1, eBookMood::Bright},
    {2, eBookMood::Touching},
    {3, eBookMood::Tense},
    {4, eBookMood::Strange}
};

// -------------------- eBookCondition --------------------
const std::unordered_map<eBookCondition, std::string> EnumConverter<eBookCondition>::to_string_map = {
    {eBookCondition::Perfect, "Perfect"},
    {eBookCondition::Worn, "Worn"},
    {eBookCondition::Damaged, "Damaged"},
    {eBookCondition::Destroyed, "Destroyed"}
};

const std::unordered_map<eBookCondition, std::string> EnumConverter<eBookCondition>::to_korean_map = {
    {eBookCondition::Perfect, "완벽"},
    {eBookCondition::Worn, "낡음"},
    {eBookCondition::Damaged, "손상"},
    {eBookCondition::Destroyed, "파괴"}
};

const std::unordered_map<eBookCondition, int> EnumConverter<eBookCondition>::to_int_map = {
    {eBookCondition::Perfect, 100},
    {eBookCondition::Worn, 80},
    {eBookCondition::Damaged, 40},
    {eBookCondition::Destroyed, 0}
};

const std::unordered_map<std::string, eBookCondition> EnumConverter<eBookCondition>::from_string_map = {
    {"Perfect", eBookCondition::Perfect},
    {"Worn", eBookCondition::Worn},
    {"Damaged", eBookCondition::Damaged},
    {"Destroyed", eBookCondition::Destroyed}
};

const std::unordered_map<std::string, eBookCondition> EnumConverter<eBookCondition>::from_korean_map = {
    {"완벽", eBookCondition::Perfect},
    {"낡음", eBookCondition::Worn},
    {"손상", eBookCondition::Damaged},
    {"파괴", eBookCondition::Destroyed}
};

const std::unordered_map<int, eBookCondition> EnumConverter<eBookCondition>::from_int_map = {
    {100, eBookCondition::Perfect},
    {80, eBookCondition::Worn},
    {40, eBookCondition::Damaged},
    {0, eBookCondition::Destroyed}
};

// -------------------- eBookEdge --------------------
const std::unordered_map<eBookEdge, std::string> EnumConverter<eBookEdge>::to_string_map = {
    {eBookEdge::None, "None"},
    {eBookEdge::Reversal, "Reversal"}
};

const std::unordered_map<eBookEdge, std::string> EnumConverter<eBookEdge>::to_korean_map = {
    {eBookEdge::None, "없음"},
    {eBookEdge::Reversal, "반전"}
};

const std::unordered_map<eBookEdge, int> EnumConverter<eBookEdge>::to_int_map = {
    {eBookEdge::None, 0},
    {eBookEdge::Reversal, 1}
};

const std::unordered_map<std::string, eBookEdge> EnumConverter<eBookEdge>::from_string_map = {
    {"None", eBookEdge::None},
    {"Reversal", eBookEdge::Reversal}
};

const std::unordered_map<std::string, eBookEdge> EnumConverter<eBookEdge>::from_korean_map = {
    {"없음", eBookEdge::None},
    {"반전", eBookEdge::Reversal}
};

const std::unordered_map<int, eBookEdge> EnumConverter<eBookEdge>::from_int_map = {
    {0, eBookEdge::None},
    {1, eBookEdge::Reversal}
};

// -------------------- eBookEtc --------------------
const std::unordered_map<eBookEtc, std::string> EnumConverter<eBookEtc>::to_string_map = {
    {eBookEtc::None, "None"},
    {eBookEtc::Fragrance, "Fragrance"},
    {eBookEtc::Label, "Label"},
    {eBookEtc::Promotion, "Promotion"},
    {eBookEtc::Branding, "Branding"}
};

const std::unordered_map<eBookEtc, std::string> EnumConverter<eBookEtc>::to_korean_map = {
    {eBookEtc::None, "없음"},
    {eBookEtc::Fragrance, "향기"},
    {eBookEtc::Label, "표지"},
    {eBookEtc::Promotion, "프로모션"},
    {eBookEtc::Branding, "브랜딩"}
};

const std::unordered_map<eBookEtc, int> EnumConverter<eBookEtc>::to_int_map = {
    {eBookEtc::None, 0},
    {eBookEtc::Fragrance, 1},
    {eBookEtc::Label, 2},
    {eBookEtc::Promotion, 3},
    {eBookEtc::Branding, 4}
};

const std::unordered_map<std::string, eBookEtc> EnumConverter<eBookEtc>::from_string_map = {
    {"None", eBookEtc::None},
    {"Fragrance", eBookEtc::Fragrance},
    {"Label", eBookEtc::Label},
    {"Promotion", eBookEtc::Promotion},
    {"Branding", eBookEtc::Branding}
};

const std::unordered_map<std::string, eBookEtc> EnumConverter<eBookEtc>::from_korean_map = {
    {"없음", eBookEtc::None},
    {"향기", eBookEtc::Fragrance},
    {"표지", eBookEtc::Label},
    {"프로모션", eBookEtc::Promotion},
    {"브랜딩", eBookEtc::Branding}
};

const std::unordered_map<int, eBookEtc> EnumConverter<eBookEtc>::from_int_map = {
    {0, eBookEtc::None},
    {1, eBookEtc::Fragrance},
    {2, eBookEtc::Label},
    {3, eBookEtc::Promotion},
    {4, eBookEtc::Branding}
};

// -------------------- eDamageType --------------------
const std::unordered_map<eDamageType, std::string> EnumConverter<eDamageType>::to_string_map = {
    {eDamageType::Water, "Water"}, {eDamageType::Fire, "Fire"},
    {eDamageType::MagicCurse, "MagicCurse"}, {eDamageType::Tear, "Tear"},
    {eDamageType::Lost, "Lost"}, {eDamageType::None, "None"}
};

const std::unordered_map<eDamageType, std::string> EnumConverter<eDamageType>::to_korean_map = {
    {eDamageType::Water, "물"}, {eDamageType::Fire, "불"},
    {eDamageType::MagicCurse, "저주"}, {eDamageType::Tear, "찢김"},
    {eDamageType::Lost, "분실"}, {eDamageType::None, "없음"}
};

const std::unordered_map<eDamageType, int> EnumConverter<eDamageType>::to_int_map = {
    {eDamageType::Water, 0}, {eDamageType::Fire, 1},
    {eDamageType::MagicCurse, 2}, {eDamageType::Tear, 3},
    {eDamageType::Lost, 4}, {eDamageType::None, 5}
};

const std::unordered_map<std::string, eDamageType> EnumConverter<eDamageType>::from_string_map = {
    {"Water", eDamageType::Water}, {"Fire", eDamageType::Fire},
    {"MagicCurse", eDamageType::MagicCurse}, {"Tear", eDamageType::Tear},
    {"Lost", eDamageType::Lost}, {"None", eDamageType::None}
};

const std::unordered_map<std::string, eDamageType> EnumConverter<eDamageType>::from_korean_map = {
    {"물", eDamageType::Water}, {"불", eDamageType::Fire},
    {"저주", eDamageType::MagicCurse}, {"찢김", eDamageType::Tear},
    {"분실", eDamageType::Lost}, {"없음", eDamageType::None}
};

const std::unordered_map<int, eDamageType> EnumConverter<eDamageType>::from_int_map = {
    {0, eDamageType::Water}, {1, eDamageType::Fire},
    {2, eDamageType::MagicCurse}, {3, eDamageType::Tear},
    {4, eDamageType::Lost}, {5, eDamageType::None}
};

// -------------------- eRequestType --------------------
const std::unordered_map<eRequestType, std::string> EnumConverter<eRequestType>::to_string_map = {
    {eRequestType::GenreOnly, "GenreOnly"}, {eRequestType::MoodOnly, "MoodOnly"},
    {eRequestType::GenreAndMood, "GenreAndMood"}, {eRequestType::AnyBook, "AnyBook"}
};

const std::unordered_map<eRequestType, std::string> EnumConverter<eRequestType>::to_korean_map = {
    {eRequestType::GenreOnly, "장르만"}, {eRequestType::MoodOnly, "무드만"},
    {eRequestType::GenreAndMood, "둘다"}, {eRequestType::AnyBook, "아무거나"}
};

const std::unordered_map<eRequestType, int> EnumConverter<eRequestType>::to_int_map = {
    {eRequestType::GenreOnly, 0}, {eRequestType::MoodOnly, 1},
    {eRequestType::GenreAndMood, 2}, {eRequestType::AnyBook, 3}
};

const std::unordered_map<std::string, eRequestType> EnumConverter<eRequestType>::from_string_map = {
    {"GenreOnly", eRequestType::GenreOnly}, {"MoodOnly", eRequestType::MoodOnly},
    {"GenreAndMood", eRequestType::GenreAndMood}, {"AnyBook", eRequestType::AnyBook}
};

const std::unordered_map<std::string, eRequestType> EnumConverter<eRequestType>::from_korean_map = {
    {"장르만", eRequestType::GenreOnly}, {"무드만", eRequestType::MoodOnly},
    {"둘다", eRequestType::GenreAndMood}, {"아무거나", eRequestType::AnyBook}
};

const std::unordered_map<int, eRequestType> EnumConverter<eRequestType>::from_int_map = {
    {0, eRequestType::GenreOnly}, {1, eRequestType::MoodOnly},
    {2, eRequestType::GenreAndMood}, {3, eRequestType::AnyBook}
};

// -------------------- eNPCGenerationMode --------------------
const std::unordered_map<eNPCGenerationMode, std::string> EnumConverter<eNPCGenerationMode>::to_string_map = {
    {eNPCGenerationMode::Local, "Local"},
    {eNPCGenerationMode::SimpleAI, "SimpleAI"},
    {eNPCGenerationMode::CreativeAI, "CreativeAI"}
};

const std::unordered_map<eNPCGenerationMode, std::string> EnumConverter<eNPCGenerationMode>::to_korean_map = {
    {eNPCGenerationMode::Local, "로컬"},
    {eNPCGenerationMode::SimpleAI, "간단AI"},
    {eNPCGenerationMode::CreativeAI, "창의AI"}
};

const std::unordered_map<eNPCGenerationMode, int> EnumConverter<eNPCGenerationMode>::to_int_map = {
    {eNPCGenerationMode::Local, 0},
    {eNPCGenerationMode::SimpleAI, 1},
    {eNPCGenerationMode::CreativeAI, 2}
};

const std::unordered_map<std::string, eNPCGenerationMode> EnumConverter<eNPCGenerationMode>::from_string_map = {
    {"Local", eNPCGenerationMode::Local},
    {"SimpleAI", eNPCGenerationMode::SimpleAI},
    {"CreativeAI", eNPCGenerationMode::CreativeAI}
};

const std::unordered_map<std::string, eNPCGenerationMode> EnumConverter<eNPCGenerationMode>::from_korean_map = {
    {"로컬", eNPCGenerationMode::Local},
    {"간단AI", eNPCGenerationMode::SimpleAI},
    {"창의AI", eNPCGenerationMode::CreativeAI}
};

const std::unordered_map<int, eNPCGenerationMode> EnumConverter<eNPCGenerationMode>::from_int_map = {
    {0, eNPCGenerationMode::Local},
    {1, eNPCGenerationMode::SimpleAI},
    {2, eNPCGenerationMode::CreativeAI}
};
