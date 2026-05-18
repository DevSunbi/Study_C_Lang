#### 현업 얘기
* 빌드된 결과를 Embed 장비에, 빌드 자체는 개발 환경에서 진행
* 왜 우분투를 깔았냐? -> 개발 환경 구현 연습 중임
* 크로스 플랫폼 환경에서 학습을 진행
* gcc/g++ 컴파일러는 상용 컴파일러에 뒤쳐지지 않는 성능 존재
## GCC
* gcc 특징
	* gnu에서 만든 C 컴파일러
		* /usr/bin/gcc is not compiler
	* 많은 CPU 아키텍처 지원
		* ARM, I386, PPC, SPARC...
	* 타 언어로 작성된 소스도 컴파일 가능(Cpp, fortran, Java...)
	* Objective C -> Apple쪽에서 자주 사용 -> apple 쪽 컴파일도 가능
	* 전처리기, C 컴파일러, 어셈블러, 링커 호출 역할 담당
![[Pasted image 20260512095233.png]]
* \#로 시작하는 명령어 구문을 전처리 수행, 전처리 완료된 소스 파일 .i 생성
* .i의 정의된/조건부 컴파일 소스파일을 입력으로 받아 어셈블리 코드 파일 생성
* 어셈블러를 통해 기계어로 번역 -> 목적파일 생성
* 목적파일을 통해 ld/collect2(linker)가 실행파일 생성
![[Pasted image 20260512095606.png|550]]
![[Pasted image 20260512095623.png|547]]![[Pasted image 20260512095646.png]]

#### GCC 전처리 과정
* cpp0 -> 전처리 명령어
	* 전처리 수행 과정
	1. 헤더 파일의 삽입
	2. 매크로 치환 및 적용
![[Pasted image 20260512095730.png|413]]
<include 과정>
1. 소스파일 읽음
2. include를 만나면 include 디렉토리에서 헤더 파일 찾음
3. 찾는 순서 : /usr/local/include => /usr/lib/gcc/\*-linux/ gcc버전/include => /usr/include

<매크로 치환 과정>
1. define 부분 cc1 심볼 테이블에 저장
2. 심볼 테이블에 들어 있는 문자열과 같은 문자열을 만나게 되면 치환

* cc1에 의한 컴파일 과정
	* 어휘 분석 -> 구문 분석 -> 의미 분석 -> 중간 언어 생성 -> 최적화 -> 목적 코드 생성
	* 최적화 => 공통 부분식 제거 혹은 사용되지 않는 코드 삭제, 루프 최적화를 통해 필요 없는 부분 제거/병합
		* 고민이 필요함 
			* 임베디드에서는 Memory Map 방식 사용함
			* 실 메모리 주소는 device driver에서 사용
			* volatile -> 최적화에서 제외되는 변수
				* 하드웨어 레지스터 제어, ISR, 멀티스레드 환경 등
* 어휘 분석
	* 전처리 결과 파일 읽음
	* 문법적으로 의미 있는 가장 최소 단위(토큰)로 나눔

| 종류    | 예                                   |
| ----- | ----------------------------------- |
| 지정어   | if, while, for, do, switch, case... |
| 연산 기호 | +, -, \*, /, %, <...                |
| 구분자   | (, \[, , ;...                       |
| 명칭    | main, printf...                     |
| 상수    | 123, 123.1, 0x123, "bit\n"...       |

#### GCC 컴파일 과정
* 최적화
	* 기능은 같지만 크기가 작고, 빠르며, 메모리를 작게 사용하는 코드로 변경하는 것을 의미
	* gcc는 컴파일 시간의 대부분을 최적화 과장을 위해 사용(소스의 대부분도 최적화를 위한 코드)
	* -O0 - -O3 옵션을 통해 최적화 수위 조절
		* 보편적으로는 2레벨 사용, 고수위 최적화 진행 시 코드 왜곡 가능성 존재
* 최적화 과정
	1. 중간코드 최적화
		* 지역 최적화 : 상수 계산 최적화 등
		* 전역 최적화 : 공통 부분식 제거 및 사용되지 않는 코드 제거
		* 루프 최적화 : 루프가 필요 없는 부분은 루프를 제거 또는 합침
	2. 목적 코드 최적화
		* 레지스터 사용 최적화
		* 메모리 접근에 대한 최적화
* 기계어 코드 생성
	* as에 의해 기계어로 어셈블
		* as -V -Qy -o source.o source.s
	* as에 의해 생성되는 .o 파일은 어셈블된 .s의 인스트럭션과 데이터가 들어있는 ELF(Executable and Linking Format) 바이너리 포맷 구조를 가짐
![[Pasted image 20260512102354.png|190]]
* ELF 헤더 정보
![[Pasted image 20260512102413.png]]
* obj, executable 파일 열 땐 readelf 명령을 통해 포맷이 맞춰졌는지 확인 가능
* 심볼 테이블
![[Pasted image 20260512102819.png]]
#### GCC 링킹 과정
* collect2에 의한 링킹 과정
	* ELF 포맷의 바이너리 파일 생성 후 링커에 의한 표준 C 라이브러리와 링크하게 됨
![[Pasted image 20260512102905.png]]
공유 라이브러리
- 실행 파일 안에 라이브러리 코드가 직접 포함되지 않는다.
- 실행 파일에는 필요한 공유 라이브러리 이름, 심볼, 재배치 정보 등이 들어간다.
- 실행 시 동적 링커가 .so 파일을 메모리에 매핑하고 필요한 심볼을 연결한다.
- 여러 프로세스가 같은 .so의 읽기 전용 코드 영역을 물리 메모리에서 공유할 수 있다.

정적 라이브러리
- .a 파일은 여러 .o 파일을 묶어둔 archive이다.
- 링크 시 필요한 object code가 실행 파일 안에 복사된다.
- 실행 시에는 정적 라이브러리 파일을 별도로 참조하지 않는다.
- 동일한 정적 라이브러리를 사용한 여러 실행 파일은 각자 코드 사본을 포함하므로 디스크/메모리 사용량이 증가할 수 있다.
#### GCC 옵션
* -E
	* 전처리 과정의 결과를 화면에 보이는 옵션
* -S
	* cc1으로 전처리된 파일을 어셈블리 파일로 컴파일까지만 수행
	* .s 파일 생성
* -c
	* as에 의한 어셈블까지만 수행, 링크는 수행 하지 않음
	* .o 파일 생성
* -v
	* gcc가 컴파일을 어떤 식으로 수행하는지를 화면에 출력해서 보임
* --save-temps
	* 컴파일 과정에서 생성되는 중간 파일인 전처리 파일, 어셈블리 파일, 오브젝트 파일을 현재 디렉토리에 저장, 컴파일 과정에서 발견되는 오류 분석 시 이용
* -I
	* 전처리 과정에서 헤더 파일을 탐색하는 기본 디렉토리를 추가할 때 사용(위치 명시)
* -include
	* 헤더 파일을 소스 내에 추가할 때 사용
* -D
	* 매크로를 외부에서 define 할 때 사용
* -U
	* -D와 반대로 소스파일 내에 #undefine 옵션을 추가한 것과 동일
* 경고 옵션
	* Wall 옵션은 모든 모호한 문법에 대한 경고 메시지 출력
	* W는 합법적이지만 모호한 코딩에 대해 부가적인 정보 출력
* 최적화 옵션
	* O0
		* 최적화 수행 안함
	* O1
		* 최소 단위 최적화
	* O2
		* 가장 많이 사용 옵션, 일반 응용이나 커널을 컴파일 할 때 사용, 거의 대부분의 최적화 수행
	* O3
		* 가장 높은 레벨의 최적화로 모든 함수를 인라인 함수와 같이 취급
		* call instruction을 사용하지 않고 호출
		* 왜곡 발생 위험 존재
	* Os
		* 사이즈 최적화 수행
* 디버깅 옵션
	* -g
		* gdb에게 제공하는 정보 바이너리에 삽입
		* O와 같이 레벨 지정 가능
	* -pg
		* 프로파일을 위한 코드 삽입(프로그램 실행 추적)
		* gprof에 의해 실행 파일의 내용 분석, 함수 호출 횟수나 수행 시간 분석 수행
```zsh
sunbi@DESKTOP-CEO27QH ~/gcc master* 5s                                                               10:55:36
❯ gcc hello.c -o hello -I/home/sunbi/inc

sunbi@DESKTOP-CEO27QH ~/gcc master*                                                                  10:55:44
❯ ./hello
hello ubuntu:
hi define%                                     
```

![[Pasted image 20260512112647.png]]
-> 불필요한(실행 안될 것 같은) 코드 제거 결과 확인 가능(O0, O2)

```zsh
sunbi@DESKTOP-CEO27QH ~/gcc master*                                                                  11:24:05
❯ cat test.c
#include <stdio.h>

int main()
{
        int a, b=0;
        scanf("%d", &a);
        if(a>0&&a<0)
                b=10;

        return 0;
}


```
![[Pasted image 20260512113524.png]]
```zsh
sunbi@DESKTOP-CEO27QH ~/gcc master* 44s                                                              11:32:38
❯  cat volatile.c
#include <stdio.h>

int main()
{
        int num1=0;
        volatile int num2=0;

        while(num1<16)
                num1++;
        while(num2<16)
                num2++;

        return 0;
}

```

#### 라이브러리?
* 라이브러리란
	* 함수의 집합
	* 라이브러리의 분류는 시스템에서 미리 제공되는 라이브러리와 사용자가 정의한 라이브러리로 분류 가능
		* 정적 라이브러리
		* 공유 라이브러리
		* 동적 라이브러리
	* 정적 라이브러리
		* 오브젝트 파일을 모아놓은 것, .a 확장자 사용
		* 오브젝트 집합은 ar(archiver) 프로그램에 의해 생성
		* 재컴파일 없이 프로그램에 링크 가능, 재컴파일에 필요한 시간 절약 가능
		* 컴파일 시 실행 파일에 적재 -> 유연성 낮음
		* 작성 절차
			1. 선언될 header 파일 생성
			2. 함수 구현될 파일 생성
			3. 함수 구현된 파일 컴파일(obj 파일까지만)
			4. ar 명령어를 이용, 정적 라이브러리 파일 생성
			5. 작성된 라이브러리 파일을 사용하는 예제 파일 작성
			6. 예제 파일에 적용
			7. 실행
	* 공유 라이브러리
		* 실행 시 로딩되는 라이브러리
		* 최초 실행 시 메모리에 로딩된 후 타 응용프로그램에 의해 사용될 때 이미 메모리에 로딩된 라이브러리가 사용
		* 기존 응용 프로그램에 추가되는 것이 아닌 실행 시 링크됨
		* ![[Pasted image 20260512122857.png]]
		* ![[Pasted image 20260512123138.png]]
```zsh
sunbi@DESKTOP-CEO27QH ~/gcc/lib/shared master*                                                       12:33:33
❯ ldd ./main
        linux-vdso.so.1 (0x00007fffb1b7a000)
        libcalc.so (0x00007a5b2f34c000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007a5b2f000000)
        /lib64/ld-linux-x86-64.so.2 (0x00007a5b2f358000)

```
* 공유 라이브러리 사용 현황 확인

	* 동적 라이브러리
		* 프로그램 시작할 때가 아닌 실행 중에 로딩되는 라이브러리
		* 플러그인이나 모듈을 구현 시 적합
		* 필요할 때 까지 로딩을 기다릴 수 있음
		* 코드를 머신 코드로 바꾸고 효율을 위해 멈추지 않고 컴파일된 코드로 만드는 인터프리터 구현 시 유용
		* 실시간 컴파일러나 MUD(Multi User Dungeon)을 구현시 유용
		* dlopen() func
			* 동적 라이브러리 로딩, 사용 가능하도록 준비시켜줌
			* 바인딩 시점 결정
			* 실패 null, 성공 시 handle
		* dlerror() func
			* 마지막 호출 에러의 무자열 반환
		* dlsym() func
			* 함수명에 대한 함수 주소 리턴
			* open 성공 시 받은 handle을 인자로 symbol을 통해 함수 주소 받아옴
			* symbol 없으면 null 반환
		* dlclose() func
			* 열었으니 닫자
## GNU DEBUGGER
#### GDB
* 다양한 아키텍처와 CPU를 위한 낮은 수준의 종속적인 디버깅까지도 지원
* 임베디드 리눅스 개발 환경에서는 교차-디버거로 컴파일된 GDB 이용
* 디버거 자체는 개발 호스트 시스템에서 실행, 디버거는 컴파일 시점에서 주어진 아키텍처를 위한 바이너리 실행 파일을 인식하도록 되어 있는 것을 의미
#### 디버깅
* 프로그램의 논리적인 오류를 찾아내는 과정
* 프로그램 수행 중에 내부적인 동작 파악
* 프로그램 수행 중 오류 발생으로 중단된 원인 파악
#### GDB 사용
* gdb 명령으로 시작
	* gdv ex-prog core-dump
	* 실행 파일 ex-prog를 디버깅
	* 프로그램 오류에 의해 중단된 프로세스의 덤프 파일 core-dump를 디버깅
* options
	* -d dir : 소스 파일이 있는 디렉 지정
	* -x file : gbd 시작 후 file에 있는 gdb 명령어 우선 실행
	* -c number : 실행 중인 프로세스의 pid가 number인 프로세스 디버깅
	* -batch : -x file로 지정된 gdb 명령 수행 후 gdb 종료
#### GDB 명령어 : 파일 내용 출력
* list 명령어는 실행하고 있는 부분의 소스 출력
	* (gdb) list
		* 프로그램 실행 전에는 main 함수의 내용 보여줌
		* 특정 부분 보려면 소스 프로그램의 줄 번호 입력 -> (gdb) list 90
		* 특정 함수의 소스 코드를 보려면 함수 이름 입력
	* ![[Pasted image 20260512143103.png]]
#### GDB 명령어 : 프로그램 수행
* run 명령어 : 디버그 할 프로그램 수행
	* 프로그램에 전달 할 인자 지정 가능
	* run -b \<invalues> outtable
	* 다음 run 명령어에서 인자를 주지 않으면 이전의 인자 그대로 사용
* set arg 명령을 사용해 인자를 바꾸거나 설정 가능
	* set args -b \<invalues> outtable
		* show args로 설정된 인자 알아 볼 수 있음
		* show args
* break 명령어로 프로그램 정지 지점 설정
	* break line-num
		* 소스 특정 위치 주어진 줄, line-num에 오면 프로그램 정지
	* break func-name
		* 소스의 특정 함수, func-name에 오면 프로그램 중지
	* break line-or-func if condition
		* 특정 위치에서 조건, condition을 만족하면 프로그램 정지
* watch 명령어로 특정 조건을 만족하면 프로그램 정지
	* watch condition
		* 프로그램 느려짐
		* watch를 사용해 프로그램 오류 대략적인 위치 파악, break를 이용해 정확한 위치 추적
#### GDB 명령어 : 프로그램 상태 파악
* 고급 print 명령어
	* 함수의 결과 값도 함수를 호출해 알아 볼 수 있음
		* print function(args, ...) -> 전역 변수 변경 가능성 존재
	* @을 사용해 배열의 길이 지정 가능
		* print \*p@10
	* /x, u, o, c, etc를 사용해 출력 형태 지정 가능
		* print /x var-x
#### 정지점 관리
* 여러 개의 정지점 설정 가능
* info breakpoints를 사용해 정지점 알아 볼 수 있음
* delete break-number 명령을 사용해 정지점 제거 가능, 인자 없으면 전부 삭제
* disable, enable을 사용해 정지점 잠시 유효 및 무효화 가능
* continue 사용해 프로그램 계속 수행 가능
* step을 사용해 한 줄 씩 수행 가능 -> 함수 만나면 함수로 들어가 한 줄 수행
* next를 사용해 한 줄씩 수행 가능 -> 함수도 한 줄로 인식, 함수 안으로 안들어감
* finish를 사용해 현재 실행 중인 함수의 끝까지 실행하고 멈춤
* return value는 현재 실행 중인 함수 취소, value를 리턴 값으로 사용
#### 명령어 자동 실행
* command 명령어를 사용, 정지 시 자동으로 실행하는 명령어 설정
	* command break-number
		* ...list-of-commnad
		* ..list-of-command
		* End
* display 명령어 사용해 프로그램 멈출 때 마다 변수 값 출력
	* display variable
#### 시그널 설정
* handle 명령어 사용, 디버깅 프로그램에 보내는 시그널 제어
	* handle signal action-list
* signal은 SIGINT와 같은 시스템에서 정한 시그널
* Action-list는 다음과 같은 의미 지님
	* nostop : 시그널 받았을 때 프로그램에 넘겨주지 않고 정지 시키지도 않음
	* stop : 시그널 받았을 때 프로그램을 정지, 디버그 모드로 전환
	* print : 시그널 받았을 때 메시지 출력
	* pass : 프로그램에 시그널 넘겨 줌
	* nopass : 프로그램에 시그널을 넘겨주지 않음
		* handle SIGINT stop print
* signal 명령을 통해 프로그램에 시그널 발생
	* signal 2
#### 명령어 정리
| 명령어 | 설명 |
|---|---|
| `list` | 현재 위치에서 소스 파일의 내용을 10줄 보여준다.<br>`list 2, 15` : 소스 파일의 2~15번째 줄을 보여준다. |
| `run` | 프로그램을 시작한다. 브레이크포인트가 있다면 브레이크포인트까지 실행한다.<br>`run arg` : 새 프로그램을 가지고 프로그램을 시작한다.<br>`arg`는 `*`, `>` 같은 문자를 포함할 수도 있다.<br>쉘의 사용자, 프로그램 확장자를 사용할 수 있다.<br>`<`, `>`, `>>` 같은 입출력 방향 재지정 기능도 허용된다. |
| `break` | 특정 라인이나 함수에 정지점을 설정한다.<br>`break function` : 현재 파일 안의 함수 `function`에 정지점을 설정한다.<br>`break file:function` : 파일 `file` 안의 함수 `function`에 정지점을 설정한다.<br>`watch` : 감시점 설정. 감시점은 어떤 사건이 일어날 때마다 작동한다.<br>`until` : 실행 중 line까지 실행. |
| `clear` | 특정 라인이나 함수에 있던 정지점을 삭제한다. |
| `delete` | 몇몇 정지점이나 자동으로 출력되는 표현을 삭제한다. |
| `next` | 다음 행을 수행한다. 서브루틴을 호출하면서 계속 수행한다.<br>호출이 발생하지 않으면 `step`과 같다.<br>`next n` : 이를 `n`번 수행한다는 의미이다. |
| `step` | 한 줄씩 실행시킨다.<br>함수를 포함하고 있으면 함수 내부로 들어가서 한 줄씩 실행시킨다. |
| `print` | `print expr` : 수식의 값을 보여준다. |
| `display` | 현재 display된 명령의 목록을 보여준다. |
| `bt` | 프로그램 스택을 보여준다. `backtrace`의 약어이다. |
| `kill` | 디버깅 중인 프로그램의 실행을 취소한다. |
| `file` | `file program` : 디버깅할 프로그램으로 파일을 사용한다. |
| `cont` | `continue` : 현재 위치에서 프로그램을 계속 실행한다. |
| `help` | 명령에 관한 정보를 보여주거나 일반적인 정보를 보여준다. |
| `quit` | GDB에서 빠져나간다. |
## CORE 파일 분석
* 예기치 못한 일이 발생해 비정상적인 종료가 발생할 때 OS는 디스크에 core file 남김
* 프로세스의 메모리 이미지를 dump한 것
* core file을 gdb와 함께 사용하여 프로그램의 상태를 조사하고 실패 원인 규명 가능
* 메모리에 관한 문제는 checker 패키지 사용해 예방 가능
* 메모리 fault를 일으키는 경우네는 메모리가 충돌하면서 파일 dump
* core file은 일반적으로 프로세스를 실행시킨 현재 작업 디렉터리에 생성되지만 프로그램 내에서 작업 디렉터리를 바꾸는 경우 있음
* 일반적으로 linux는 부팅 시에 core file을 만들지 않도록 설정되어 있음
* core file 생성을 가능케 하려고 한다면 그것을 기능하게 하는 내장 명령 사용
	* ulimit -c unlimited
* gdb에서 코어 파일을 이용한 디버깅
	* 실행파일명 core파일명

#### proc
![[Pasted image 20260512152841.png]]
* 커널 관련 정보들
![[Pasted image 20260512152900.png]]
* 커널 파라미터
![[Pasted image 20260512152925.png]]
* kernel 내부 파라미터들
```zsh
root@DESKTOP-CEO27QH:/proc/sys/kernel# cat core_pattern
|/wsl-capture-crash %t %E %p %s
```
-> 매개변수로 커널의 메모리
```zsh
sunbi@DESKTOP-CEO27QH ~ master*                                                                      15:31:30
❯ sleep 60
^\[1]    119042 quit (core dumped)  sleep 60

sunbi@DESKTOP-CEO27QH ~ master*                                                                      15:31:36
❯ ls
core.119042  dont_exec.sh  end_op.sh  gcc  hello.txt  inc  mydata  outputfile  shellscript  snap

sunbi@DESKTOP-CEO27QH ~ master*                                                                      15:31:37
❯ ls -l core.119042
-rw------- 1 sunbi sunbi 438272 May 12 15:31 core.119042

sunbi@DESKTOP-CEO27QH ~ master*                                                                      15:32:28
❯ ls -l /bin/sleep
-rwxr-xr-x 1 root root 35336 Jan 23 19:51 /bin/sleep

```
* 무겁다
* core 파일이 실행 파일보다 더 무거움
```zsh
❯ gdb /bin/sleep ./core.119042
Core was generated by `sleep 60'.
Program terminated with signal SIGQUIT, Quit.
```
* core 파일 gdb 디버그 일부 내용 
* 생성 객체, terminated 사유 기재 확인 가능

```gdb
❯ gdb ./array_overflow ./core.121135
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./array_overflow...
[New LWP 121135]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Core was generated by `./array_overflow'.
Program terminated with signal SIGABRT, Aborted.
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=131233785395008) at ./nptl/pthread_kill.c:44
44      ./nptl/pthread_kill.c: No such file or directory.

(gdb) bt
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=131233785395008) at ./nptl/pthread_kill.c:44
#1  __pthread_kill_internal (signo=6, threadid=131233785395008) at ./nptl/pthread_kill.c:78
#2  __GI___pthread_kill (threadid=131233785395008, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
#3  0x0000775b3f042476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#4  0x0000775b3f0287f3 in __GI_abort () at ./stdlib/abort.c:79
#5  0x0000775b3f089677 in __libc_message (action=action@entry=do_abort,
    fmt=fmt@entry=0x775b3f1db92e "*** %s ***: terminated\n") at ../sysdeps/posix/libc_fatal.c:156
#6  0x0000775b3f13661a in __GI___fortify_fail (msg=msg@entry=0x775b3f1db916 "stack smashing detected")
    at ./debug/fortify_fail.c:26
#7  0x0000775b3f1365e6 in __stack_chk_fail () at ./debug/stack_chk_fail.c:24
#8  0x000055d6d661628f in main () at array_overflow.c:34
```

* 오류 발생 지점의 변수 확인
```gdb
(gdb) frame 8
#8  0x000055d6d661628f in main () at array_overflow.c:34
34      }
(gdb) info locals
data = {0, 10, 20, 30, 40}
i = 5
```

#### 실습 - 강사 코드
```zsh
(gdb) b AddArray
Breakpoint 1 at 0x5ef11d5003b2: file dynamicArray.c, line 30.
(gdb) r
Starting program: /home/sunbi/gdb/work/main
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, AddArray (lpArray=0x0, value=1) at dynamicArray.c:30
30              if(lpArray->size==lpArray->max_size) {          // Full?
(gdb) s

Program received signal SIGSEGV, Segmentation fault.
0x00005555555553b6 in AddArray (lpArray=0x0, value=1) at dynamicArray.c:30
30              if(lpArray->size==lpArray->max_size) {          // Full?
(gdb) s

Program terminated with signal SIGSEGV, Segmentation fault.
The program no longer exists.
```
* seg fault 발생 지점 확인 가능
```text
createArray에서 동적 할당한 temp 주소를 main의 lpArray에 전달하지 못함
→ main의 lpArray가 NULL 상태로 유지됨
→ AddArray(NULL, 1) 호출
→ lpArray->size 접근
→ SIGSEGV
```
![[Pasted image 20260512161609.png]]

```gdb
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=125238481471296) at ./nptl/pthread_kill.c:44
44      ./nptl/pthread_kill.c: No such file or directory.
(gdb) bt
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=125238481471296) at ./nptl/pthread_kill.c:44
#1  __pthread_kill_internal (signo=6, threadid=125238481471296) at ./nptl/pthread_kill.c:78
#2  __GI___pthread_kill (threadid=125238481471296, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
#3  0x000071e75b042476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#4  0x000071e75b0287f3 in __GI_abort () at ./stdlib/abort.c:79
#5  0x000071e75b089677 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0x71e75b1dbb77 "%s\n")
    at ../sysdeps/posix/libc_fatal.c:156
#6  0x000071e75b0a0cfc in malloc_printerr (str=str@entry=0x71e75b1d983e "realloc(): invalid next size")
    at ./malloc/malloc.c:5666
#7  0x000071e75b0a4c7c in _int_realloc (av=av@entry=0x71e75b21ac80 <main_arena>,
    oldp=oldp@entry=0x5a31f41172b0, oldsize=oldsize@entry=48, nb=nb@entry=48) at ./malloc/malloc.c:4842
#8  0x000071e75b0a5909 in __GI___libc_realloc (oldmem=0x5a31f41172c0, bytes=40) at ./malloc/malloc.c:3485
#9  0x00005a31befbf3e4 in AddArray (lpArray=0x5a31f41172a0, value=21) at dynamicArray.c:31
#10 0x00005a31befbf287 in main () at main.c:19

```
```zsh
==147055==
==147055== HEAP SUMMARY:
==147055==     in use at exit: 0 bytes in 0 blocks
==147055==   total heap usage: 6 allocs, 6 frees, 1,640 bytes allocated
==147055==
==147055== All heap blocks were freed -- no leaks are possible
==147055==
==147055== For lists of detected and suppressed errors, rerun with: -s
==147055== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
-> valgrind 사용하면 memory leak 문제 확인 가능함
