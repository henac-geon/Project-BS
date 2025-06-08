#pragma once

#ifndef WRITING_ELEMENT_MANAGER_H
#define WRITING_ELEMENT_MANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "Enum_Utils.h"
#include "Enums.h"

template <typename T>
struct ElementData {
    T element;
    int magicCost;
    int goldCost;
    int requiredLevel;
};

class WritingElementManager {
public:
    WritingElementManager();

    std::vector<eBookGenre> getAvailableGenres(int level) const;
    std::vector<eBookMood> getAvailableMoods(int level) const;
    std::vector<int> getAvailableLengths(int level) const;
    std::vector<eBookEdge> getAvailableEdges(int level) const;
    std::vector<eBookEtc> getAvailableEtcs(int level) const;

    int getMagicCost(WritingElementCategory category, int enumValue) const;
    int getGoldCost(WritingElementCategory category, int enumValue) const;

    void addGenreOption(eBookGenre genre, int magic, int gold, int level);
    void addMoodOption(eBookMood mood, int magic, int gold, int level);

    bool isGenreOptionAvailable(eBookGenre genre) const;
    bool isMoodOptionAvailable(eBookMood mood) const;

    template <typename T>
    std::vector<ElementData<T>> getElements(WritingElementCategory category) const;


    std::vector<std::string> getGenreNames() const;
    std::vector<std::string> getMoodNames() const;
    std::vector<std::string> getEdgeNames() const;
    std::vector<std::string> getEtcNames() const;

private:
    void loadElements();

    std::vector<ElementData<eBookGenre>> genres;
    std::vector<ElementData<eBookMood>> moods;
    std::vector<ElementData<int>> lengths;
    std::vector<ElementData<eBookEdge>> edges;
    std::vector<ElementData<eBookEtc>> etcs;
};

#endif // WRITING_ELEMENT_MANAGER_H
