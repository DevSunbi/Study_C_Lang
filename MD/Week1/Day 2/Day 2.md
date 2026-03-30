### HyperLink
* [[MD/Week1/Day 2/QnA|QnA]]
* [[MD/Week1/Day 2/CodeBase|CodeBase]]
---
## Intro
### 상수와 데이터 출력
* 모든 언어에서 동일하게 사용하고 있는 문장에 대한 종류
* 그 문장을 어떻게 쓰는지 살펴본다
* C언어에 국한되어 나오는 내용이 아닌, 모든 프로그래밍 언어에서 기본적으로 제공되고 있는 기능
* 데이터 표현 방법이 중요

## C 프로그램의 구조와 데이터 출력 방법
### 프로그램과 main 함수 구조
#### 출력 함수 사용법
* main **함수** - 프로그램이 시작되는 곳, 필수 함수 (entry point)
* 머리와 몸통으로 구성 (head-body)
* 머리 : 선언부
* 몸통 : 실행 코드
```C
int main(void) // head
{
	return 0; // body
}
```
* x에서 y로의 사상(mapping)을 시작으로 한 개념
* main -> func identifier (식별자)
* void(인자 없음 -> 비워놔도 됨) -> 인자 (parameter) (0-n개)
* int(2byte | 4byte) -> func return type (unique value)
* { } -> block으로 표현 -> n개의 statement로 구성
	* 한 줄에 여러 문장 기입 가능 -> ;으로 구분(statement terminator)
* 프로그램 : 어떠한 목적을 달성하도록 작성한 코드의 덩어리 (func 단위)
	* C의 경우 main함수에서 모든 일을 처리하고 끝내면 되는 것
* statement의 종류
	1. 실행문(대입, 연산 등) -> 문장 하나로 어떠한 결과를 나타내는 작업 단위
	2. 조건문(if)
	3. 반복문(while, for)
* 데이터 입력 -> 표준 라이브러리 -> OS -> I/O output => System call
* C언어에서 ( ) -> 함수 호출 시 인자
	* printf -> return은 int일 확률이 높음
![[Pasted image 20260324101647.png]]
* Compile 단계에서 Warning은 Pass
* Link 단계를 거칠 때 body+외부 lib 병합 작업 수행
	* 컴파일러에서 stdio.h include 안하면 오류 발생
	* 함수 참조의 문제 발생
* include 시 전처리기에 의한 텍스트 확장 진행
	* <> -> 표준 헤더 파일
		* system에서 제공해주는 표준 라이브러리 참조
		* system에서 미리 만들어둠, 특정 디렉토리에 저장되어 있음
	* " " -> 헤더파일 include 에서도 사용 가능하지만 <>와 조금 다름
		* 현 폴더에 본인이 만든 header file을 사용하겠다
		* 없으면 default include folder를 찾아 표준 헤더 파일 탐색
![[Pasted image 20260324102909.png]]
* inline : 코드 번역 시 함수 호출부에서 함수 내부 코드 그대로 사용
* int \_\_cdecl : 함수의 원시 타입
	* 함수에 여러 개의 인자를 넣으면 제일 우측 값부터 메모리 스택 영역에 적재
	* Caller가 메모리 정리함
* ... : 가변 인자
* char의 포인터
![[Pasted image 20260324103205.png]]
* entry 포인트 못찾으면 위와 같은 오류 발생
* 런타임 라이브러리에서 invoke_main호출, main 못찾아 에러 출력
	* 컴파일러는 include -> func define -> main -> func 순 읽음
	* 실행 시 main(func call) -> func jump -> return main
* 출력 자체는 I/O Buffer에 출력 OS가 I/O device에 명령(실행)

#### 제어 문자 출력
* \ : escape string (new line character)
	* 일반적인 문자가 아닌 특별한 뜻을 지닌 문자로 해석
* \n : Unix / Linux / Win OS 마다 해석 방법이 다름
	* 문자열 내에서 개행 문자(Carriage Return Line Feed)로 해석
	* 타자기에서 커서를 맨 앞으로 이동(CR, \r)하고 종이를 위로 올림(LF, \n)
	* Win OS -> CRLF 다 사용
	* Unix / Linux / MAC -> LF만 사용
* \t : Tab -> 일반적으로 8칸을 띄움
* \b : 뒤로 한 칸 이동 
* \a : alert

#### 정수와 실수 출력
* 가변 인자 함수(printf, scanf ...)
	* 인자가 몇 개인지 미정
	* % -> 출력 포맷(formatter)
	* digit : 정수
	* float : 실수(부동 소수점 실수)
	* lf : long float -> 자리 수 지정 시 직전 자리 반올림 후 출력
* left align -> 좌측 기준, 출력 진행

### 상수와 데이터 표현 방법
* Sign bit : 1 -> 음수
* Sign bit : 0 -> 양수
* 1 byte 표현 범위 : -128 - 127
* 2 byte : 2^15 ~ 2^16 - 1 => 32K
	* -32768 - 32767
* 정수 표현 : 2의 보수법만 알아두기
* C언어
	* char : 1byte (고정)
	* short : 2byte (고정)
	* int : 2 | 4byte (Linux / Win OS)
	* long : 타 자료형을 늘림
* 상수 컴파일 후 변환 -> Big endian / Small endian 방식 차이 존재
* 실수 -> 지수 / 소수부(Mantissa) 나뉨
	* 4 Byte 기준 -> Sign(1) + 지수(8) + 유효 소수(23)
	* 8 Byte 기준 -> Sign(1) + 지수(11) + 유효 소수(52)
		* 지수 파트 : Bias를 더해서 저장
		* 소수 파트 : 정규화를 통한 표현
		* 지수/정수 파트 나눠 저장

#### 문자와 문자열 상수 표현법
* 문자는 작은 따옴표, 문자열은 큰 따옴표로 묶음
* " " -> null terminate char array => Null 값이 나올 때 까지 반복
	* 'A' -> 1byte
	* "A" -> 2byte(A + Null)
* %s -> char을 Null 만날 때 까지 연속으로 받음
* 문자 상수는 아스키 코드 값 정수 형태로 변환
* 해석 방식에 따라 다른 데이터 취급 될 수 있음(%d, %c ...)
---

## 변수
#### 변수 선언 방법
* 자료형 + 변수명 (예약어 + identifier)
* 특수 문자 사용 x(_ 제외), 숫자로 시작 x
* '\_'로 변수 명 시작 시 컴파일러/표준 라이브러리 예약어 충돌 가능성 존재
* DataType identifier = expression; 형태로 변수 선언
* 계산 먼저 된 후 대입 연산자 작동(어딘가에는 계산 값 저장 됐다가 대입이 된다)
* 변수의 메모리 주소는 불변, 내부 값만 가변

#### 정수 자료형
* 정수 저장 자료형 종류
	* char
	* short
	* int
	* long
	* long long
* char형 변수
	* 저장되는 값은 문자의 아스키 코드 값
* unsigned keyword : sign bit을 일반 비트와 같이 해석 -> 무조건적 양수 표현
	* Overflow 발생 시(%d 사용) -> sign bit 해석 시작 -> 음수 출력 가능
	* 음수 저장 시(%u 사용) -> sign bit 무시 -> 최대 값 출력(-1 경우)
![[Pasted image 20260324161338.png]]
-> 메모리 현상 주목

![[Pasted image 20260324161356.png]]
=> 값 변화 확인 가능
(디버그-창-메모리-메모리1)
1. 컴파일러 해석
2. 실행 시 결과
=> 둘의 결과는 차이점 존재
* 컴파일러의 해석 규칙과 OS(f런타임)의 출력(포맷 해석) 규칙이 다를 수 있음

#### 문자열
* char (arrayname) (array length) = " "; => 항상 null character 포함
	* \0으로 인해 배열의 크기를 1이상 크게 확보 필수
* 대입문 -> 공간(메모리)에 value를 덮어 씀
* 초기화 -> 공간(메모리)를 만들고 데이터 넣음
* 변수 선언 이후 초기화 안하면 garbage 들어가 있을 수 있음
	* 하지만 전역 변수는 자동으로 0 초기화 지역 변수만 해당 됨
* \0만나면 무조건 문장 종료 -> 문장 중간에 \0 삽입하면 null point 직전까지 출력 후 끝남
* 배열에 할당된 문자 초과한 순서부터 출력 -> garbage 없으면 아무 것도 출력 안 됨(undefined)

#### const 이용한 변수
* 상수화 시키는 변수
* 대입연산자 사용 불가 -> 고정값
* const 변수는 초기화 필수 -> 대입이 불가하기에 초기에 정확한 값 부여 필수
