#include "WritingElementManager.h"
#include <algorithm>

WritingElementManager::WritingElementManager() {
    loadDefaultElements();
}

void WritingElementManager::loadDefaultElements() {
    elements.clear();

    elements["장르"] = { "판타지", "공상과학", "아포칼립스" };
    elements["분위기"] = { "몽환", "암울", "공포" };
    elements["분량"] = { "30", "90", "120" };
    elements["옛지 요소"] = { "없음", "반전" };
    elements["기타"] = { "없음" };
}

std::vector<std::string> WritingElementManager::getOptions(const std::string& category) const {
    auto it = elements.find(category);
    if (it != elements.end()) {
        return it->second;
    }
    return {};
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
