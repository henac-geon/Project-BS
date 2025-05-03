#include "NPC.h"    // NPC 클래스 정의 헤더 포함

/**
 * @brief NPC 클래스 생성자 구현
 *
 * @param name        NPC의 고유 이름
 * @param genre       NPC가 선호하는 책 장르 (Enums.h에 정의된 eBookGenre)
 * @param mood        NPC가 선호하는 책 분위기 (Enums.h에 정의된 eBookMood)
 * @param gold        초기 금화량 (게임 내 경제 시스템에서 사용)
 * @param magicPower  초기 마법력 (특정 상호작용이나 보상 시스템에서 사용)
 *
 * 본 생성자에서는 멤버 초기화 리스트를 사용하여 각 멤버 변수를
 * 전달받은 인수로 간결하고 안전하게 초기화합니다.
 */
NPC::NPC(const std::string& name, eBookGenre genre, eBookMood mood, int gold, int magicPower)
    : name(name), preferredGenre(genre), preferredMood(mood), gold(gold), magicPower(magicPower)
{
    // TODO: 필요 시 초기화 후 추가 로직을 여기에 구현
    // 예: 기본 인벤토리(Book 포인터)를 설정하거나,
    //     초기화 메시지 출력, 통계 증가 등
}
