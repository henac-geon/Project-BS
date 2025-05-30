#include "WritingElementManager.h"
#include <algorithm>

WritingElementManager::WritingElementManager() {
    loadDefaultElements();
    loadMagicCosts(); // 마법기운 테이블 초기화
}

void WritingElementManager::loadDefaultElements() {
    elements.clear();

    elements["장르"] = { "판타지", "공상과학", "아포칼립스" };
    elements["분위기"] = { "몽환", "암울", "공포", "기묘", "무거움" };
    elements["분량"] = { "30", "90", "120" };
    elements["옛지 요소"] = { "없음", "반전" };
    elements["기타"] = { "없음", "숨겨진 코드", "고대 룬", "운명의 반전", "미래 예시", "금단 기술" };
}


void WritingElementManager::loadMagicCosts() {
    magicCostTable.clear();

    magicCostTable["장르"] = {
        {"판타지", 10}, {"공상과학", 50}, {"아포칼립스", 90}
    };
    magicCostTable["분위기"] = {
        {"밝음", 20}, {"암울", 40}, {"공포", 50}, {"기묘", 60}, {"무거움", 60}
    };
    magicCostTable["분량"] = {
        {"30", 30}, {"90", 90}, {"120", 120}
    };
    magicCostTable["옛지 요소"] = {
        {"없음", 0}, {"반전", 100}
    };
    magicCostTable["기타"] = {
        {"없음", 0}, {"숨겨진 코드", 70}, {"고대 룬", 100}, {"운명의 반전", 100},
        {"미래 예시", 110}, {"금단 기술", 120}
    };
}

int WritingElementManager::getMagicCost(const std::string& category, const std::string& option) const {
    auto catIt = magicCostTable.find(category);
    if (catIt != magicCostTable.end()) {
        const auto& innerMap = catIt->second;
        auto optIt = innerMap.find(option);
        if (optIt != innerMap.end()) {
            return optIt->second;
        }
    }
    return 0;
}

// TODO: 1. 각 카테고리별로 잠금 해제 조건을 설정합니다.
// 2. 배열로 구현하여 좀더 보기 좋게 해야 함
std::vector<std::string> WritingElementManager::getAvailableOptions(const std::string& category, int level) const {
    std::vector<std::string> filtered;
    auto it = elements.find(category);
    if (it == elements.end()) return filtered;

    for (const auto& option : it->second) {
        bool unlocked = false;

        if (category == "장르") {
            if (option == "판타지") unlocked = true;
            else if (option == "공상과학" && level >= 2) unlocked = true;
            else if (option == "아포칼립스" && level >= 5) unlocked = true;
        }
        else if (category == "분위기") {
            if (option == "밝음") unlocked = true;
            else if (option == "암울" && level >= 2) unlocked = true;
            else if (option == "공포" && level >= 5) unlocked = true;
            else if ((option == "기묘" || option == "무거움") && level >= 10) unlocked = true;
        }
        else if (category == "분량") {
            if (option == "30") unlocked = true;
            else if (option == "90" && level >= 2) unlocked = true;
            else if (option == "120" && level >= 5) unlocked = true;
        }
        else if (category == "옛지 요소") {
            if (option == "없음") unlocked = true;
            else if (option == "반전" && level >= 5) unlocked = true;
        }
        else if (category == "기타") {
            if (option == "없음") unlocked = true;
            else if (option == "숨겨진 코드" && level >= 30) unlocked = true;
            else if ((option == "고대 룬" || option == "운명의 반전") && level >= 50) unlocked = true;
            else if ((option == "미래 예시" || option == "금단 기술") && level >= 80) unlocked = true;
        }

        filtered.push_back(unlocked ? option : "잠금");
    }

    return filtered;
}



std::vector<std::string> WritingElementManager::getOptions(const std::string& category) const {
    auto it = elements.find(category);
    return (it != elements.end()) ? it->second : std::vector<std::string>{};
}

void WritingElementManager::addElementOption(const std::string& category, const std::string& option) {
    elements[category].push_back(option);
}


bool WritingElementManager::isOptionAvailable(const std::string& category, const std::string& option) const {
    auto it = elements.find(category);
    if (it != elements.end()) {
        const auto& opts = it->second;
        return std::find(opts.begin(), opts.end(), option) != opts.end();
    }
    return false;
}
