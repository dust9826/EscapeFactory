# EscapeFactory

Unreal Engine 5에서 C++과 블루프린트를 함께 써서 만든 공장 자동화 프로젝트입니다(2026.02, 1인). 게임 내에 등장하는 모든 액터를 "아이템"으로 추상화해 동작하도록 설계했습니다.

- 기술 Unreal Engine 5, C++, Blueprint

## 구현

- **아이템 추상화** — 소품·기계·플레이어 보유물을 하나의 추상 타입으로 통합. 인터페이스 + 데이터 에셋 기반이라 새 아이템을 추가할 때 기존 코드 수정이 최소화됩니다. 코어 인터페이스는 C++, 개별 동작·연출은 블루프린트로 분리했습니다.
- **액터 공용 인벤토리** — 플레이어·기계·컨테이너가 같은 인벤토리 컴포넌트를 공유하고, 슬롯 단위 입출력 인터페이스를 통일해 액터 간 아이템 이동을 한 곳에서 처리합니다.
- **기계 동작** — 입력 → 가공 → 출력의 공통 사이클을 베이스 기계 클래스에 두고, 레시피는 데이터 에셋으로 분리해 코드 변경 없이 새 기계·공정을 추가할 수 있습니다.

## 링크

- 프로젝트 상세 (Notion): [EscapeFactory](https://military-guanaco-a36.notion.site/353a22a5543980ff8b94c438a7dd4c7f)
- 포트폴리오: [Notion](https://military-guanaco-a36.notion.site/352a22a5543980f5be50d4660a744e8e) · [PDF](https://drive.google.com/file/d/11B7ugR6RwQhI4dSEP5VHTsIx2B1_gTAP/view)
