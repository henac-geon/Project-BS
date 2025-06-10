# 📚 BookGameSystem

책 대여와 NPC 상호작용, 미니게임을 중심으로 한 **텍스트 기반 콘솔 게임**입니다.  
NPC는 자신의 취향에 맞는 책을 요청하며, 사용자는 그에 맞춰 책을 제공하고 반응을 관찰합니다.  
게임은 **하루 단위 루프**로 진행되며, 레벨/점수/보상 시스템과 함께 확장 가능한 구조로 설계되었습니다.

---

## 🧩 프로젝트 개요

- **객체지향 설계 기반**
- **UML 기반 설계 → C++ 구현**
- **GUI 없이 CLI(Text) 기반 출력**
- **CMake 기반 빌드 및 실행 계획**

---

## 🏗️ 주요 기능

### 📖 Book System
- 책의 장르/분위기 속성 (`Genre`, `Mood`)
- 손상/수리/상태 구분 (`DamageType`, `BookCondition`)
- 자동 생성 팩토리 패턴 지원

### 🧙‍♂️ NPC System
- NPC의 선호 장르 기반 책 요청
- 피해 보상 시스템 (골드/마법 기운)
- NPC 유형별 행동 다형성 지원

### 🎮 MiniGame System
- 책과 연계된 미니게임 시스템
- `MiniGame` 인터페이스 기반 구조
- 다양한 게임 방식 도입 가능 (타자, 퍼즐 등)

### 🧠 Game Loop & Manager
- `GameManager`를 통한 하루 단위 진행
- 사용자 모드/관리자 모드 전환
- 점수/레벨 시스템 통합

---

## 🧱 기술 스택

| 항목 | 내용 |
|------|------|
| 언어 | `C++14 이상` |
| 빌드 | `CMake` |
| 설계 | `PlantUML` 기반 UML |
| 개발 환경 | `Visual Studio`|
| CMake 호환 IDE |

---

## ▶️ 빌드 & 실행 방법

```bash
# 1. 프로젝트 클론
git clone https://github.com/your-team/BookGameSystem.git
cd BookGameSystem

# 2. 빌드 (CMake 사용)
mkdir build && cd build
cmake ..
cmake --build .

# 3. 실행
./BookGameSystem

[프로젝트 소개 영상]([https://www.youtube.com/watch?v=dQw4w9WgXcQ](https://youtu.be/B9qQArcYyiQ))
