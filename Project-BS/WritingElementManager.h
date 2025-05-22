#pragma once

#ifndef WRITING_ELEMENT_MANAGER_H
#define WRITING_ELEMENT_MANAGER_H

#include <string>
#include <vector>
#include <map>

/**
 * @class WritingElementManager
 * @brief 집필에 사용되는 요소들을 관리하는 클래스
 *
 * 장르, 분위기, 분량, 옛지 요소, 기타 요소들을 카테고리별로 저장하고,
 * 선택 가능한 옵션을 제공하며, 동적으로 요소를 추가할 수도 있음.
 * 
 */
class WritingElementManager {
private:
    std::map<std::string, std::vector<std::string>> elements;

public:
    WritingElementManager();

    void loadDefaultElements(); // 기본 요소 초기화

    std::vector<std::string> getOptions(const std::string& category) const;
    std::vector<std::string> getAvailableOptions(const std::string& category, int level) const;
    void addElementOption(const std::string& category, const std::string& option);
    bool isOptionAvailable(const std::string& category, const std::string& option) const;
};

#endif // WRITING_ELEMENT_MANAGER_H
