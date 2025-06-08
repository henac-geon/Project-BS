#pragma once

#ifndef AINPC_H
#define AINPC_H

#include "NPC.h"
#include <string>
#include <vector>

// OpenAI 또는 기타 AI 시스템에서 생성된 NPC 전용 클래스
class AINPC : public NPC {
private:
    int experience;  // AI 생성 캐릭터에 부여할 추가 특성 (예: 경험치)

public:
    AINPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int gold, int magicPower, const std::vector<std::string>& dialogues);

    // 필수 메서드 구현
    bool rateBook(Book* book) const override;
    bool borrowBook(Book* book) override;
    Book* returnBook() override;
    bool isReturningBook() const override;
    bool wantsRecommendation() const override;

    int payGold(int amount = 0) override;
    int payMagicPower(int amount = 0) override;
    int payExp(int amount = 0) override;

    void compensateForDamage(Book* book) override;
    void debugPrint() const override;

    // 추가 기능
    void setExperience(int exp);
    int getExperience() const;
};

#endif // AINPC_H
