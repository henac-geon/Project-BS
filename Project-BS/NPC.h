#pragma once

#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"

class NPC {
protected:
    std::string name;
    bool isMale;
    eBookGenre preferredGenre;
    eBookMood preferredMood;
    int gold;
    int magicPower;
    bool borrowed;
    eRequestType requestType;
    std::vector<Book*> inventory;
    std::vector<std::string> dialogues;

public:
    NPC(const std::string& name, bool isMale, eBookGenre genre, eBookMood mood, int gold, int magicPower)
        : name(name), isMale(isMale), preferredGenre(genre), preferredMood(mood),
        gold(gold), magicPower(magicPower), requestType(eRequestType::GenreOnly), borrowed(false){
    }

    virtual ~NPC() = default;

    virtual bool rateBook(Book* book) const = 0;
    virtual bool borrowBook(Book* book) = 0;
    virtual Book* returnBook() = 0;
    virtual bool isReturningBook() const = 0;
    virtual bool wantsRecommendation() const = 0;
    virtual void compensateForDamage(Book* book) = 0;
    virtual void debugPrint() const = 0;


    std::string getName() const;
    bool getIsMale() const;
    eBookGenre getPreferredGenre() const;
    eBookMood getPreferredMood() const;
    int getGold() const;
    void setGold(int amount);
    int getMagicPower() const;
    void setMagicPower(int amount);
    void removeBookFromInventory(Book* book);
    const std::vector<Book*>& getInventory() const;
    bool hasBookInInventory(const Book* book) const;
    eRequestType getRequestType() const;
    void setRequestType(eRequestType type);
    void payGold(int amount);
    void gainExp(int amount);
    std::string getArt() const;
    void setDialogues(const std::vector<std::string>& lines) { dialogues = lines; }
    const std::vector<std::string>& getDialogues() const { return dialogues; }

    bool hasBorrowed() const { return borrowed; }
};

#endif
