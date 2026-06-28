## Yocto
- 툴체인 + 부트로더 + 커널 + 루트 파일 시스템 빌드
- 레시피 그룹(파이썬, 쉘 스크립트)을 중심으로 구성
- BitBake 태스크 스케줄러에 의해 레시피에 설정된 사항 생성
- 주요 구성요소

| 구성요소 | 수행 내용 |
|---|---|
| OE-Core | OpenEmbedded 와 공유하는 코어 메타데이터 |
| BitBake | 태스크 스케줄러 |
| Poky | 레퍼런스 배포판 |
| Documentation | 사용자 매뉴얼, 컴포넌트 개발 지침서 |
| Toaster | BitBake와 그 메타데이터를 위한 웹 기반 인터페이스 |
=> .bb file->recipe file
```bb title=u-boot_2024.01.bb
require u-boot-common.inc
require u-boot.inc

DEPENDS += "bc-native dtc-native python3-pyelftools-native"

SRC_URI += "file://CVE-2024-57254.patch \
            file://CVE-2024-57255.patch \
            file://CVE-2024-57256.patch \
            file://CVE-2024-57257.patch \
            file://CVE-2024-57258-1.patch \
            file://CVE-2024-57258-2.patch \
            file://CVE-2024-57258-3.patch \
            file://CVE-2024-57259.patch \
            file://CVE-2024-42040.patch \
"
```
* bitbake의 target
```text
core-image-minimal : 테스트용, 커스텀 이미지의 기초가 되는 콘솔 기반의 소형 시스템 core-image-full-cmdline : 콘솔 기반 시스템으로 표준 CLI 환경과 타깃 장치에 대한 완전한 지원 시스템 
core-image-sato : gnome 데스크탑 시스템 
core-image-weston : wayland 를 지원하는 임베디드 그래픽 시스템 
meta-toolchain : cross-toolchain 빌드 시스템 
meta-ide-support : 통합 개발환경 도구 빌드 시스템
```
* bitbake를 이용한 빌드
```test
bitbake core-image-minimal
```
* bitbake 완료 후 tmp/ 디렉토리

| 경로 | 설명 |
|---|---|
| work/ | 빌드 디렉터리와 루트파일시스템을 위한 작업 영역 |
| deploy/ | 타깃에 배포할 최종 바이너리 |
| deploy/images/[machine name]/ | 타깃에서 실행될 부트로더, 커널, 루트파일시스템 이미지 |
| deploy/rpm/ | 이미지 구성했던 SW 패키지 |
| deploy/licenses/ | 각 패키지에서 추출한 라이선스 파일 |
* 기본 레시피 + 메타데이터 레이어를 추가하는 방식으로 확장
* 각 레이어 간의 의존성 및 호환되는 yocto 프로젝트 버전 확인 필요
* 각 레이어는 최소한 하나 이상의 conf/local.conf와 README 파일 및 라이선스로 구성
