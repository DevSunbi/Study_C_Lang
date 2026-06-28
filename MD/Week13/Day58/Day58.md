## Yocto(poky) 구성 요소
![[Pasted image 20260619091840.png]]
![[Pasted image 20260619091851.png]]
#### bitbake와 메타 데이터
|구분|내용|
|---|---|
|Recipes|`.bb` 로 끝나는 파일소스코드 사본이나 다른 컴포넌트의 의존성 파일을 얻는 방법, 빌드 및 설치 방법을 포함 소프트웨어 빌드에 대한 정보로 구성파이썬과 셸 프로그램으로 이루어진 태스크들의 모음|
|Append|`.bbapend`로 끝나는 파일레시피의 세부 항목을 덮어 씌우거나 확장|
|Include|`.inc` 로 끝나는 파일여러 레시피를 위한 공통된 정보 포함, Include 또는 require 키워드를 이용하여 포함|
|Classes|`.bbclass` 로 끝나는 파일공통 빌드 정보 포함, inherit 키워드를 이용하여 상속됨|
|Configuration|`.conf` 로 끝나는 파일프로젝트 빌드 프로세스를 통제하는 구성 변수로 이루어짐|
![[Pasted image 20260619092943.png]]
* meta dir 아래서 레시피 수정 가능
* Task List 확인
	* `$ bitbake -c listtasks core-image-minimal`
<주요 task> 
* do_fetch : source code를 fetch 작업 수행 
* do_unpack: source code의 압축 해제 작업 수행 (tar.gz, zip, xz, tar ..) 
* do_patch: source code에 적용할 patch가 있는 경우 적용하는 작업 수행 => 여기서 자주 죽음
* do_configure: source code에 configure script가 있을 경우 이를 수행하는 작업 
* do_compile: compile 작업 수행 
* do_install: build 결과물을 rootfs에 포함시키는 작업(설치) 
* do_package: 패키지 생성 작업 
* do_rootfs: rootfs 이미지 생성 작업 수행
```bash
❯ bitbake -c listtasks core-image-full-cmdline
Loading cache: 100% |###########################################################################################| Time: 0:00:00
Loaded 1923 entries from dependency cache.
NOTE: Resolving any missing task queue dependencies

Build Configuration:
BB_VERSION           = "2.8.1"
BUILD_SYS            = "x86_64-linux"
NATIVELSBSTRING      = "universal"
TARGET_SYS           = "arm-poky-linux-gnueabi"
MACHINE              = "raspberrypi4"
DISTRO               = "poky"
DISTRO_VERSION       = "5.0.18"
TUNE_FEATURES        = "arm vfp cortexa7 neon vfpv4 thumb callconvention-hard"
TARGET_FPU           = "hard"
meta
meta-poky
meta-yocto-bsp       = "scarthgap:70ed6f677234d32198371a030178d2f272cf2d94"
meta-raspberrypi     = "scarthgap:167703d5618498bb7feeaedf18e61be7a8246d1b"

Sstate summary: Wanted 0 Local 0 Mirrors 0 Missed 0 Current 0 (0% match, 0% complete)##################         | ETA:  0:00:00
Initialising tasks: 100% |######################################################################################| Time: 0:00:00
NOTE: No setscene tasks
NOTE: Executing Tasks
do_build                              Default task for a recipe - depends on all other normal tasks required to 'build' a recipe
do_checkuri                           Validates the SRC_URI value
do_clean                              Removes all output files for a target
do_cleanall                           Removes all output files, shared state cache, and downloaded source files for a target
do_cleansstate                        Removes all output files and shared state cache for a target
do_collect_spdx_deps
do_compile                            Compiles the source in the compilation directory
do_configure                          Configures the source by enabling and disabling any build-time and configuration options for the software being built
do_create_runtime_spdx
do_create_runtime_spdx_setscene        (setscene version)
do_create_spdx
do_create_spdx_setscene                (setscene version)
do_deploy_source_date_epoch
do_deploy_source_date_epoch_setscene   (setscene version)
do_devshell                           Starts a shell with the environment set up for development/debugging
do_fetch                              Fetches the source code
do_flush_pseudodb
do_image
do_image_complete
do_image_complete_setscene             (setscene version)
do_image_ext3
do_image_qa
do_image_qa_setscene                   (setscene version)
do_image_tar
do_image_wic
do_install                            Copies files from the compilation directory to a holding area
do_listtasks                          Lists all defined tasks for a target
do_patch                              Locates patch files and applies them to the source code
do_populate_lic_deploy
do_populate_lic_setscene              Writes license information for the recipe that is collected later when the image is constructed (setscene version)
do_populate_sdk                       Creates the file and directory structure for an installable SDK
do_populate_sdk_ext
do_populate_sdk_setscene              Creates the file and directory structure for an installable SDK (setscene version)
do_populate_sysroot_setscene          Copies a subset of files installed by do_install into the sysroot in order to make them available to other recipes (setscene version)
do_prepare_recipe_sysroot
do_pydevshell                         Starts an interactive Python shell for development/debugging
do_recipe_qa
do_recipe_qa_setscene                  (setscene version)
do_rootfs                             Creates the root filesystem (file and directory structure) for an image
do_rootfs_wicenv
do_sdk_depends
do_unpack                             Unpacks the source code into a working directory
NOTE: Tasks Summary: Attempted 1 tasks of which 0 didn't need to be rerun and all succeeded.
```
#### yocto를 이용한 프로그램 개발
* layer 생성
* 소스파일 작성
* recipes 생성
* image에 추가
![[Pasted image 20260619094446.png]]
#### bitbake-layers cmd
* 레이어 생성/확인/추가/삭제
```bash
bitbake-layers create-layer [layer name]
bitbake-layers show-layers [layer name]
bitbake-layers add-layer [layer name]
bitbake-layers remove-layer [layer name]
```
```bash
~/lsnp/yocto/poky/build-rpi4 scarthgap*                                                                               09:46:44
❯ bitbake-layers show-layers
NOTE: Starting bitbake server...
layer                 path                                                                    priority
========================================================================================================
core                  /home/sunbi/lsnp/yocto/poky/meta                                        5
yocto                 /home/sunbi/lsnp/yocto/poky/meta-poky                                   5
yoctobsp              /home/sunbi/lsnp/yocto/poky/meta-yocto-bsp                              5
raspberrypi           /home/sunbi/lsnp/yocto/poky/meta-raspberrypi                            9
```
```bash
~/lsnp/yocto/poky/build-rpi4 scarthgap*                                                                               09:48:01
❯ bitbake-layers create-layer ../meta-test
NOTE: Starting bitbake server...
Add your new layer with 'bitbake-layers add-layer ../meta-test'
```

![[Pasted image 20260619095309.png]]
-> 빌드 후 생성 결과물
![[Pasted image 20260619095326.png]]
-> 이미지 생성
![[Pasted image 20260619101853.png]]
-> 레이어 디렉토리 생성 및 소스파일 구조
```bb
SUMMERY = "Simple helloworld application"
SECTION = "hello"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI = "file://helloworld.c"

S = "${WORKDIR}/sources"
UNPACKDIR = "${S}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${S}/helloworld.c -o ${B}/helloworld 
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/helloworld ${D}${bindir}
}
```
* ${B} -> 빌드 산출물 디렉토리
* ${D} -> 설치될 대상 디렉토리
![[Pasted image 20260619103000.png]]
-> Image에 추가
```conf title="conf/local.conf"
EXTRA_IMAGE_FEATURES ?= "debug-tweaks"
...
IMAGE_INSTALL_append = " helloworld"
```
-> 패키지 추가
* 기존 이미지와 이름이 붙을 가능성 존재 -> 레이어 이름 앞에 공백 하나 추가


![[Pasted image 20260619095258.png]]
![[Pasted image 20260619095300.png]]
![[Pasted image 20260619095301.png]]![[Pasted image 20260619095302.png]]![[Pasted image 20260619095302 1.png]]![[Pasted image 20260619095302 2.png]]![[Pasted image 20260619095303.png]]

---
## 커널 디버깅
* 커널에 부하 없이 tracing 할 수 있음
* 실행중인 커널 디버깅 가능
#### ftrace
* Linux 커널에 내장된 함수 단위 트레이싱 도구
* 성능 분석, 부팅 문제, 드라이버 디버깅에 매우 유용
* ftrace 인터페이스 위치 : /sys/kernel/debug/tracing
* ftrace 주요 기능

| 기능              | 설명             |
| --------------- | -------------- |
| function tracer | 함수 호출 흐름 추적    |
| function_graph  | 함수 호출 + 실행 시간  |
| irqsoff         | IRQ 비활성화 시간 추적 |
| sched_switch    | 스케줄링 이벤트 추적    |
![[Pasted image 20260619141346.png]]
* 선결 조건
	* ftrace 관련 코드가 포함된 리눅스 커널
	* 커널 빌드 디렉토리의 .config 파일 확인
-> `mount -t debugfs nodev /sys/kernel/debug`
```
Kernel hacking → Tracers → Kernel Function Tracer
CONFIG_FUNCTION_TRACER

Kernel hacking → Tracers → Kernel Function Graph Tracer
CONFIG_FUNCTION_GRAPH_TRACER

Kernel hacking → Tracers → enable/disable function tracing dynamically
CONFIG_DYNAMIC_FTRACE
```
![[Pasted image 20260619141658.png]]
-> boot dir 내부 FTRACE 요소 확인
* Ftrace 참조 문서
https://www.kernel.org/doc/html/v6.6/trace/ftrace.html#introduction
* 추적 관련 주요 파일 - /sys/kernel/debug/tacing

| 주요 파일                                       | 내용                                                                                                                                                                                                                                                                       |
| ------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `trace`                                     | ftrace의 로그가 저장되는 파일                                                                                                                                                                                                                                                      |
| `tracing_on`                                | ftrace on/off `(1/0)`                                                                                                                                                                                                                                                    |
| `available_tracers`                         | 사용 가능한 trace 프로그램의 종류`nop` : 기본 트레이서, 이벤트만 출력`function` : 함수 트레이서, `set_ftrace_filter`에 지정된 함수를 호출하는 함수 출력`function_graph` : 함수 실행시간 및 세부 호출 정보 그래프 표시`wakeup`, `wakeup_dl`, `wakeup_rt` : wakeup latency 분석`mmiotrace` : 메모리맵 IO에 대한 분석`irqsoff` : interrupt latency 분석 |
| `current_tracer`                            | 현재 tracer를 설정하거나 표시하는데 사용, 기본 값 : `nop``available_tracers`에 저장된 트레이서만 설정 가능**주의:** `set_ftrace_filter`와 함께 설정!                                                                                                                                                           |
| 주요 파일                                       | 내용                                                                                                                                                                                                                                                                       |
| `set_ftrace_filter``(*) set_ftrace_notrace` | 트레이스하고 싶은 함수 지정 `(function 또는 function_graph 설정시 이용)``available_filter_functions`에 지정된 함수만 가능**주의:** `current_tracer`를 `function` 또는 `function_graph`로 지정 시 이 필터에 함수를 지정하지 않으면 `available_filter_functions`에 지정된 모든 함수를 트레이스하므로 시스템 뻗임!!                                 |
| `available_filter_functions`                | 트레이싱 가능한 함수 목록디바이스 드라이버나 커널 소스에 새로운 함수 구현 시 확인 가능                                                                                                                                                                                                                        |
| `set_ftrace_pid`                            | 추적을 원하는 특정 프로세스 또는 쓰레드의 ID 지정                                                                                                                                                                                                                                            |
| `buffer_size_kb`                            | `ftrace` 로그 버퍼 크기, 로그 내용을 더 많이 저장하는 경우 설정                                                                                                                                                                                                                                |
| `function_profile_enable`                   | `ftrace`의 함수 프로파일링`(Function Profiling)` 기능을 `on/off`이 값을 `1`로 설정하면 커널의 각 함수의 호출 횟수와 누적 실행 시간을 측정해 `/sys/kernel/tracing/trace_stat/function*` 파일에 저장                                                                                                                     |
```bash
root@Sunbi:/sys/kernel/debug/tracing# cat trace
# tracer: nop
#
# entries-in-buffer/entries-written: 0/0   #P:4
#
#                                _-----=> irqs-off/BH-disabled
#                               / _----=> need-resched
#                              | / _---=> hardirq/softirq
#                              || / _--=> preempt-depth
#                              ||| / _-=> migrate-disable
#                              |||| /     delay
#           TASK-PID     CPU#  |||||  TIMESTAMP  FUNCTION
#              | |         |   |||||     |         |
```
* 이벤트만 추적하는 tracer
```bash
root@Sunbi:/sys/kernel/debug/tracing# cat tracing_on
1
```
* 추적 상황 -> 추적 중
```bash
root@Sunbi:/sys/kernel/debug/tracing# echo 0 > tracing_on
root@Sunbi:/sys/kernel/debug/tracing# cat tracing_on
0
```
* 추적 안 함
```bash
root@Sunbi:/sys/kernel/debug/tracing# cat available_tracers 
blk function_graph wakeup_dl wakeup_rt wakeup function nop
```
* 추적 가능한 종류들
```bash
root@Sunbi:/sys/kernel/debug/tracing# cat current_tracer
nop
```
* 현 추적기 종류
=> echo val redirect를 활용해 값 변경 가능
```bash
root@Sunbi:/sys/kernel/debug/tracing# cat set_ftrace_filter 
#### all functions enabled ####
```
* 필터 설정
-> 추적하고 싶은 함수만 넣으면 해당 함수만 추적 가능
#### 실습
![[Pasted image 20260619144032.png]]
![[Pasted image 20260619144128.png|607]]
![[Pasted image 20260619144157.png|608]]
![[Pasted image 20260619144259.png]]
-> 추적 결과는 `cat trace`로 확인
* function_graph
![[Pasted image 20260619144526.png|697]]
![[Pasted image 20260619144611.png|697]]=> 소요된 시간 + 관계 출력
* function_graph란?
	* ftrace 고급 모드
	* 함수 호출 관계(call graph)를 트리 형태로 출력
	* 각 함수의 실행 시간까지 표시
	* 드라이버 초기화, IRQ 처리, 시스템 콜 흐름 분석에 매우 강력
* function_graph가 제공하는 정보

|항목|설명|
|---|---|
|함수 호출 순서|어떤 함수가 어떤 함수를 호출했는지|
|중첩 깊이|함수 호출 스택 구조|
|실행 시간|각 함수의 entry ~ exit까지 걸린 시간|
|스케줄링 지연|함수 실행 중 스케줄링이 발생했는지|
* 특정 함수만 추적
```bash
echo vfs_open > set_graph_function 
echo function_graph > current_tracer 
echo 1 > tracing_on 
cat /etc/hostname > /dev/null 
cat trace
```
* 함수 실행 시간 기준 필터링
```bash
echo 10 > tracing_thresh
```
* function_graph tracer가 기록하는 함수들 중 실행 시간이 10µs(마이크로초) 이상 걸린 함수만 trace에 남긴다 
* 아주 빠르게 실행되는 함수들은 로그에서 자동으로 제외된다.
![[Pasted image 20260619152039.png]]
=> kfree, kmalloc tracing

|서브시스템|이벤트(함수)|의미|
|---|---|---|
|`irq/`|`irq_handler_entry`|인터럽트 발생 시작과 인터럽트 번호 및 이름 출력|
|`irq/`|`irq_handler_exit`|인터럽트 핸들링 완료|
|HW 인터럽트 및 SW 인터럽트(시스템 콜)를 추적하는 이벤트|`softirq_raise`|Soft IRQ 서비스 실행 요청|
|HW 인터럽트 및 SW 인터럽트(시스템 콜)를 추적하는 이벤트|`softirq_entry`|Soft IRQ 실행 서비스 시작|
|HW 인터럽트 및 SW 인터럽트(시스템 콜)를 추적하는 이벤트|`softirq_exit`|Soft IRQ 서비스 실행 완료|
|`sched/`프로세스의 스케줄링 동작 및 프로파일링을 추적하는 이벤트|`sched_switch`|문맥 교환 동작|
|`sched/`프로세스의 스케줄링 동작 및 프로파일링을 추적하는 이벤트|`sched_wakeup`|프로세스를 깨우는 동작|
![[Pasted image 20260619152503.png]]
![[Pasted image 20260619152609.png]]
![[Pasted image 20260619152616.png]]
![[Pasted image 20260619152622.png]]
![[Pasted image 20260619152636.png]]
![[Pasted image 20260619153124.png]]
![[Pasted image 20260619154046.png]]
![[Pasted image 20260619154130.png]]
![[Pasted image 20260619154503.png]]
![[Pasted image 20260619154512.png]]
```bash
#!/bin/bash

echo 0 > /sys/kernel/debug/tracing/tracing_on
sleep 1

echo nop > /sys/kernel/debug/tracing/current_tracer
echo 0 > /sys/kernel/debug/tracing/events/enable
sleep 1

echo 8096 > /sys/kernel/debug/tracing/buffer_size_kb

echo 1 > /sys/kernel/debug/tracing/events/sched/sched_switch/enable
echo 1 > /sys/kernel/debug/tracing/events/sched/sched_wakeup/enable
sleep 1

echo 1 > /sys/kernel/debug/tracing/events/irq/irq_handler_entry/enable
echo 1 > /sys/kernel/debug/tracing/events/irq/irq_handler_exit/enable

echo 1 > /sys/kernel/debug/tracing/tracing_on
```
```bash
#!/bin/bash

echo 0 > /sys/kernel/debug/tracing/tracing_on
echo "ftrace off"
sleep 3

cp /sys/kernel/debug/tracing/trace .
mv trace ftrace_log.txt
```
#### 모듈 적재 디버깅
![[Pasted image 20260619160811.png]]
![[Pasted image 20260619163033.png]]
