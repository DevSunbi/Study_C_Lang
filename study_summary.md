# 📚 VEDA C/C++ 학습 요약본

> **학습 기간**: Week 1 (Day 1~5) + Week 2 (Day 6~10)  
> **학습 목표**: C언어 기초 → 포인터/메모리 → 구조체/파일 I/O → C++ OOP 입문

---

## 🗓️ Week 1 — C 언어 기초

---

### Day 1 — 프로그램과 컴파일러의 이해
📄 [[MD/Week1/Day 1/Day 1|Day 1 노트]] | [[MD/Week1/Day 1/CodeBase|CodeBase]] | [[MD/Week1/Day 1/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 컴퓨터 역사 | PC → 전용 Device → 범용 컴퓨터 발전, ASM → Fortran/Pascal/C |
| 언어 분류 | Compile Lang (C/C++/Java), Script Lang (Python/JS), OOPL (Java/C++/C#) |
| 빌드 과정 | `소스(.c)` → **Compile** → `목적파일(.obj)` → **Link** → `실행파일(.exe)` |
| 라이브러리 | SLL (정적 Static Link Lib), DLL (동적 Dynamic Link Lib) |
| 실행 흐름 | OS → 파일 탐색 → User 영역 로드 → entry point(`main`) → 실행 → OS 반환 |

**키워드**: `entry point`, `forward referencing`, `Debug vs Release`, `CISC/RISC`, `.slnx`, `.vcxproj`

---

### Day 2 — C 프로그램 구조 & 자료형
📄 [[MD/Week1/Day 2/Day 2|Day 2 노트]] | [[MD/Week1/Day 2/CodeBase|CodeBase]] | [[MD/Week1/Day 2/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| main 함수 구조 | 머리(선언부) + 몸통(실행코드), entry point |
| printf/scanf | 가변 인자 함수, 형식 지정자(`%d`, `%f`, `%s`, `%c` ...) |
| 제어 문자 | `\n`(LF/CRLF), `\t`(Tab), `\b`(뒤로), `\a`(alert) |
| 정수 자료형 | `char(1)`, `short(2)`, `int(2/4)`, `long`, `long long` |
| 실수 표현 | sign(1) + 지수(8) + 유효소수(23) — 4Byte 기준 부동소수점 |
| 문자열 | null-terminated char array, `'A'`(1byte) vs `"A"`(2byte = A + \0) |
| const | 상수화 변수, 선언 시 초기화 필수, 이후 대입 불가 |

**키워드**: `unsigned`, `sign bit`, `Big/Little Endian`, `escape character`, `%d vs %u`

---

### Day 3 — 입력, 연산자, 제어문, 함수
📄 [[MD/Week1/Day 3/Day 3|Day 3 노트]] | [[MD/Week1/Day 3/CodeBase|CodeBase]] | [[MD/Week1/Day 3/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| scanf | `&`(주소 연산자) 필수, 포인터로 타 함수의 변수에 간접 접근 |
| 연산자 | 산술/비교/비트(`<<`, `>>`)/대입(우선순위 최하) |
| 형 변환 | 묵시적(자동) / 명시적(`(type)identifier`) |
| 선택문 | `if-else`, `switch-case` (case에는 반드시 상수만 가능) |
| 반복문 | `while`, `do-while`(최소 1회 실행), `for(초기;조건;증감)` |
| 함수 | 함수명 + 매개변수 + 반환형, main 위에 `prototype` 선언 필요 |
| 메모리 구조 | Code Segment / Data Segment (Stack / Heap / Static(Global)) |

```c
// Call by Value vs Call by Address
void swap_value(int x, int y)  { /* 원본 변경 안 됨 */ }
void swap_ptr(int *x, int *y)  { /* 원본 변경 됨    */ }
```

**키워드**: `Segment Fault`, `call by value`, `Scope Rule`, `break`, `continue`, `Stack 공간 할당/해제`

---

### Day 4 — 배열
📄 [[MD/Week1/Day 4/Day 4|Day 4 노트]] | [[MD/Week1/Day 4/CodeBase|CodeBase]] | [[MD/Week1/Day 4/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 배열 선언 | 자료형별 공간 결정, C는 index-out-of-bounds 자동 체크 안 함 |
| 초기화 규칙 | 요소 수 < 초기값 → 남은 공간 Null, 요소 수 > 초기값 → Overflow |
| 문자 배열 | `\0` 고려해 **n+1** 크기 확보, `gets`/`puts` 사용 권장 |
| 배열과 함수 | 배열명은 주소 상수 → 포인터 취급, size 함께 전달 |
| 복사 개념 | 일반 요소 → **깊은 복사**, 포인터/구조체 → **얕은 복사** |

```c
// 배열 크기 역산 공식
int count = sizeof(arr) / sizeof(arr[0]);
```

---

### Day 5 — 포인터
📄 [[MD/Week1/Day 5/Day 5|Day 5 노트]] | [[MD/Week1/Day 5/CodeBase|CodeBase]] | [[MD/Week1/Day 5/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 포인터 변수 | 주소 값을 저장하는 변수, 항상 8byte (64bit 기준) |
| 역참조 | `*p` → 포인터가 가리키는 주소의 실제 값 읽기 |
| 포인터 연산 | `p+1` → 타입 크기만큼 주소 이동 (int: +4, char: +1) |
| const 포인터 | `int * const p` / `const int * p` / `const int * const p` |
| Call by pointer | 함수 밖 변수 값 직접 수정 가능, 여러 값 반환 가능 |
| 배열과 포인터 | `a[1] == *(a+1)`, 배열명은 주소 상수, 포인터는 주소 변수 |

```c
int a = 10;
int *p = &a;   // p = a의 주소 (포인터)
*p = 20;       // 역참조 → a의 값을 20으로 변경
printf("%d", a); // 출력 : 20
```

**키워드**: `가상 메모리(Virtual Memory)`, `역참조(Dereference)`, `null 초기화`, `uintptr_t`

---

## 🗓️ Week 2 — C 고급 + C++ 입문

---

### Day 6 — 문자열 함수 & 변수 영역 & 다차원 배열
📄 [[MD/Week2/Day 6/Day 6|Day 6 노트]] | [[MD/Week2/Day 6/CodeBase|CodeBase]] | [[MD/Week2/Day 6/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 문자열 복사 | `strcpy(dest, src)` — dest는 반드시 배열(포인터 불가) |
| 문자열 연결 | `strcat` / `strncat` — 기존 문자열의 `\0` 위치부터 복사 |
| 문자열 길이 | `strlen` — 배열 크기 아닌 실제 문자 수(\0 이전까지) |
| 문자열 비교 | `strcmp` / `strncmp` — ASCII 코드 값으로 비교 |
| 버퍼 문제 | `scanf` 후 `\n` 버퍼에 잔류 → `getchar()`로 소모 |
| 지역/전역 변수 | Stack(지역, 자동해제) / Global(전역, 프로그램 종료까지) |
| static 변수 | Data Segment 할당, lifecycle 전체 유지, 함수 전용 공간 |
| 레지스터 변수 | `register` 키워드, 메인 메모리 미사용, 주소값 없음 |
| 2차원 배열 | 행×열 구조, base size = 1차원 배열 한 줄의 크기 |

---

### Day 7 — 고급 포인터 & 동적 메모리 할당
📄 [[MD/Week2/Day 7/Day 7|Day 7 노트]] | [[MD/Week2/Day 7/CodeBase|CodeBase]] | [[MD/Week2/Day 7/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 포인터 배열 | `char *pary[5]` → char* 포인터가 5개인 배열 |
| 이중 포인터 | `**pp` → 포인터의 포인터 (2차원 배열을 대체 **불가**) |
| 배열 포인터 | `int (*pa)[4]` → int 4개짜리 1차원 배열을 가리키는 포인터 |
| 함수 포인터 | 함수도 Code Segment에 주소 존재 → 포인터로 저장 후 간접 호출 |
| void 포인터 | 어떤 타입도 저장 가능, 사용 시 반드시 **형변환 필수** |
| `malloc` / `free` | Heap 공간 수동 할당/해제, 미해제 시 **메모리 누수** 발생 |
| `calloc` | 할당 후 **0으로 초기화** |
| `realloc` | 기존 할당 공간 크기 조정 (여유 없으면 새 공간 할당 후 복사) |

```c
// malloc 기본 패턴
int *arr = (int *)malloc(sizeof(int) * 10);
if (arr == NULL) { /* 할당 실패 처리 */ }

// ... 사용 ...

free(arr);
arr = NULL;  // 댕글링 포인터(Dangling Pointer) 방지 필수!
```

> ⚠️ `free` 후 반드시 `NULL` 초기화 → 이후 잘못된 주소 재접근 방지

---

### Day 8 — 사용자 정의 자료형 & 파일 I/O & 전처리 & C++ 시작
📄 [[MD/Week2/Day 8/Day 8|Day 8 노트]] | [[MD/Week2/Day 8/CodeBase|CodeBase]] | [[MD/Week2/Day 8/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| 구조체(`struct`) | 여러 자료형을 하나의 타입으로 묶음, 멤버별 독립 메모리 |
| 패딩 바이트 | 가장 큰 자료형 기준으로 padding 결정, `sizeof`로 확인 |
| 구조체 포인터 | `ps->val` 또는 `(*ps).val` (화살표 연산자) |
| 자기 참조 구조체 | 본인 타입의 포인터 멤버 → 연결 리스트 등에 활용 |
| 공용체(`union`) | 하나의 메모리 공간을 여러 멤버가 공유 |
| 열거형(`enum`) | 관련 상수를 묶어 타입으로 관리, 내부적으로 `int` |
| 파일 I/O | `fopen` / `fclose` / `fgetc` / `fputc` / `fscanf` / `fprintf` / `fread` / `fwrite` |
| 전처리 지시자 | `#include`, `#define` (매크로), `#ifdef`, `#pragma pack` |
| 분할 컴파일 | 헤더, `extern`(타 파일 참조), `static`(현 파일 한정) |
| **C++ 시작** | `#include <iostream>`, `cin` / `cout`, `namespace std`, `endl` |

```cpp
// C++ 기본 입출력
#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    cout << "입력값: " << a << endl;
    return 0;
}
```

**실습 파일**: [[workspace/Week2/CPPSolution/Day8CppApp/Day8CppApp.cpp|Day8CppApp.cpp]]

---

### Day 9 — C++ 데이터 형식 & 예외 처리 & OOP 패러다임
📄 [[MD/Week2/Day 9/Day 9|Day 9 노트]] | [[MD/Week2/Day 9/CodeBase|CodeBase]] | [[MD/Week2/Day 9/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| C++ 형변환 | `static_cast`, `const_cast`, `dynamic_cast`, `reinterpret_cast` |
| dynamic_cast | 안전한 다운캐스팅 확인, OOP 다형성에서 중요 |
| L-value / R-value | L: 수정 가능한 메모리 위치 / R: 임시값·리터럴 |
| `new` / `delete` | C++ 동적 메모리 할당 (`malloc/free` 대체) |
| 레퍼런스(`&`) | 변수의 별칭, 포인터보다 안전한 참조 방식 |
| 예외 처리 | `try { throw } catch(Type e) { }`, 스택 풀기(Stack Unwinding) |
| `noexcept` | 예외 없음 명시, 컴파일러 최적화 용이 |
| OOP 패러다임 | 비구조적 → 절차적(C) → **객체지향(C++)** |

```cpp
// 레퍼런스 vs 포인터
int a = 10;
int &ref = a;   // 레퍼런스: a의 별칭 (포인터 없이 직접 참조)
int *ptr = &a;  // 포인터: a의 주소 저장

// 예외 처리 패턴
try {
    if (x < 0) throw "음수 입력 오류";
} catch (const char* e) {
    cout << e << endl;
}
```

---

### Day 10 — OOP: 클래스, 캡슐화, 상속, 다형성
📄 [[MD/Week2/Day 10/Day 10|Day 10 노트]] | [[MD/Week2/Day 10/CodeBase|CodeBase]] | [[MD/Week2/Day 10/QnA|QnA]]

**핵심 개념**

| 주제 | 내용 |
|------|------|
| **OOP 4대 원칙** | 캡슐화, 추상화, 상속, 다형성 |
| 클래스 | 데이터(멤버 변수) + 함수(멤버 함수), `::` 범위 지정 연산자 |
| 접근 지정자 | `public(+)`, `private(-)`, `protected(#)` |
| 객체/인스턴스 | 클래스 = 설계도, 인스턴스 = 메모리에 실체화된 객체 |
| 생성자/소멸자 | 객체 생성/소멸 시 자동 호출되는 특수 함수 |
| `this` 포인터 | 멤버 함수 호출 객체의 주소를 담은 숨겨진 포인터 |
| getter/setter | 캡슐화 구현, private 변수 접근 제어 및 유효성 검증 |
| UML | 클래스 다이어그램(정적), 시퀀스/상태 다이어그램(동적) |
| Is-a / Has-a | 상속 관계 / 소유 관계 |

```cpp
class Monster {
private:
    int hp;
    int power;
public:
    // getter / setter
    int get_hp() const { return hp; }
    void set_hp(int h) { if (h >= 0) hp = h; }

    void get_damage(int dmg) { hp -= dmg; }
    void attack(Player& p);
    virtual void attack_special(Player& p);  // 다형성 (오버라이딩)
};

// 객체 선언 (정적 / 동적)
Monster m1;                       // 정적 선언 (Stack)
Monster *m2 = new Monster();      // 동적 선언 (Heap)
delete m2;
```

---

## 📁 실습 파일 위치

| 구분 | 경로 |
|------|------|
| Week1 실습 | [[workspace/Week1]] |
| Week2 실습 | [[workspace/Week2]] |
| C++ 실습 (Day8~) | [[workspace/Week2/CPPSolution]] |
| GroupStudy 정렬 | [[GroupStudy]] |

### 그룹 스터디 — 정렬 알고리즘

| 파일 | 내용 |
|------|------|
| [[GroupStudy/bubble_sort.cpp\|bubble_sort.cpp]] | 버블 정렬 (Bubble Sort) |
| [[GroupStudy/selection_sort.cpp\|selection_sort.cpp]] | 선택 정렬 (Selection Sort) |
| [[GroupStudy/Insertion_Sort.cpp\|Insertion_Sort.cpp]] | 삽입 정렬 (Insertion Sort) |
| [[GroupStudy/practice_2751.c\|practice_2751.c]] | BOJ 2751 — 수 정렬하기2 |

---

## 🗺️ 전체 학습 흐름

```
Week 1                              Week 2
──────────────────────────────────────────────────────────────
Day 1  : 컴파일러/빌드/OS 동작      Day 6  : 문자열 함수/변수영역/2차원 배열
Day 2  : 자료형/출력/문자열 기초    Day 7  : 고급 포인터/동적 메모리 할당
Day 3  : 입력/연산자/제어문/함수    Day 8  : 구조체/파일I/O/전처리 → C++ 시작
Day 4  : 배열 선언/초기화/문자배열  Day 9  : C++ 형변환/예외처리/OOP 개념
Day 5  : 포인터 핵심                Day 10 : 클래스/캡슐화/상속/다형성
```

> **Next Step**: 상속 심화 → 가상함수(`virtual`) → 순수 가상함수/추상 클래스 → STL (vector, map...)
