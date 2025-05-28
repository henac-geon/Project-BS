#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"
#include "AsciiArtRepository.h"

class NPC {
private:
    std::string name;
    eBookGenre preferredGenre;
    eBookMood preferredMood;
    int gold;
    int magicPower;
    bool borrowed;
    std::vector<Book*> inventory;

    eRequestType requestType;
    std::string dialogue;

public:
    NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower);

    // 책 추천에 대한 반응
    bool rateBook(Book* book) const;

    // 대여/반납 관련
    bool borrowBook(Book* book);
    Book* returnBook();
    bool hasBorrowed() const;

    // NPC의 행동 결정
    bool isReturningBook() const;
    bool wantsRecommendation() const;

    // 재화 관련
    void payGold(int amount);
    void gainExp(int amount);

    // 상태 getter/setter
    std::string getName() const;
    void setName(const std::string& newName);

    eBookGenre getPreferredGenre() const;
    void setPreferredGenre(eBookGenre genre);

    eBookMood getPreferredMood() const;
    void setPreferredMood(eBookMood mood);

    const std::vector<Book*>& getInventory() const;

    int getGold() const;
    void setGold(int newGold);

    int getMagicPower() const;
    void setMagicPower(int newMagicPower);

    eRequestType getRequestType() const;
    void setRequestType(eRequestType type);

    std::string getDialogue() const;
    void setDialogue(const std::string& line);

    std::string getArt() const;

    void debugPrint() const;
};


#endif // NPC_H
