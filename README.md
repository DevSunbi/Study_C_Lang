# 🔵 stage/c-cpp — C / C++ 기초~OOP 심화

> VEDA 교육과정 中 **C언어 기초부터 C++ OOP 심화**까지의 강의 노트와 실습 코드를 담은 브랜치입니다.

---

## 🗂️ 브랜치 구조

```
stage/c-cpp/
├── MD/
│   ├── Week1/     # C 기초 (문법, 함수, 배열, 포인터)
│   ├── Week2/     # C 심화 + C++ 입문 (동적할당, 구조체, cin/cout)
│   └── Week3/     # C++ OOP 심화 (템플릿, STL)
└── workspace/
    ├── Week1/     # C 기초 실습
    ├── Week2/     # 구조체 실습, C++ 참조자/클래스/상속 실습
    └── Week3/     # 템플릿, STL 컨테이너 실습
```

---

## 📅 학습 커리큘럼

| 주차 | 일차 | 주제 | 핵심 내용 |
|------|------|------|-----------|
| **Week 1** | Day 1~5 | C 기초 & 포인터 | 기초 문법, 함수, 배열, **포인터**, 아스키코드 |
| **Week 2** | Day 6~7 | C 심화 & 메모리 | 문자열 함수, static 변수, **이중 포인터**, **동적 할당**(malloc/free) |
| **Week 2** | Day 8 | 구조체 & C++ 입출력 | `typedef struct`, Point/Line 구조체, C++ `cin/cout` |
| **Week 2** | Day 9 | C++ 심화 & OOP 입문 | **레퍼런스**, `new/delete`, 연산자 오버로딩, **예외처리**, 프로그래밍 패러다임 |
| **Week 2** | Day 10 | 객체지향 프로그래밍 | **클래스**, **캡슐화**, **추상화**, **상속**, **다형성**, UML, `this` |
| **Week 3** | Day 11 | 상속과 다형성 | 단일/다중 상속, 오버라이딩, **가상함수(`virtual`)**, 정적/동적 바인딩 |
| **Week 3** | Day 12 | 복사 생성자 & 정적 멤버 | **복사 생성자**, 얕은/깊은 복사, **정적 멤버(`static`)** |
| **Week 3** | Day 13 | 템플릿 & 표준 라이브러리 | **함수/클래스 템플릿**, 특수화, `string`, 파일시스템, 난수(`mt19937`) |
| **Week 3** | Day 14 | STL 컨테이너 & 알고리즘 | **Vector/List/Deque/Set/Map**, 반복자, Stack/Queue |

---

## 🔑 핵심 학습 목표

- ✅ C언어 문법 기초 및 입출력
- ✅ **포인터 및 메모리 구조** — 변수/배열/함수 포인터, 이중 포인터
- ✅ **동적 메모리 관리** — malloc/free, new/delete
- ✅ **구조체** — `typedef struct`, 패딩/바이트 정렬, 공용체, 열거형
- ✅ **파일 입출력** — fopen/fclose, fread/fwrite, fscanf/fprintf
- ✅ **C++ OOP** — 클래스, 캡슐화, 추상화, 상속, 다형성
- ✅ **복사 생성자** — 얕은 복사 vs 깊은 복사
- ✅ **템플릿(Template)** — 함수/클래스 템플릿, 특수화
- ✅ **STL 컨테이너** — vector, list, deque, set, map, stack, queue
- ✅ **반복자(Iterator)** — begin/end, const_iterator, 범위형 for

---

## 🔗 관련 브랜치

| 브랜치 | 내용 |
|--------|------|
| [`main`](../../tree/main) | 전체 프로젝트 소개 |
| [`stage/qt`](../../tree/stage/qt) | Qt 프레임워크 (Week4) |
| [`stage/embedded`](../../tree/stage/embedded) | 임베디드 시스템 (Week5~6) |
| [`stage/linux`](../../tree/stage/linux) | Linux / Bash (Week6~7) |
| [`group-study`](../../tree/group-study) | 알고리즘 스터디 |
