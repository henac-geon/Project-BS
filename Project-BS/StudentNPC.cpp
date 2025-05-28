#include "NPC.h"
#include "StudentNPC.h"
#include "ConsoleIO.h"

/**

StudentNPC::StudentNPC(const std::string& name)
    : NPC(name, eBookGenre::Mystery, eBookMood::Light, 100, 10) {
}

*/

StudentNPC::StudentNPC(
    const std::string& name,
    bool isMale,
    eBookGenre genre,
    eBookMood mood,
    int gold,
    int magicPower)
    : NPC(name, isMale, genre, mood, gold, magicPower), 
    studyLevel(1){
}

Book* StudentNPC::requestBook(const std::vector<Book*>& candidates) {
    if (!candidates.empty()) return candidates.front();
    return nullptr;
}

bool StudentNPC::rateBook(Book* book) const {
    return NPC::rateBook(book);  // 학생 NPC 책 평가
}

// 책 손상에 대한 보상 처리
void StudentNPC::compensateForDamage(Book* book) {
}
