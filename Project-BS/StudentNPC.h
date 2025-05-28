#pragma once
#ifndef STUDENTNPC_H
#define STUDENTNPC_H

#include "NPC.h"
#include "Book.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief 학생 NPC 클래스
 * 공부 목적의 독서 성향을 가지며, 예산이 제한적일 수 있음
 */
class StudentNPC : public NPC {
private:
    int studyLevel; ///< 학생의 학습 수준 (예: 0~100)

public:
    /**
     * @brief StudentNPC 생성자
     * @param name NPC 이름
     * @param genre 선호하는 책 장르
     * @param mood 선호하는 책 분위기
     * @param gold 보유 금액
     * @param studyLevel 학습 수준
     */
    StudentNPC(const std::string& name,
        eBookGenre genre,
        eBookMood mood,
        int gold,
        int studyLevel);

    /**
     * @brief 후보 책 목록 중 하나를 선택하여 요청
     * @param candidates 후보 책 리스트
     * @return 선택된 책 객체 포인터
     */
    Book* requestBook(const std::vector<Book*>& candidates);

    /**
     * @brief 책에 대한 만족 여부 판단
     * @param book 평가할 책 포인터
     * @return 평가 결과 (만족: true, 불만족: false)
     */
    bool rateBook(Book* book) const;

    /**
     * @brief 책 손상에 대해 보상 또는 사과 처리
     * @param book 손상된 책 포인터
     */
    void compensateForDamage(Book* book);

    /// Getter for studyLevel
    int getStudyLevel() const { return studyLevel; }

    /// Setter for studyLevel
    void setStudyLevel(int level) { studyLevel = level; }
};

#endif // STUDENTNPC_H
