#### g++ options
```bash
C:\Users\Sunbi\Desktop\VEDA\workspace\Week5>g++ --help
Usage: g++ [options] file...
Options:
  -pass-exit-codes         Exit with highest error code from a phase.
  --help                   Display this information.
  --target-help            Display target specific command line options (including assembler and linker options).
  --help={common|optimizers|params|target|warnings|[^]{joined|separate|undocumented}}[,...].
                           Display specific types of command line options.
  (Use '-v --help' to display command line options of sub-processes).
  --version                Display compiler version information.
  -dumpspecs               Display all of the built in spec strings.
  -dumpversion             Display the version of the compiler.
  -dumpmachine             Display the compiler's target processor.
  -foffload=<targets>      Specify offloading targets.
  -print-search-dirs       Display the directories in the compiler's search path.
  -print-libgcc-file-name  Display the name of the compiler's companion library.
  -print-file-name=<lib>   Display the full path to library <lib>.
  -print-prog-name=<prog>  Display the full path to compiler component <prog>.
  -print-multiarch         Display the target's normalized GNU triplet, used as
                           a component in the library path.
  -print-multi-directory   Display the root directory for versions of libgcc.
  -print-multi-lib         Display the mapping between command line options and
                           multiple library search directories.
  -print-multi-os-directory Display the relative path to OS libraries.
  -print-sysroot           Display the target libraries directory.
  -print-sysroot-headers-suffix Display the sysroot suffix used to find headers.
  -Wa,<options>            Pass comma-separated <options> on to the assembler.
  -Wp,<options>            Pass comma-separated <options> on to the preprocessor.
  -Wl,<options>            Pass comma-separated <options> on to the linker.
  -Xassembler <arg>        Pass <arg> on to the assembler.
  -Xpreprocessor <arg>     Pass <arg> on to the preprocessor.
  -Xlinker <arg>           Pass <arg> on to the linker.
  -save-temps              Do not delete intermediate files.
  -save-temps=<arg>        Do not delete intermediate files.
  -no-canonical-prefixes   Do not canonicalize paths when building relative
                           prefixes to other gcc components.
  -pipe                    Use pipes rather than intermediate files.
  -time                    Time the execution of each subprocess.
  -specs=<file>            Override built-in specs with the contents of <file>.
  -std=<standard>          Assume that the input sources are for <standard>.
  --sysroot=<directory>    Use <directory> as the root directory for headers
                           and libraries.
  -B <directory>           Add <directory> to the compiler's search paths.
  -v                       Display the programs invoked by the compiler.
  -###                     Like -v but options quoted and commands not executed.
  -E                       Preprocess only; do not compile, assemble or link.
  -S                       Compile only; do not assemble or link.
  -c                       Compile and assemble, but do not link.
  -o <file>                Place the output into <file>.
  -pie                     Create a dynamically linked position independent
                           executable.
  -shared                  Create a shared library.
  -x <language>            Specify the language of the following input files.
                           Permissible languages include: c c++ assembler none
                           'none' means revert to the default behavior of
                           guessing the language based on the file's extension.

Options starting with -g, -f, -m, -O, -W, or --param are automatically
 passed on to the various sub-processes invoked by g++.  In order to pass
 other options on to these processes the -W<letter> options must be used.

For bug reporting instructions, please see:
<https://github.com/niXman/mingw-builds>.
```
* 가장 많이 쓰는 option
	* -o \<file> : Place the output into \<file>
		* compile process : pre-compile -> Object code gen Compile -> Link
	* -c : Compile and Assemble, but do not link 
		* Obj Code gen -> .obj/.o file gen
	* -s : Compile Only; do not assemble or link
		* 배포용 빌드
	* -B \<dir> : Add dir to the compiler's search paths
		* 특정 컴파일러 버전 지정을 위함
		* 혹은 버전 확인 시 사용함
* exe를 만든다 -> main이름을 지닌 파일이 존재해야함 -> -o option 사용
* 여러 함수를 분리 -> 분리 컴파일 시 -c option 사용
	* 차후 main func을 갖는 파일과 Link를 시켜 .exe 생성

* 신경 쓸 option
	* -std=\<standard> : Assume that the input sources are for \<standard>
		* C의 표준이 존재
		* E.g) g++ main.cpp -std=c++11
		* 매년 표준 형태의 변화로 인해 여러 문법이 추가 됨
		* std 버전 셋팅을 통해 강제적으로 지정, 언어 규격 정의
	* -Werror : warning option
		* warning의 level을 설정 가능
		* warning을 error로 할지, 넘어갈지
		* Wall => 모든 잠재적 warning을 표기, 잠재적 오류
		* Werror => 모든 warning을 error로 변환
	* -l \<lib_name> : 특정 라이브러리 사용을 의미
		* 표준 라이브러리에 thread가 없는 경우, `-l thread`를 통해 include 가능
#### Embedded Software
* OS 위에서 동작하는 타입과 OS 없이 동작하는 타입 존재
	* 대표적인 예시 RPi/Arduino
* OS Embedded
	* App
	* MiddleWare -> 기능 존재
	* OS -> 기능 존재
	* HW(MCU)
* None-Os Embedded
	* App
	* HW(MCU)
	* => 미들웨어, 운영체제의 기능이 없다
	* 최소한의 기능은 lib 형태로 제공
#### 크로스 개발환경
* PC와 Embedded System의 cpu 차이 존재
	* PC : Intel(CISC) / Ryzen
	* Embedded : ARM(RISC)
	* => 호환 자체가 안되는 다른 구조라 생각

| 단계  | 이름          | 역할                                  | input           | output       | 대표 명령어              |
| --- | ----------- | ----------------------------------- | --------------- | ------------ | ------------------- |
| 1   | pre-process | code macro 전개                       | 전처리 소스(.c file) | .i file      | \#include           |
| 2   | 컴파일 처리      | C코드->ASM                            | .i file         | .s file      | gcc -S              |
| 3   | 어셈블리 처리     | ASM->obj code                       | .s 파일           | obj file     | as, .s, -> .o       |
| 4   | 링크 처리       | 여러 obj file + lib -> 실행 가능한 파일로 결합  | .o files(+ lib) | 실행 파일        | ld, gcc -o          |
| 5   | HEX 파일 처리   | 실행 파일을 MCU가 읽을 수 있는 HEX/BIN 포맷으로 변환 | .elf, .out file | .hex, .bin파일 | objcopy, elf -> hex |

 ```c
 #include <stdio.h>
	
int main()
{
	int i = 10;
	int j = i + 11;
	return 0;
}
 ```
 ```asm
 .text

main:
	mov R0, #10
	mov R1, #11
	add R0, R0, R1
	bx lr
.end
 ```

#### main 함수 추적
* `<__vectors>:` -> 인터럽트 벡터 설정
* `<__ctors_end>:` -> 스택 포인터 초기 설정
* `jmp(call) address` -> branch 명령어로 생성, 특정 번지 수로 이동 => 해당 함수 호출

#### Memory Map
* 메모리 각 영역의 역할을 나눈 것
* 메모리맵은 코드영역(ROM)과 데이터 영역으로 나뉜다(RAM)
	* 코드 영역이 ROM -> Embedded는 한번 작성한 코드는 계속해서 유지
	* 데이터 영역이 RAM -> 데이터는 계속 바뀜

#### Stack
* LIFO 구조의 메모리 영역
* 함수 호출 시마다 지역 변수, 리턴 주소, 레지스터 값 등을 저장

#### Stack n Interrupt
* 인터럽트 발생 시
	1. 현재 실행 중인 명령 중단
	2. 현재 CPU에 상태 저장(PC, 상태 레지스터 등)
		* ->스택에 저장
	3. 인터럽트 서비스 루틴(ISR) 실행
	4. 스택에서 이전 상태 복원
	5. 중단된 위치부터 다시 실행

#### ICE
* 임베디드 시스템에 탑재되어 있는 CPU를 대신해서 동작하는 기기

#### ARM
* 1985년 에이콘 컴퓨터에서 고안
* 1990년 ARM Limited 설립
* 양국 기반 합작 투자 회사 = 에이콘 컴퓨터, 애플 컴퓨터, VLSI 테크놀로지
* Advanced RISC Machine

#### RISC vs CISC
| RISC(Reduced Instruction Set Computer)                                               | CISC(Complex Instruction Set Computer)                                               |
| ------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------ |
| CPU 명령어 개수 줄임, 파이프라인<br>HW 구조 간단화<br>모든 연산 하나의 클럭으로<br>명령어 길이 고정<br>CISC 대비 소모 전류 적음 | Program을 위한 수많은 명령으로 구성<br>HW 구조 복잡<br>복잡한 명령의 집합 가짐<br>HW 스택 지원<br>RISC 대비 소모 전류 많음 |
![[Pasted image 20260424142259.png]]

#### ARM 프로세서 종류
| 프로세서 종류                       | 특징                            | 활용 분야                                                               |
| ----------------------------- | ----------------------------- | ------------------------------------------------------------------- |
| Cortex-A<br>(Application)     | OS 지원하는 고성능 프로세서<br>고성능, 비쌈   | 스마트폰, 멀티미디어 디바이스, 클라우드 서버 등                                         |
| Cortex-R<br>(realtime)        | 높은 성능<br>real-time App에 주로 사용 | 실시간 처리 특화 로봇 및 항공 시스템 분야                                            |
| Cortex-M<br>(microcontroller) | 가성비 우수한 MCU<br>낮은 전력 소모와 저렴함  | IoT 기기, 전원 관리, <br>임베디드 오디오, <br>산업 및 가정 자동화, <br>의료 및 웰빙 어플리케이션 분야 |
#### ARM Coretex-M4
![[Pasted image 20260424143729.png]]
```asm
.arm // arm으로 시작
.text // 텍스트 코딩 시작(.end까지)
//명령어 순차 실행
.global main // program의 entry point
.type main, %function // main의 type def

main: // main문 시작

	BX lr //함수 종료 후 return(link register -> return func addr 들어가 있음)

.end//끝
```
![[Pasted image 20260424151604.png]]

#### Branch Instructions
* 특정한 시작 주소를 가리킴
![[Pasted image 20260424152602.png]]
-> 조건 없이 jump 실행
=> 조건에 대한 형태는 앞에 사용한 조건들 사용
```asm title="func_call"
.arm // arm으로 시작
.text // 텍스트 코딩 시작(.end까지)
//명령어 순차 실행
.global main // program의 entry point
.type main, %function // main의 type def

main: // main문 시작
	
	bl factorial
	bx lr //함수 종료 후 return(link register -> return func addr 들어가 있음)

.global factorial
.type factorial, %function
factorial:
	
.end//끝
```
![[Pasted image 20260424154454.png]]
-> jump(Go to) 만남
![[Pasted image 20260424154508.png]]
-> func factorial 실행
![[Pasted image 20260424154521.png]]
-> return
![[Pasted image 20260424154532.png]]
-> main 복귀
```asm
.global _start
.text
_start:
    MOV R0, 
    MOV R1,

loop:
    CMP R0, #101
    BEQ end_program

    CMP R1, #3
    BEQ multiple_of_3

    ADD R0, R0, #1
    ADD R1, R1, #1

    B loop

multiple_of_3:
    

end_program:
    BX LR

.end
```
```asm
.global _start
.text
_start:
    MOV R0, #1

loop_numbers:
    CMP R0, #101
    BEQ end_program

    MOV R1, R0

check_multiple:
    CMP R1, #3
    BLT not_multiple
    SUB R1, R1, #3
    B check_multiple

is_multiple:
    @led output
    B next_number

not_multiple:
    CMP R1, #0
    BEQ is_multiple

next_number:
    ADD R0, R0, #1
    B loop_numbers

end_program:
    BX LR

.end
```