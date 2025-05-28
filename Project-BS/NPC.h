#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"
#include "AsciiArtRepository.h"

class NPC {
protected:
    std::string name;
    eBookGenre preferredGenre;
    eBookMood preferredMood;
    std::vector<Book*> inventory;
    int gold;
    int magicPower;
    eRequestType requestType = eRequestType::GenreAndMood;
    std::string dialogue;
    bool borrowed = false;  // 책을 현재 대여 중인지 여부

public:
    NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower);
    virtual ~NPC() = default;

    // 게임 상호작용 인터페이스
    virtual Book* requestBook(const std::vector<Book*>& candidates) = 0;
    virtual bool rateBook(Book* book) const;
    virtual void compensateForDamage(Book* book) = 0;

    // 새로운 기능: 대여 / 반납 / 보상
    virtual bool borrowBook(Book* book);
    virtual Book* returnBook();
    virtual bool hasBorrowed() const;

    virtual void payGold(int amount);
    virtual void gainExp(int amount);

    // Getters
    std::string getName() const;
    eBookGenre getPreferredGenre() const;
    eBookMood getPreferredMood() const;
    const std::vector<Book*>& getInventory() const;
    int getGold() const;
    int getMagicPower() const;
    eRequestType getRequestType() const;
    std::string getArt() const;
    std::string getDialogue() const;

    // Setters
    void setName(const std::string& newName);
    void setPreferredGenre(eBookGenre genre);
    void setPreferredMood(eBookMood mood);
    void setGold(int newGold);
    void setMagicPower(int newMagicPower);
    void setRequestType(eRequestType type);
    void setDialogue(const std::string& line);
};

#endif // NPC_H
