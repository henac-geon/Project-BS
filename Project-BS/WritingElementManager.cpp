#include "WritingElementManager.h"

// 생성자: 객체가 생성될 때 기본 요소들을 초기화
WritingElementManager::WritingElementManager() {
    loadElements();
}

// 요소들을 초기화하는 함수
void WritingElementManager::loadElements() {
    // 장르 초기화: (장르 타입, 마력 비용, 골드 비용, 요구 레벨)
    genres = {
        {eBookGenre::Fantasy, 0, 0, 0},
        {eBookGenre::Romance, 10, 0, 2},
        {eBookGenre::Horror, 12, 0, 3},
        {eBookGenre::Mystery, 14, 0, 3},
        {eBookGenre::SciFi, 18, 0, 7},
        {eBookGenre::Apocalypse, 28, 0, 8},
        {eBookGenre::Documentary, 40, 0, 9},
    };

    // 분위기 초기화
    moods = {
        {eBookMood::Dark, 0, 0, 0},
        {eBookMood::Bright, 8, 0, 2},
        {eBookMood::Touching, 10, 0, 2},
        {eBookMood::Tense, 14, 0, 5},
        {eBookMood::Strange, 18, 0, 6},
    };

    // 길이 옵션 초기화 (길이 값, 마력 비용, 골드 비용, 요구 레벨)
    lengths = {
        {30, 0, 0, 0},
        {60, 0, 10, 2},
        {90, 0, 40, 4},
        {120, 0, 60, 4},
        {180, 0, 90, 8},
        {210, 0, 110, 8},
        {300, 0, 150, 10}
    };

    // 전개 요소 초기화
    edges = {
        {eBookEdge::None, 0, 0, 0},
        {eBookEdge::Reversal, 14, 0, 4},
        {eBookEdge::Cliché, 18, 0, 6},
        {eBookEdge::Unprecedented, 24, 0, 10},
    };

    // 기타 요소 초기화
    etcs = {
        {eBookEtc::None, 0, 0, 0},
        {eBookEtc::Fragrance, 0, 200, 1},
        {eBookEtc::Label, 0, 300, 1},
        {eBookEtc::Promotion, 0, 400, 2},
        {eBookEtc::Branding, 0, 600, 2},
    };
}

// 요구 레벨에 따른 사용 가능한 장르 반환
std::vector<eBookGenre> WritingElementManager::getAvailableGenres(int level) const {
    std::vector<eBookGenre> result;
    for (const auto& elem : genres)
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    return result;
}

// 사용 가능한 분위기 반환
std::vector<eBookMood> WritingElementManager::getAvailableMoods(int level) const {
    std::vector<eBookMood> result;
    for (const auto& elem : moods)
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    return result;
}

// 사용 가능한 길이 반환
std::vector<int> WritingElementManager::getAvailableLengths(int level) const {
    std::vector<int> result;
    for (const auto& elem : lengths)
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    return result;
}

// 사용 가능한 전개 반환
std::vector<eBookEdge> WritingElementManager::getAvailableEdges(int level) const {
    std::vector<eBookEdge> result;
    for (const auto& elem : edges)
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    return result;
}

// 사용 가능한 기타 요소 반환
std::vector<eBookEtc> WritingElementManager::getAvailableEtcs(int level) const {
    std::vector<eBookEtc> result;
    for (const auto& elem : etcs)
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    return result;
}

// 카테고리별 마력 비용 반환
int WritingElementManager::getMagicCost(WritingElementCategory category, int enumValue) const {
    switch (category) {
    case WritingElementCategory::Genre:
        for (const auto& elem : genres)
            if (static_cast<int>(elem.element) == enumValue) return elem.magicCost;
        break;
    case WritingElementCategory::Mood:
        for (const auto& elem : moods)
            if (static_cast<int>(elem.element) == enumValue) return elem.magicCost;
        break;
    case WritingElementCategory::Length:
        for (const auto& elem : lengths)
            if (elem.element == enumValue) return elem.magicCost;
        break;
    case WritingElementCategory::Edge:
        for (const auto& elem : edges)
            if (static_cast<int>(elem.element) == enumValue) return elem.magicCost;
        break;
    case WritingElementCategory::Etc:
        for (const auto& elem : etcs)
            if (static_cast<int>(elem.element) == enumValue) return elem.magicCost;
        break;
    }
    return 0;
}

// 카테고리별 골드 비용 반환
int WritingElementManager::getGoldCost(WritingElementCategory category, int enumValue) const {
    switch (category) {
    case WritingElementCategory::Genre:
        for (const auto& elem : genres)
            if (static_cast<int>(elem.element) == enumValue) return elem.goldCost;
        break;
    case WritingElementCategory::Mood:
        for (const auto& elem : moods)
            if (static_cast<int>(elem.element) == enumValue) return elem.goldCost;
        break;
    case WritingElementCategory::Length:
        for (const auto& elem : lengths)
            if (elem.element == enumValue) return elem.goldCost;
        break;
    case WritingElementCategory::Edge:
        for (const auto& elem : edges)
            if (static_cast<int>(elem.element) == enumValue) return elem.goldCost;
        break;
    case WritingElementCategory::Etc:
        for (const auto& elem : etcs)
            if (static_cast<int>(elem.element) == enumValue) return elem.goldCost;
        break;
    }
    return 0;
}

// 새로운 장르 옵션 추가
void WritingElementManager::addGenreOption(eBookGenre genre, int magic, int gold, int level) {
    genres.push_back({ genre, magic, gold, level });
}

// 새로운 분위기 옵션 추가
void WritingElementManager::addMoodOption(eBookMood mood, int magic, int gold, int level) {
    moods.push_back({ mood, magic, gold, level });
}

// 장르가 존재하는지 확인
bool WritingElementManager::isGenreOptionAvailable(eBookGenre genre) const {
    return std::any_of(genres.begin(), genres.end(), [&](const auto& e) { return e.element == genre; });
}

// 분위기가 존재하는지 확인
bool WritingElementManager::isMoodOptionAvailable(eBookMood mood) const {
    return std::any_of(moods.begin(), moods.end(), [&](const auto& e) { return e.element == mood; });
}

// 카테고리별 요소 데이터 반환 (템플릿 버전)
template <typename T>
std::vector<ElementData<T>> WritingElementManager::getElements(WritingElementCategory category) const {
    switch (category) {
    case WritingElementCategory::Genre:
        if (std::is_same<T, eBookGenre>::value) return reinterpret_cast<const std::vector<ElementData<T>>&>(genres);
        break;
    case WritingElementCategory::Mood:
        if (std::is_same<T, eBookMood>::value) return reinterpret_cast<const std::vector<ElementData<T>>&>(moods);
        break;
    case WritingElementCategory::Length:
        if (std::is_same<T, int>::value) return reinterpret_cast<const std::vector<ElementData<T>>&>(lengths);
        break;
    case WritingElementCategory::Edge:
        if (std::is_same<T, eBookEdge>::value) return reinterpret_cast<const std::vector<ElementData<T>>&>(edges);
        break;
    case WritingElementCategory::Etc:
        if (std::is_same<T, eBookEtc>::value) return reinterpret_cast<const std::vector<ElementData<T>>&>(etcs);
        break;
    }
    return {};
}

// 이름 목록 반환 (한글)
std::vector<std::string> WritingElementManager::getGenreNames() const {
    std::vector<std::string> result;
    for (const auto& e : genres)
        result.push_back(Enum_Utils::toKorean(e.element));
    return result;
}

std::vector<std::string> WritingElementManager::getMoodNames() const {
    std::vector<std::string> result;
    for (const auto& e : moods)
        result.push_back(Enum_Utils::toKorean(e.element));
    return result;
}

std::vector<std::string> WritingElementManager::getEdgeNames() const {
    std::vector<std::string> result;
    for (const auto& e : edges)
        result.push_back(Enum_Utils::toKorean(e.element));
    return result;
}

std::vector<std::string> WritingElementManager::getEtcNames() const {
    std::vector<std::string> result;
    for (const auto& e : etcs)
        result.push_back(Enum_Utils::toKorean(e.element));
    return result;
}
