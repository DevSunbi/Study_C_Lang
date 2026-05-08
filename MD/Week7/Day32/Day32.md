## 시스템 관리
#### 패키지 관리 시스템
* 패키지 : 소프트웨어 프로그램과 관련 파일들을 포함한 묶음
* 패키지 관리 시스템(PMS, Package Management System)
	* 패키지의 설치, 업데이트, 구성, 제거르 자동화하고 관리하는 시스템
![[Pasted image 20260508091045.png|345]]
* apt(Advanced Package Tool)
	* 데비안, 우분투 계열의 리눅스 배포판에 탑재된 패키지 관리 시스템
		* $apt install
		* $apt remove -> 단일 패키지 삭제
		* $apt autoremove -> 대상 패키지 삭제 후 불필요 패키지 함께 삭제
		* $apt list
* awk
	* 파일로부터 레코드 선택, 선택된 레코드에 포함된 값을 조작하거나 데이터화
	* 지정된 파일로부터 데이터 분류, 분류된 텍스트 데이터를 바탕으로 패턴 매칭 여부 검색 또는 데이터 조작 및 연산 등의 액션, 결과 출력 기능
	* $awk \[option] \[awk program] \[args]
	* -F : 필드 구분 문자 지정
	* -f : awk program 파일 경로 지정
	* -v : awk program에서 사용될 특정 variable 값 지정
#### systemd
* 데몬 프로세스 : 백그라운드에서 실행하는 특정 기능을 하는 프로세스
* 유닛 파일 : 서비스에 필요한 설정, 실행 방법, 실행 시점, 다른 서비스와의 의존성, 실패 시 재시작 벙법 등을 정의해 하나의 서비스를 구성
* Service 섹션 -> 서비스의 작동 방법 정의, 어떻게 시작돼야 하는지 어떤 환경변수 쓰는지 실행 명령어 등
	* 서비스 유형 정의 -> Type : simple, forking, oneshot, dbus, notify, idle 등
	* ExecStart -> 서비스 시작 시 실행 명령어 지정, 지정된 명령은 서비스의 실행 파일을 가리킴 => 필수 항목
	* ExecStartPre / ExecStartPost : 서비스 시작 전 후에 실행할 명령어 각각 지정
	* ExecStop : 서비스 중지 시 실행 할 명령어 지정 -> 안전한 종료를 위해 필요한 경우 사용
	* ReStart : 서비스 실패 시 재시작 여부 결정
		* always, on-success, on-failure, on-abnormal, on-watching, on-abort, never 등
	* RestartSec : 재시작 간격 -> 서비스 실패 후 재시작 전까지 대기 시간 초 단위 설정 
	* Environment : 서비스 실행 시 사용할 환경 변수
	* WorkingDirectory : 작업 디렉 설정
* Install 섹션 : 현 서비스가 어떤 대상에 필요한지를 나타내며 주로 타깃 유닛 설정
	* grahical.target -> GUI
	* multu-user.target -> default, GUI 제외
	* rescue.target -> 복구모드로 시스템 시작, 시스템 문제 해결 시 사용
	
```bash
/etc/systemd/system 10m 45s                                                                                           10:40:27
❯ cat myservice.service
[Unit] #어느 서비스 뒤에, 전에 등을 규정 -> after, before 사용됨 => dependency 없음
#설명
Description=My Test Service

#어떤 쉘 프로그램을 service로 등록해서 실행할지
#서비스의 작동 방법 정의, 어떻게 시작돼야 하는지, 환경변수, 실행 명령어 등
[Service]
Type=simple
ExecStart=/tmp/myservice.sh

#대상 지정
[Install]
WantedBy=multi-user.target
```
#### systemctl
* 서비스 목록, 시작, 중지, 재시작, 등 여러 서비스 제공
* 주 디렉터리
	* /etc/systemd/system 
```bash
~ master*                                                                                                             10:48:00
❯ sudo systemctl start myservice

~ master*                                                                                                             10:48:08
❯ sudo systemctl status myservice
● myservice.service - My Test Service
     Loaded: loaded (/etc/systemd/system/myservice.service; enabled; vendor preset: enabled)
     Active: active (running) since Fri 2026-05-08 10:48:08 KST; 7s ago
   Main PID: 5527 (myservice.sh)
      Tasks: 2 (limit: 9035)
     Memory: 856.0K
        CPU: 7ms
     CGroup: /system.slice/myservice.service
             ├─5527 /bin/bash /tmp/myservice.sh
             └─5530 sleep 10

May 08 10:48:08 DESKTOP-CEO27QH systemd[1]: Started My Test Service.
May 08 10:48:08 DESKTOP-CEO27QH myservice.sh[5527]: running.....

~ master*                                                                                                             10:48:15
❯ sudo systemctl stop myservice

~ master*                                                                                                             10:48:40
❯ sudo systemctl status myservice
○ myservice.service - My Test Service
     Loaded: loaded (/etc/systemd/system/myservice.service; enabled; vendor preset: enabled)
     Active: inactive (dead) since Fri 2026-05-08 10:48:40 KST; 7s ago
    Process: 5527 ExecStart=/tmp/myservice.sh (code=killed, signal=TERM)
   Main PID: 5527 (code=killed, signal=TERM)
        CPU: 17ms

May 08 10:48:08 DESKTOP-CEO27QH systemd[1]: Started My Test Service.
May 08 10:48:08 DESKTOP-CEO27QH myservice.sh[5527]: running.....
May 08 10:48:18 DESKTOP-CEO27QH myservice.sh[5527]: running.....
May 08 10:48:28 DESKTOP-CEO27QH myservice.sh[5527]: running.....
May 08 10:48:40 DESKTOP-CEO27QH systemd[1]: Stopping My Test Service...
May 08 10:48:40 DESKTOP-CEO27QH systemd[1]: myservice.service: Deactivated successfully.
May 08 10:48:40 DESKTOP-CEO27QH systemd[1]: Stopped My Test Service.
```

```bash title="log file"
~ master*                                                                                                             10:49:04
❯ cat /tmp/myservice.log
Fri May  8 10:48:08 KST 2026
Fri May  8 10:48:18 KST 2026
Fri May  8 10:48:28 KST 2026
```
## bashrc
#### bashrc란
* Bash가 초기화 될 때 읽어들이는 셸 스크립트 파일
* source 명령어 : .bashrc 파일을 읽어들일 때 사용
	* $source file_name \[param]
* 하는 일
	1. 다른 파일을 읽어들인다
	2. 변수를 설정한다
	3. alias를 설정한다 
	4. Bash 셸 옵션을 설정한다
```bash
~/shellscript/scripts master*                                                                                         11:22:27
❯ ./test.sh
zsh: permission denied: ./test.sh

~/shellscript/scripts master*                                                                                         11:22:30
❯ source ./test.sh
-------system information------
User: sunbi
Current Direcotry: /home/sunbi/shellscript/scripts
Date: Fri May  8 11:22:34 KST 2026
OS: Linux DESKTOP-CEO27QH 6.6.87.2-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Thu Jun  5 18:30:46 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux
process count: 38
```
#### alias
* 어떤 명령에 대한 별칭 설정
* 자주 사용하는 명령을 짧은 alias로 설정해 사용하거나 어떤 명령어의 기본 옵션을 활성화하기 위해 alias 설정하기도 함
	* $alias \[set]
