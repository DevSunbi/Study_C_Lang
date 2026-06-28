## U-Boot
#### U-Boot
- 임베디드 분야의 다양한 CPU 아키텍처 및 장치를 지원하는 부트로더
- Denx Software Engineering에서 유지보수
- ARM 기반 & 임베디드 Linux 시스템 경우 주로 u-boot 사용
- u-boot 기반으로 자신의 Board에 맞게 porting 진행
![[Pasted image 20260616104332.png]]
## 커널 구성과 빌드
#### 사용자 공간, 커널 공간
![[Pasted image 20260616160439.png]]
![[Pasted image 20260616160507.png]]
#### 커널 구성과 빌드
* 커널 모듈
	* 커널의 기능이나 장치 드라이버 등 다양하게 활용
- 임베디드 분야의 장치 드라이버의 경우 일반적으로 모듈보다는 커널에 직접 내재 시키는 경우가 많음
- 임베디드 시스템에서 모듈 사용이 좋은 경우
	- 라이선스 등의 이유로 비공개 모듈이 있는 경우
	- 필수적인 장치 드라이버가 아닌 경우 로딩 시간을 연기함으로써 부팅 시간 감소 가능
	- 로드해야하는 드라이버가 여러 개라 정적으로 링크 시 메모리를 많이 차지해야 되는 경우
- 커널 빌드
	- .config 파일로부터 구성정보를 취합해 의존 관계를 파악하고 커널 이미지를 빌드하는 Makefile 수행
```Makefile
obj-y += mem.o random.o => 무보건 컴파일, 커널 이미지에 퍼함
pbj-$(CONFIG_TTY_PRINTK) += ttyprintk.o => y면 커널 내장, m이면 모듈, x면 컴파일 안 함
```
* 커널 이미지 빌드
`make -j# ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- Image | zImage | uImage`
	-Image - vmlinux + ELF 처리가 가능한 코드 결합
	-zImage - 압축된 Image 파일 + 압축 해제 및 재배치 코드와 결합
	-uImage - zImage + U-Boot Header(64 Byte)
* vmlinux file -> ELF 바이너리(디버깅 정보 포함)
![[Pasted image 20260616162102.png]]
![[Pasted image 20260616162243.png]]
* 커널 부팅 과정 중 초기화 작업이 이루어진 후 사용자 공간을 제공하기 위해 루트 파일 시스템 마운트(램 디스크 또는 실제 파일 시스템)
	* 커널 소스 코드 중 init/main.c의 rest_init() 함수 실행
	* PID 1의 쓰레드 생성 kernel_init() 함수 실행
	* 램디스크가 있는 경우 프로그램 /init 실행, 없는 경우 명령 중의 root= 인자에 지정된 블록 장치 파일의 파일시스템 마운트
* 커널 명령 줄 인자(Documentation / kernel-parameters.txt)
![[Pasted image 20260616162502.png]]
![[Pasted image 20260616163050.png]]
* busybox | toybox 프로젝트를 통해 리눅스 필수 기능을 수행하는 도구를 하나의 바이너리로 묶어 제공