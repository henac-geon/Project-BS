#include "CrudStore.h"
#include <iostream>
#include "ConsoleIO.h"

CrudStore::CrudStore()
    : experience(0), level(1), score(0),
    magicPower(MAX_MAGIC_POWER), gold(0), bookstoreRank(1), bookStock(0) {
    for (int i = 0; i < 5; ++i) {
        inventory.addBook(bookFactory.createRandomBook());
    }
}

void CrudStore::displayStatus() const {
    std::string line;
    line += "마법 기운: " + std::to_string(magicPower) + "   ";
    line += "골드: " + std::to_string(gold) + "   ";
    line += "LV." + std::to_string(level) + " (" + std::to_string(experience) + "%)   ";
    line += "서점 랭킹: Rank " + std::to_string(bookstoreRank) + "   ";
    line += "재고 상태: " + std::to_string(bookStock) + "/" + std::to_string(MAX_BOOK_STOCK);
    ConsoleIO::println(line);
}

void CrudStore::gainExperience(int amount) {
    if (amount < 0) return;
    experience += amount;
    checkLevelUp();
}

bool CrudStore::checkLevelUp() {
    while (level < MAX_LEVEL) {
        double requiredExp = 100.0 + (level - 1) * 20;
        if (experience >= requiredExp) {
            experience -= requiredExp;
            level++;
            std::cout << "레벨업! 현재 레벨: " << level << std::endl;
        }
        else break;
    }

    if (level >= MAX_LEVEL) {
        level = MAX_LEVEL;
        experience = 0.0;
    }

    return true;
}

int CrudStore::getLevel() const { return level; }
int CrudStore::getMagicPower() const { return magicPower; }
int CrudStore::getGold() const { return gold; }
double CrudStore::getExperience() const { return experience; }
int CrudStore::getBookstoreRank() const { return bookstoreRank; }
int CrudStore::getBookStock() const { return bookStock; }
int CrudStore::getMaxBookStock() const { return MAX_BOOK_STOCK; }

void CrudStore::consumeMagicPower(int amount) {
    if (amount < 0) return;
    magicPower -= amount;
    if (magicPower < 0) magicPower = 0;
}
void CrudStore::restoreMagicPower(int amount) {
    if (amount < 0) return;
    magicPower += amount;
    if (magicPower > MAX_MAGIC_POWER) magicPower = MAX_MAGIC_POWER;
}
void CrudStore::addMagicPower(int amount) {
    if (amount < 0) return;
    magicPower += amount;
    if (magicPower > MAX_MAGIC_POWER) magicPower = MAX_MAGIC_POWER;
}
void CrudStore::setMagicPower(int amount) {
    if (amount < 0) amount = 0;
    if (amount > MAX_MAGIC_POWER) amount = MAX_MAGIC_POWER;
    magicPower = amount;
}
void CrudStore::setGold(int amount) {
    if (amount < 0) amount = 0;
    if (amount > MAX_GOLD) amount = MAX_GOLD;
    gold = amount;
}
void CrudStore::addGold(int amount) {
    if (amount < 0) return;
    gold += amount;
    if (gold > MAX_GOLD) gold = MAX_GOLD;
}
void CrudStore::useGold(int amount) {
    if (amount < 0) return;
    gold -= amount;
    if (gold < 0) gold = 0;
}
void CrudStore::setBookstoreRank(int rank) {
    if (rank >= 1 && rank <= MAX_BOOKSTORE_RANK)
        bookstoreRank = rank;
}
void CrudStore::setBookStock(int stock) {
    if (stock < 0) stock = 0;
    if (stock > MAX_BOOK_STOCK) stock = MAX_BOOK_STOCK;
    bookStock = stock;
}
void CrudStore::adjustBookStock(int delta) {
    bookStock += delta;
    if (bookStock > MAX_BOOK_STOCK) bookStock = MAX_BOOK_STOCK;
    if (bookStock < 0) bookStock = 0;
}

int CrudStore::calculateGoldPenalty(const Book& book) const {
    return 0; // TODO: 구현 예정
}
int CrudStore::calculateMagicPenalty(const Book& book) const {
    return 0; // TODO: 구현 예정
}

void CrudStore::addScore(int amount) {
    score += amount;
}
void CrudStore::deductScore(int amount) {
    score -= amount;
    if (score < 0) score = 0;
}
int CrudStore::getScore() const {
    return score;
}

Inventory& CrudStore::getInventory() {
    return inventory;
}
BookFactory& CrudStore::getBookFactory() {
    return bookFactory;
}
WritingElementManager& CrudStore::getWritingElementManager() {
    return writingElementManager;
}

void CrudStore::addDailyGold(int amount) {
    dailyGoldEarned += amount;
    addGold(amount);
}
void CrudStore::addDailyScore(int amount) {
    dailyScoreEarned += amount;
    addScore(amount);
}
void CrudStore::addDailyMagicPower(int amount) {
    dailyMagicPowerEarned += amount;
    addMagicPower(amount);
}
void CrudStore::addDailyExperience(int amount) {
    dailyExperienceEarned += amount;
    gainExperience(amount);
}
int CrudStore::getDailyGoldEarned() const { return dailyGoldEarned; }
int CrudStore::getDailyScoreEarned() const { return dailyScoreEarned; }
int CrudStore::getDailyMagicPowerEarned() const { return dailyMagicPowerEarned; }
int CrudStore::getDailyExperienceEarned() const { return dailyExperienceEarned; }

void CrudStore::resetDailyEarnings() {
    dailyGoldEarned = 0;
    dailyScoreEarned = 0;
    dailyMagicPowerEarned = 0;
    dailyExperienceEarned = 0;
}

void CrudStore::displayDailySummary() const {
    ConsoleIO::println("\n[오늘의 정산 요약]");
    ConsoleIO::println("- 획득 골드: " + std::to_string(dailyGoldEarned));
    ConsoleIO::println("- 획득 점수: " + std::to_string(dailyScoreEarned));
    ConsoleIO::println("- 획득 마법 기운: " + std::to_string(dailyMagicPowerEarned));
    ConsoleIO::println("- 총 점수: " + std::to_string(score));
    ConsoleIO::println("- 현재 레벨: " + std::to_string(level));
}

//사용 가능한 요소 필터링
template <typename T>
std::vector<ElementData<T> > CrudStore::getAvailableElements(WritingElementCategory category) const {
    std::vector<ElementData<T> > all = writingElementManager.getElements<T>(category);
    std::vector<ElementData<T> > available;

    for (typename std::vector<ElementData<T> >::const_iterator it = all.begin(); it != all.end(); ++it) {
        const ElementData<T>& elem = *it;
        if (level >= elem.requiredLevel &&
            magicPower >= elem.magicCost &&
            gold >= elem.goldCost) {
            available.push_back(elem);
        }
    }

    return available;
}


// 장르, 분위기, 길이, 엣지, 기타 요소에 대한 책 집필 가능 여부 확인
// 책 생성 전 요소 유효성 검증
bool CrudStore::canAffordBookElements(eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) const {
    int totalMagic =
        writingElementManager.getMagicCost(WritingElementCategory::Genre, static_cast<int>(genre)) +
        writingElementManager.getMagicCost(WritingElementCategory::Mood, static_cast<int>(mood)) +
        length +
        writingElementManager.getMagicCost(WritingElementCategory::Edge, static_cast<int>(edge)) +
        writingElementManager.getMagicCost(WritingElementCategory::Etc, static_cast<int>(etc));

    return magicPower >= totalMagic;
}


// 책 집필 요청 함수
Book* CrudStore::tryWriteBook(const std::string& title, const std::string& desc,
    eBookGenre genre, eBookMood mood, int length,
    eBookEdge edge, eBookEtc etc) {
    if (!canAffordBookElements(genre, mood, length, edge, etc)) {
        ConsoleIO::println("마법 기운이 부족하여 책을 집필할 수 없습니다.");
        return nullptr;
    }

    int cost =
        writingElementManager.getMagicCost(WritingElementCategory::Genre, static_cast<int>(genre)) +
        writingElementManager.getMagicCost(WritingElementCategory::Mood, static_cast<int>(mood)) +
        length +
        writingElementManager.getMagicCost(WritingElementCategory::Edge, static_cast<int>(edge)) +
        writingElementManager.getMagicCost(WritingElementCategory::Etc, static_cast<int>(etc));

    consumeMagicPower(cost);
    return bookFactory.createBook(title, desc, genre, mood, length, edge, etc);
}

void CrudStore::displayAvailableElements() const {
    constexpr int COLUMN_WIDTH = 16;

    auto padRight = [](const std::string& str, int totalWidth) -> std::string {
        int padding = totalWidth - static_cast<int>(str.length());
        return str + std::string((padding > 0) ? padding : 0, ' ');
        };

    auto printCategoryHeaders = [&](const std::vector<std::string>& headers) {
        std::string line;
        for (const auto& h : headers) {
            line += padRight("[" + h + "]", COLUMN_WIDTH) + "  ";
        }
        ConsoleIO::println(line);
        };

    printCategoryHeaders({ "장르", "분위기", "분량", "엣지 요소", "기타" });

    auto genreList = getAvailableElements<eBookGenre>(WritingElementCategory::Genre);
    auto moodList = getAvailableElements<eBookMood>(WritingElementCategory::Mood);
    auto lengthList = getAvailableElements<int>(WritingElementCategory::Length);
    auto edgeList = getAvailableElements<eBookEdge>(WritingElementCategory::Edge);
    auto etcList = getAvailableElements<eBookEtc>(WritingElementCategory::Etc);

    // std::max 없이 최대 행 수 계산
    size_t maxRows = genreList.size();
    if (moodList.size() > maxRows) maxRows = moodList.size();
    if (lengthList.size() > maxRows) maxRows = lengthList.size();
    if (edgeList.size() > maxRows) maxRows = edgeList.size();
    if (etcList.size() > maxRows) maxRows = etcList.size();

    for (size_t row = 0; row < maxRows; ++row) {
        std::string line;

        auto format = [](const auto& elem) -> std::string {
            std::string name = enum_utils::toKoreanString(elem.element);
            std::string cost;
            if (elem.magicCost > 0) cost += "◆" + std::to_string(elem.magicCost);
            if (elem.goldCost > 0) {
                if (!cost.empty()) cost += " ";
                cost += "◎" + std::to_string(elem.goldCost);
            }
            return name + (cost.empty() ? "" : " [" + cost + "]");
            };

        auto getOrLock = [&](const auto& list) -> std::string {
            if (row < list.size()) return format(list[row]);
            return "(잠금)";
        };

        line += padRight(getOrLock(genreList), COLUMN_WIDTH) + "  ";
        line += padRight(getOrLock(moodList), COLUMN_WIDTH) + "  ";
        line += padRight(getOrLock(lengthList), COLUMN_WIDTH) + "  ";
        line += padRight(getOrLock(edgeList), COLUMN_WIDTH) + "  ";
        line += padRight(getOrLock(etcList), COLUMN_WIDTH);

        ConsoleIO::println(line);
    }
}
