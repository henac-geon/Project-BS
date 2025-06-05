// WritingElementManager.cpp
#include "WritingElementManager.h"

WritingElementManager::WritingElementManager() {
    loadElements();
}

// 초기 요소 정의 및 설정
void WritingElementManager::loadElements() {
    genres = {
        {eBookGenre::Fantasy, 10, 0},
        {eBookGenre::SciFi, 50, 2},
        {eBookGenre::Apocalypse, 90, 5}
    };
    moods = {
        {eBookMood::Light, 20, 0},
        {eBookMood::Dark, 40, 2},
        {eBookMood::Whimsical, 60, 10},
        {eBookMood::Tense, 60, 10}
    };
    lengths = {
        {"30", 30, 0},
        {"90", 90, 2},
        {"120", 120, 5}
    };
    edges = {
        {eBookEdge::None, 0, 0},
        {eBookEdge::Reversal, 100, 5}
    };
    etcs = {
        {eBookEtc::None, 0, 0}
    };
}

std::vector<eBookGenre> WritingElementManager::getAvailableGenres(int level) const {
    std::vector<eBookGenre> result;
    for (const auto& elem : genres) {
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    }
    return result;
}

std::vector<eBookMood> WritingElementManager::getAvailableMoods(int level) const {
    std::vector<eBookMood> result;
    for (const auto& elem : moods) {
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    }
    return result;
}

std::vector<std::string> WritingElementManager::getAvailableLengths(int level) const {
    std::vector<std::string> result;
    for (const auto& elem : lengths) {
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    }
    return result;
}

std::vector<eBookEdge> WritingElementManager::getAvailableEdges(int level) const {
    std::vector<eBookEdge> result;
    for (const auto& elem : edges) {
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    }
    return result;
}

std::vector<eBookEtc> WritingElementManager::getAvailableEtcs(int level) const {
    std::vector<eBookEtc> result;
    for (const auto& elem : etcs) {
        if (level >= elem.requiredLevel) result.push_back(elem.element);
    }
    return result;
}

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
            if (std::stoi(elem.element) == enumValue) return elem.magicCost;
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

void WritingElementManager::addGenreOption(eBookGenre genre, int cost, int level) {
    genres.push_back({ genre, cost, level });
}

void WritingElementManager::addMoodOption(eBookMood mood, int cost, int level) {
    moods.push_back({ mood, cost, level });
}

bool WritingElementManager::isGenreOptionAvailable(eBookGenre genre) const {
    return std::any_of(genres.begin(), genres.end(), [&](const auto& e) { return e.element == genre; });
}

bool WritingElementManager::isMoodOptionAvailable(eBookMood mood) const {
    return std::any_of(moods.begin(), moods.end(), [&](const auto& e) { return e.element == mood; });
}

std::vector<std::string> WritingElementManager::getGenreNames() const {
    std::vector<std::string> result;
    for (const auto& e : genres) {
        result.push_back(enum_utils::toKoreanString(e.element));
    }
    return result;
}

std::vector<std::string> WritingElementManager::getMoodNames() const {
    std::vector<std::string> result;
    for (const auto& e : moods) {
        result.push_back(enum_utils::toKoreanString(e.element));
    }
    return result;
}

std::vector<std::string> WritingElementManager::getEdgeNames() const {
    std::vector<std::string> result;
    for (const auto& e : edges) {
        result.push_back(enum_utils::toKoreanString(e.element));
    }
    return result;
}

std::vector<std::string> WritingElementManager::getEtcNames() const {
    std::vector<std::string> result;
    for (const auto& e : etcs) {
        result.push_back(enum_utils::toKoreanString(e.element));
    }
    return result;
}

