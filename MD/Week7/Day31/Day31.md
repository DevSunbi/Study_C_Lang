![[Pasted image 20260507091406.png]]
-> Shell에서 for(반복문) 돌리기 => Interpreter 기반
![[Pasted image 20260507091615.png]]
=> zsh랑 bash랑 동작이 사뭇 다름
![[Pasted image 20260507091734.png]]
* test.sh의 내용으로, 외부 선언한 변수는 반영이 안됨을 알 수 있음
* export를 통한 정의로 반영 가능
![[Pasted image 20260507091857.png]]
* 이중 괄호 -> 산술형태 연산 지원하게 하는 format
```bash
➜  scripts git:(master) ✗ ./roottest.sh
loop index: 0
loop index: 1
loop index: 2
loop index: 3
loop index: 4
➜  scripts git:(master) ✗ cat roottest.sh
#!/bin/bash

for ((i=0;i<5;i++))
do
        echo "loop index: $i"
done
```
* (()) 산술 연산에 해당, ((expression))은 산술 평가 명령어로 $((expression))과는 다름
* $((expression))은 산술식을 계산한 결과값으로 치환한다
* ((expression))은 계산 결과가 0이 아니면 참, 0이면 거짓으로 non-zero면 반환 상태가 0, 즉 성공/참, 0이면 반환상태가 1이라 설명함
* 따라서 ((expression))을 통한 C스타일 연산이 가능하다
```zsh
➜  scripts git:(master) ✗ cat roottest.sh
#!/bin/bash

for ((i=0;i<5;i++)) #산술 평가 명령
do
        echo "loop index: $i"
done

for n in $(seq 1 2 10) # seq(시작값 증가값 종료값)
do
        echo "ranged: $n"
done
```
* seq를 사용해 반복문 구성 가능
```bash
~/shellscript/scripts master* 1m 3s                                                                                   09:55:06
❯ cat doubleloop.sh
#!/bin/bash

for i in $(seq 2 1 9) # for ((base=2;base<=9;base++))
do
        for j in $(seq 1 1 9) # for((mult=1;mult<=0;mult++))
        do
                #"$i * $j = $(expr $i \* $j)" expr을 사용한 old style 범용성 높은 표현
                # for mult in {1..9..1} 또한 가능
                echo "$i x $j = $((i*j))"
        done
done

i=2
while [ "$i" -le 9 ]
do
        j=1
        while [ "$j" -le 9 ]
        do
                printf '%d x %d = %d\n' "$i" "$j" "$((i*j))"
                j=$((j+1))
        done
        printf '\n'
        i=$((i+1))
done
```
* 상위 구현부는 shell script의 기본형
* 하위 구현부는 BusyBox 환경 기준 임베디드 리눅스 반영 외부 명령어 의존도 낮춘 버전
* 임베디드 리눅스 기준으로는 /bin/sh의 POSIX 스타일
* BusyBox ash에서도 도는 문법으로 작성

* function은 ()안에 param을 정의하기보단, $0, $1 등을 이용해 param을 받는 것이 더욱 유용함
```zsh
~/shellscript/scripts master*                                                                                         10:18:31
❯ cat func_test.sh
#!/bin/bash

function make_a_pizza()
{
        echo "in fuction num of args: $#"
        echo "command: $0"
        echo "1st arg: $1"
}

echo "first function example"
make_a_pizza "first args"

~/shellscript/scripts master*                                                                                         10:18:34
❯ ./func_test.sh
first function example
in fuction num of args: 1
command: ./func_test.sh
1st arg: first args
```

```zsh
~/shellscript/scripts master*                                                                                         10:24:58
❯ ./all_of_params.sh 1 2 3 4
total number of params: 4
$* is '1 2 3 4'
$@ is '1 2 3 4'

~/shellscript/scripts master*                                                                                         10:25:04
❯ cat all_of_params.sh
#!/bin/bash

echo "total number of params: $#"
echo "\$* is '$*'"
echo "\$@ is '$@'"

~/shellscript/scripts master*                                                                                         10:25:06
❯ ./all_of_params.sh "1 2 3 4"
total number of params: 1
$* is '1 2 3 4'
$@ is '1 2 3 4'

~/shellscript/scripts master* 1m 55s                                                                                  10:32:26
❯ ./all_of_params.sh "1 2" "3 4"
total number of params: 2
$* is '1 2 3 4'
$@ is '1 2 3 4'
$*'s param: 1 2 3 4
$@'s param: 1 2
$@'s param: 3 4
```
* $@와 $\*의 차이
	* $\*는 모든 인자를 하나의 문자열로 합침
	* $@는 각 인자를 따로 유지함
	* 임베디드 리눅스 스크립트에서 특별한 사유 없으면 $@를 기본값으로 사용
## 확장
#### 확장 -> C언어 전처리기와 유사
* 셸이 명령을 해석하고 실행하기 전에 명령에 포함된 문자열, 수, 와일드카드 패턴 등을 변환하는 과정
#### 중괄호 확장
* 중괄호를 사용해 문자열 시퀀스나 조합을 생성하는 것
```bash
sunbi@DESKTOP-CEO27QH:~$ echo hello-{cat, dog, world}
hello-{cat, dog, world}

sunbi@DESKTOP-CEO27QH:~$ echo hello-{cat,dog,world}
hello-cat hello-dog hello-world

sunbi@DESKTOP-CEO27QH:~$ echo hello-{cat,dog,world}-second
hello-cat-second hello-dog-second hello-world-second

sunbi@DESKTOP-CEO27QH:~$ echo hello-{cat,{my,your}-dog,world}-second
hello-cat-second hello-my-dog-second hello-your-dog-second hello-world-second
```
* , 기준으로 분할, 하나씩 접합
* 공백에 따른 해석의 변경 가능성 다분
	* 공백을 기준으로 명령어 나눠 해석 가능성 존재함, 공백 유의
#### 틸데 확장
* 물결표가 홈 디렉터리로 변환되는 것
```zsh
~/shellscript/scripts master*                                                                                         10:40:20
❯ echo ~
/home/sunbi

~/shellscript/scripts master*                                                                                         11:03:34
❯ echo ~mango
/home/mango

~/shellscript/scripts master*                                                                                         11:04:04
❯ echo ~+
/home/sunbi/shellscript/scripts

~/shellscript/scripts master*                                                                                         11:05:09
❯ echo ~-
/home/sunbi/shellscript
```
* 로그인한 user의 home dir이 자동적으로 나옴
* + : current dir / - : previous dir
#### 명령어 치환
* $(expression)로 둘러싸인 명령어를 실행, 그 결과를 셸의 명령이나 스크립트에서 사용할 수 있게 하는 것
```zsh
~ master*                                                                                                             11:09:22
❯ uname
Linux

~ master*                                                                                                             11:11:09
❯ echo $(uname)
Linux

~ master*                                                                                                             11:11:17
❯ echo $(uname -a)
Linux DESKTOP-CEO27QH 6.6.87.2-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Thu Jun 5 18:30:46 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux

~ master*                                                                                                             11:12:56
❯ echo "current execute process: $(ps -e | wc  -l)"
current execute process: 31

~ master*                                                                                                             11:14:46
❯ date +"%Y-%m-%d %H:%M:%S"
2026-05-07 11:15:53 #formatting
```
#### 산술 확장
* $((expression))나 이중괄호로 감싼 표현식을 산술 연산해 그 결과를 스크립트에서 사용할 수 있게 하는 것
* 정수형 변수의 산술 연산
	* declare -i로 변수 선언
```zsh
~ master* 7m 21s                                                                                                      11:33:50
❯ cat end_op.sh
#!/bin/bash

if [ $# -ne 1 ]; then
        echo "Usage:$0 number"
        exit 1
fi

a=$1
if ((a%3==0 && a%2==0)); then
        echo "$a is a multiple of 6"
else
        echo "$a is not a multiple of 6"
fi

~ master* 54s                                                                                                         11:40:44
❯ cat end_op.sh
#!/bin/bash

if [ $# -ne 1 ]; then
        echo "Usage:$0 number"
        exit 1
fi

a=$1
if [ $((a%3)) -eq 0 ]&&[ $((a%2)) -eq 0 ]; then
        echo "$a is a multiple of 6"
else
        echo "$a is not a multiple of 6"
fi
```
#### 서브스트링 확장
* 변수에 저장된 문자열의 특정 부분 추출 기능
* ${변수 : 오프셋}
* ${변수:오프셋:길이}
* ${변수\[@]:오프셋}
* ${변수\[@]:오프셋:길이}
#### 패턴 찾아 바꾸기
* 변수에 저장된 문자열에서 패턴과 일치하는 문자나 문자열을 찾으면 다른 값으로 바꾸는 기능
	1. 변수의 문자열에서 패턴과 첫 번째로 일치하는 문자나 문자열을 찾으면 지정한 문자열로 변경
		* ${변수/패턴/문자열}
	2. 변수의 문자열에서 패턴과 일치하는 모든 문자나 문자열을 지정한 문자열로 변경
		* ${변수//패턴//문자열}
	3. 변수의 문자열 시작에서 패턴과 일치하는 문자나 문자열을 찾아 지정한 문자열로 변경
		* ${변수/#패턴/문자열}
	4. 변수의 문자열 끝에서 패턴과 일치하는 문자나 문자열을 찾아 지정한 문자열로 변경
		* ${변수/%패턴/문자열}
```bash
~ master*                                                                                                             12:09:58
❯ echo $music
do re mi re do do do

~ master*                                                                                                             12:10:02
❯ echo ${music/re/Re}
do Re mi re do do do

~ master*                                                                                                             12:10:12
❯ echo ${music//re/Re}
do Re mi Re do do do

~ master*                                                                                                             12:10:51
❯ echo ${music/#re/Re}
do re mi re do do do

~ master*                                                                                                             12:11:20
❯ echo ${music/#do/Do}
Do re mi re do do do

~ master*                                                                                                             12:11:56
❯ echo ${music/%do/Do}
do re mi re do do Do
```
#### 확장
* 대소문자 바꾸기
	1. 변수에 저장된 문자열에서 패턴과 일치하는 문자를 모두 대문자로
		* ${변수^^패턴}
	2. 변수에 저장된 문자열에서 첫번째 문자열이 패턴과 일치하면 첫번째만 대문자로
		* ${변수^패턴}
	3. 변수에 저장된 문자열에서 패턴과 일치하는 문자를 모두 소문자로
		* ${변수,,패턴}
	4. 변수에 저장된 문자열에서 패턴과 일치하는 첫번째 글자를 소문자로
		* ${변수,패턴}
```bash
sunbi@DESKTOP-CEO27QH:~$ music="do re mi re do do do"
sunbi@DESKTOP-CEO27QH:~$ echo ${music^}
Do re mi re do do do
sunbi@DESKTOP-CEO27QH:~$ echo ${music^r}
do re mi re do do do
sunbi@DESKTOP-CEO27QH:~$ echo ${music^^r}
do Re mi Re do do do
sunbi@DESKTOP-CEO27QH:~$ echo ${music^d}
Do re mi re do do do
```
#### 변수 값에 따른 확장
* 빈 값일 때 지정한 값 사용
	* ${변수:-값}
* 빈 값일 때 지정한 값 할당
	* ${변수:=값}
* 빈 값일 때 에러 발생시키기
	* ${변수:?문자열}
* 빈 값이 아닐 때 지정한 값 사용하기
	* ${변수:+문자열}
```bash
❯ echo ${num:-1234}
1234

~ master*                                                                                                             12:23:00
❯ echo $num


~ master*                                                                                                             12:23:04
❯ echo ${num:=1234}
1234

~ master*                                                                                                             12:23:26
❯ echo $num
1234

~ master*                                                                                                             12:26:32
❯ unset num

~ master*                                                                                                             12:27:07
❯ echo ${num:?err}
zsh: num: err

~ master*                                                                                                             12:27:13
❯ num=111

~ master*                                                                                                             12:27:56
❯ echo ${num:+err}
err

~ master*                                                                                                             12:27:58
❯ unset num

~ master*                                                                                                             12:28:25
❯ echo ${num:+err}
```
#### 간접 확장
* 변수의 이름을 저장하는 타 변수를 통해 해당 변수의 값을 참조하는 기능
	* ${!변수명}
```bash
~ master*                                                                                                             12:30:32
❯ echo $ref_num
num

~ master*                                                                                                             12:30:47
❯ echo {!ref_num}

~ master*                                                                                                             12:31:11
❯ echo {ref_num="num"}
{ref_num=num}
```

#### 일치하는 패턴 제거
* 앞에서부터 패턴을 검색해 가장 짧게 일치하는 문자열 제거
		* ${변수#패턴}
	* 앞에서부터 패턴 검색, 가장 길게 일치하는 문자열 제거
		* ${변수##패턴}
	* 뒤에서부터 패턴 검색 가장 짧게 일치하는 문자열 제거
		* ${변수%패턴}
	* 뒤에서부터 패턴 검색 가장 길게 일치하는 문자열 제거
		* ${변수\%%패턴}	
```bash
~ master*                                                                                                             12:34:12
❯ echo ${url#/}
www.google.com/section/time/index.html

~ master*                                                                                                             12:34:57
❯ echo ${url#*/}
section/time/index.html

~ master*                                                                                                             12:35:24
❯ echo ${url##*/}
index.html

~ master*                                                                                                             12:37:14
❯ echo ${url%/}
www.google.com/section/time/index.html

~ master*                                                                                                             12:38:21
❯ echo ${url%/*}
www.google.com/section/time

~ master*                                                                                                             12:38:49
❯ echo ${url%%/*}
www.google.com
```
#### 확장 연산자
* ${변수@연산자}
	* U : 모든 문자 대문자로
	* u : 첫 문자만 대분자로
	* L : 모든 문자 소문자로
#### 셸 옵션
```bash
sunbi@DESKTOP-CEO27QH:~$ shopt -o
allexport       off
braceexpand     on
emacs           on
errexit         off
errtrace        off
functrace       off
hashall         on
histexpand      on
history         on
ignoreeof       off
interactive-comments    on
keyword         off
monitor         on
noclobber       off
noexec          off
noglob          off
nolog           off
notify          off
nounset         off
onecmd          off
physical        off
pipefail        off
posix           off
privileged      off
verbose         off
vi              off
xtrace          off
```
#### 옵션 활성화/비활성화 방법
* set 명령어로 옵션 활성화하는 방법
	* set -o option
	* set -flag
* set 명령어로 옵션 비활성화 방법
	* set +o option
	* set +flag
#### 주요 옵션
* errexit(flag e)
	* 실행한 명령이 실패하면 실행하던 셸을 즉시 중단하게 함
* pipefail
	* 파이프라인 내에서 어떤 명령이라도 실패하면 전체 파이프라인의 조욜 코드로 0이 아닌 값을 반환하게 함
## 리디렉션과 파이프라인
#### 리디렉션
* 스트림을 파일로 저장하거나 파일의 내용을 스트림으로 가져오는 것
![[Pasted image 20260507142005.png]]
#### 출력 리디렉션
* 프로세스의 출력 스트림을 파일로 출력하는 것
* 기본 형식
	* 명령 \[스트림_번호] > 파일
	* 명령 \[스트림_번호] >> 파일
![[Pasted image 20260507142118.png]]
* 한 스트림을 다른 스트림으로 리디렉션 할 때
	* 명령 \[스트림_번호]> 파일 \[n]>&\[m]
#### 입력 리디렉션
* 파일 내용을 표준 입력으로 전달

```bash
sunbi@DESKTOP-CEO27QH:~$ echo "hello"
hello
sunbi@DESKTOP-CEO27QH:~$ echo "hello" > outputfile
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
hello
sunbi@DESKTOP-CEO27QH:~$ echo "hello" 1> outputfile
sunbi@DESKTOP-CEO27QH:~$ echo "hello" 2> outputfile
hello
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
sunbi@DESKTOP-CEO27QH:~$ echo "hello" 0> outputfile
hello
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
sunbi@DESKTOP-CEO27QH:~$

sunbi@DESKTOP-CEO27QH:~$ echo "overwrite" > outputfile
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
overwrite
sunbi@DESKTOP-CEO27QH:~$ echo "overwrite" >> outputfile
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
overwrite
overwrite

sunbi@DESKTOP-CEO27QH:~$ ping -c 5 www.naber.com &> outputfile
sunbi@DESKTOP-CEO27QH:~$ cat outputfile
PING www.naber.com (77.75.253.143) 56(84) bytes of data.
64 bytes from cloud2-vm811.de-nserver.de (77.75.253.143): icmp_seq=1 ttl=38 time=290 ms
64 bytes from cloud2-vm811.de-nserver.de (77.75.253.143): icmp_seq=2 ttl=38 time=287 ms
64 bytes from cloud2-vm811.de-nserver.de (77.75.253.143): icmp_seq=3 ttl=38 time=286 ms
64 bytes from cloud2-vm811.de-nserver.de (77.75.253.143): icmp_seq=4 ttl=38 time=295 ms
64 bytes from cloud2-vm811.de-nserver.de (77.75.253.143): icmp_seq=5 ttl=38 time=287 ms

--- www.naber.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4004ms
rtt min/avg/max/mdev = 286.191/288.972/294.613/3.146 ms
```

```bash
sunbi@DESKTOP-CEO27QH:~$ wc
i love this program
      1       4      20
      
sunbi@DESKTOP-CEO27QH:~$ wc < mydata
 3  4 25
sunbi@DESKTOP-CEO27QH:~$ cat mydata
hello
testing
many lines
```
#### here documents
* 프로세스의 표준 입력으로 넣을 데이터를 셸에서 직접 입력하고 싶을 때
	* 입력할 데이터를 임시 파일에 저장 -> 입력 리디렉션 실행 -> 임시파일 삭제
* here documents 기능 : 프로세스의 입력 스트림에 연결할 내용을 파일에서 읽어오는 대신 셸에서 직접 입력하는 방법
	* 명령 \[스트림_번호] << 구분자
		* \[텍스트]
		* 구분자
* here strings
	* heredoc과 유사한 기능, 텍스트 한 줄 입력
		* 명령 \[스트림_번호] <<< 문자열
## 파이프라인
#### 파이프라인의 개념과 사용법
* 파이프라인 : 프로세스 스트림간 상호작용
* 명령1 | 명령2 \[| 명령3] ...
* 명령1 |& 명령2 \[|& 명령3]

#### 파이프라인의 프로세스 종료 코드
* 마지막에 실행된 명령의 프로세스 종료 코드 받아옴
	* cat lyrics | grep girl | wc
## 필수 커맨드라인 툴
#### grep(global regular expression print)
* 표준 입력이나 텍스트 파일에서 특정 패턴이나 문자열을 검색
	* grep \[option] 검색_패턴 \[file]
	* cat file | grep \[option] 패턴
#### find
* 파일이나 디렉터리를 검색하는 커맨드 라인 툴
	* find \[option] \[path] \[expression]
	* -L : 심볼릭 링크 대상 파일 쫓음
	* -P : 심볼릭 링크 자체에 대해 작업
#### stat
* 파일이나 파일 시스템의 상세한 상태 정보를 표시하는 커맨드라인 툴
* stat \[option] \[file]

#### wc(word count)
* 텍스트 파일의 줄 수, 단어 수, 바이트 수 등을 계산
* wc \[option] \[file]

#### df(disk free)
* 파일 시스템의 디스크 사용량을 출력하는 커맨드라인 툴
* df \[option] \[file]

#### tar(tape archive)
* 파일과 디렉터리를 아카이브하고 압축하는데 사용
* 아카이브 : 여러 파일과 디렉터리를 한 덩어리로 만드는 것
* tar \[option] \[-f archive_file] \[file]

#### read
* Bash의 내장 명령어로, 표준 입력에서 한 줄을 읽어 변수에 저장하는데 사용
* read \[option] \[value]

#### tr(translate)
* 표준 입력으로 받은 문자들을 변환, 삭제, 압축하는 커맨드 라인 툴
* tr \[option] str1 \[str2]

#### tail
* 파일 끝부분을 보임
* tail \[file]

#### head
* 파일의 시작부를 보임
* head \[file]
