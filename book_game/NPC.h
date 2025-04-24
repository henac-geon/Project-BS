#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Book.h"
#include "Enums.h"

class NPC {
protected:
    std::string name;
    eBookGenre preferredGenre;
    eBookMood preferredMood;
    std::vector<Book*> inventory;
    int gold;
    int magicPower;

public:
    NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower);
    virtual ~NPC() = default;

    virtual Book* requestBook(const std::vector<Book*>& candidates) = 0;
    virtual bool rateBook(Book* book) = 0;
    virtual void compensateForDamage(Book* book) = 0;
};

#endif // NPC_H
