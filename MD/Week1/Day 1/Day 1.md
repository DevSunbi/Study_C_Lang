# C Lang Base
### HyperLink
* [[Intro(OT)]]
* [[MD/Week1/Day 1/QnA]]
* [[MD/Week1/Day 1/CodeBase]]
* Repo : [C:\Users](C:\Users\Sunbi\source\repos)
---

## Intro
* C언어 베이스 -> 포인터 및 구조체, 메모리 함수 주로 다룰 예정
* C언어 -> pointer의 의존성
* C-ASM까지 가능하도록 공부
---
## 1. 프로그램 만들기

### Summery
* 기본적인 얘기 진행 예정
	* 개발 환경 설정
	* Device의 역사
		* PC -> 전용 Device였다 => 범용이 아니였다
		* 계산 : HW로 했었다
		* 범용 컴퓨터를 위한 필수 조건
			* 스스로 CPU, Memory, I/O Device 사용(제어) 가능한 환경
			* 이를 위해선 SW 필요 => Operating System(OS)의 시작
			* OS(Windows) 이전 => Basic Interpreter 만짐 : 빌게이츠
			* OS가 알아 들을 수 있는 명령어 => 전자기 신호(0, 1)
			* DEC <-> BIN 호환의 차이 => 알아 듣는 방법의 부재 -> 명령어 set이 적음
			* OS => User와의 상호작용 중점 -> 원하는 작업을 위해선 Lang 필요
			* Nibble(4bit base) - Byte computer(256) => 현 2^64 (64 bit)
			* 각 제조사 등장 -> 칩 마다의 명령어 편이 해짐
			* CISC(복잡한 작업) - RISC(포맷 정형화)
			* ASM 등장 -> ADD, MOV, LOAD, SAVE 등(기계어 1:1 Mapping)
			* ASM 이후 Fortran, Pascal, C 등장 (gen 3 Lang)
				* Assmbler 필요 => 기계어 변환 
			* 실시간 번역 => Interpreter
			* 최적화 필요 => compiler
---
### 프로그램과 C언어
* 옥수수로 팝콘을 만들어보자
	1. 냄비 준비
	2. 옥수수 알갱이 냄비에 담기
	3. 버터와 소금 넣기
	4. 가열
	5. 알갱이가 모두 터질 때까지 4번 반복
	6. 팝콘 꺼내기
* Sequential함 -> 이후 Threading을 통한 병렬 프로그래밍 가능
---
### Programming Language
* 컴퓨터가 이해하기 쉽게 명확한 표현 규칙 정의 => 안간 표현 중심
* C, C++, C#, Java, Python 등
* 필수 Stack
	* Compile Lang(C, C++, Java, Go...)
	* Script Lang(Python, JS, TS...)
	* OOPS (Java, C++, C#...)
---
### Compiler
* C++ compiler 내부에 C compiler도 있음
* 1 Solution = 1 Execution File
* 솔루션 빌드 -> 하나의 Application을 만든다로 생각해도 좋음
* Compile => 실행 가능하게 기계어로 번역 => Link(Startup)
* Build => Compile + Link => 라이브러리 연동 및 메모리 할당
* Debugging : 에러 출력문 더블 클릭 -> 문제 부분 출력 됨 => 문제 추적
* 솔루션 파일 : .slnx => 최상위 file => 프로젝트 구성 및 정보 담음
	* x : extended로 해석을 할 수도 있다 | C++의 경우 cxx로 표기하기도 함
	* .vcxproj => vsc project
* forward referencing : func prototype 명시(header)
* resource file : GUI 프로그램 제작 시 사용
	* C에서는 거의 사용 안 함 => 사용은 가능한데 보통 C는 Text base
	* MFC도 쓸 일이 없을듯 하다 => QT 사용함
* 참조(reference) : 외부 종속성 -> 외부 라이브러리 사용
	* C 라이브러리
		* static link lib(SLL) : 정적 라이브러리
		* Dynamic link lib(DLL) : 동적 라이브러리
* 솔루션 파일 공유 시 그냥 열어서 수정 가능함
* 솔루션이 아닌 vcsproj를 연다면 -> slnx 파일이 있으면 열림, 없으면 만들어서 씌워버림
* 빌드 -> 링크 생성
* 컴파일 -> 링크 작업과 분리 시 사용
* obj -> 목적 파일 : 기계어로 번역한 산출물이다 => 실행은 불가능
* 실행 => 메모리 마운트 시 내부 정의 및 시작 지정
	* 외부 lib 사용 시 실제 실행되는 라이브러리 마운트 exe 파일 만들기 위한 위치 찾기
- **obj(목적 파일)**: 소스 코드를 컴파일/어셈블한 중간 산출물, 기계어 코드와 심볼 정보 등을 포함하지만 단독으로는 실행 불가
- **링크**: 여러 목적 파일과 라이브러리를 결합하고 외부 심볼을 해결, 실행 파일을 생성
- **실행**: 운영체제가 실행 파일을 메모리에 적재, 필요한 동적 라이브러리를 로드한 뒤 프로그램의 진입점부터 실행
- **외부 라이브러리 사용 시**: 링크 단계에서 필요한 라이브러리를 연결, 동적 라이브러리의 경우 실행 시 운영체제가 해당 라이브러리를 찾아 로드
* Compile -> .obj(object) File
* Link ->.exe(excutable) file
=> Terminal / .exe 명령을 통한 실행 가능
* entry point -> 프로그램의 시작점 => 단일 이름으로 고정
	* C에서의 main(언어마다 다름)
* 실행한다 -> 소스 파일 내 문장들을 기계어로 번역, 수행한다
* ROM : Bootloader 내장(전원 인가 시 바로 실행)
	* HW 구성 체크
		* 우선 순위 : Display I/O(Graphic Device)
		* CPU - Memory ...
		* OS가 최종
* 헤더 분석 후 기계어로 번역, 이후 메인 메모리로 올라와 프로그램 실행 됨
![[Pasted image 20260323154839.png]]
* .COM 파일 형식으로 작성한 hello world!!의 일부
* OS에 명령 -> 해당 파일 메인 메모리에 올림 -> Main 함수 단계별 실행 -> OS 복귀(return 내용 갖고)
![[Pasted image 20260323161119.png]]

* Bit 수 증가 -> Data Bus에 적재 가능한 데이터량 증가
* 상위비트로 증가 -> 다량의 데이터 송수신, 명령어 증가
* Memory -> User / OS Core 파트 나뉨
	* OS Core : OS 주요 코드, I/O, Buffer 
	* User : 그 외
* a.exe 실행 -> Buffer에 들어감 -> 명령으로 해석, 내장 명령어인지 확인
	* 외부 명령어, 실행 파일, 배치 파일 존재 따짐 -> HDD의 현 위치에 있는지 찾아라 명령
	* index를 보고 파일을 찾음 -> 읽은 후 User 영역으로 가져옴
	* 메인메모리에 올린 후 필요 없어지면 HDD에 switching
* 메인 메모리에 적제 되면 OS는 entry point 찾아 실행
	* 이후 Buffer에 들어가 있음 => 수행 trigger(interrupt) 발생 시 User 파트로 옮김
	* 실행 시 OS로 리턴(return)
	* 리턴의 상태는 여러 가지 있음 0(정상), 1, -1(비정상) , 2 등 (1, 2는 개인 설정)
	* OS의 명령 끝난 후 일단 Holding, 여유 있으면 남겨둠, 공간 부족 시 휘발
	* Main Memory가 적을 수록 context switching 작업 많아짐 -> 느림

![[Pasted image 20260323171103.png]]
* Release
![[Pasted image 20260323171119.png]]
* Debug
* 용량 차이가 심함이 보임
* Release 모드로 배포해야 사이즈도 작고 수정 방지 가능