#pragma once

#ifndef WRITING_ELEMENT_MANAGER_H
#define WRITING_ELEMENT_MANAGER_H

#include "enums.h"
#include "enum_utils.h" 
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

template<typename T>
struct WritingElement {
    T element;
    int magicCost;
    int requiredLevel;
};

class WritingElementManager {
public:
    WritingElementManager();

    // 요소 초기화
    void loadElements();

    // 레벨에 따라 잠금 해제된 요소 리스트를 반환함
    std::vector<eBookGenre> getAvailableGenres(int level) const;
    std::vector<eBookMood> getAvailableMoods(int level) const;
    std::vector<std::string> getAvailableLengths(int level) const;
    std::vector<eBookEdge> getAvailableEdges(int level) const;
    std::vector<eBookEtc> getAvailableEtcs(int level) const;

    // 요소 이름을 문자열로 반환 (enum_utils 사용)
    std::vector<std::string> getGenreNames() const;
    std::vector<std::string> getMoodNames() const;
    std::vector<std::string> getEdgeNames() const;
    std::vector<std::string> getEtcNames() const;

    // 마법 기운 소모량 조회
    int getMagicCost(WritingElementCategory category, int enumValue) const;

    // 동적 요소 추가 기능
    void addGenreOption(eBookGenre genre, int cost, int level);
    void addMoodOption(eBookMood mood, int cost, int level);

    // 해당 enum 요소가 존재하는지 확인
    bool isGenreOptionAvailable(eBookGenre genre) const;
    bool isMoodOptionAvailable(eBookMood mood) const;

private:
    // 요소별 저장 컨테이너
    std::vector<WritingElement<eBookGenre>> genres;
    std::vector<WritingElement<eBookMood>> moods;
    std::vector<WritingElement<std::string>> lengths;
    std::vector<WritingElement<eBookEdge>> edges;
    std::vector<WritingElement<eBookEtc>> etcs;
};

#endif // WRITING_ELEMENT_MANAGER_H
