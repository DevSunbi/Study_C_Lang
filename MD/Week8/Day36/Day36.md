## Cmake
* 플랫폼별 빌드 시스템 생성, CMakeLists.txt에 프로젝트 정보 선언, CMake가 그에 맞는 빌드 구성
* Out-of-Source Build 권장
	* 소스 폴더 외부에 build 폴더 생성, 그 안에 CMake 실행
	* 정리/재구성 용이, 빌드 산출물이 소스 트리에 섞이지 않음
* 모던 CMake 지향
	* 전역 설정 대신 타깃 기반 접근(target-based)
	* 실행 파일/라이브러리를 타깃으로 정의, 그 타깃에만 필요한 include 경로, 링크, 컴파일 옵션 부여 -> 관리 쉽고 의존성 명확
* 컴파일러/제네레이터 선택
	* 여러 버전이 설치된 환경에선 CMake 실행 시 컴파일러 명시 가능
	* CC, CXX 환경 변수 또는 -D 인자를 사용해 C/C++ 컴파일러 지정

| 심볼                           | 의미                                                                                                                                           |
| ---------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| `cmake_minimum_required`     | 프로젝트를 빌드하기 위해 필요한 최소 CMake 버전을 지정<br>`cmake_minimum_required(VERSION 3.16)`                                                                  |
| `project`                    | 프로젝트 이름과 언어를 정의<br>`project(MyApp LANGUAGES CXX)`                                                                                            |
| `add_executable`             | 실행 파일을 생성<br>`add_executable(main main.cpp utils.cpp)`                                                                                       |
| `add_library`                | 라이브러리를 생성 `STATIC`, `SHARED`, `INTERFACE`<br>`STATIC` 기본, 단 `set(BUILD_SHARED_LIBS ON)` 시 `SHARED` 기본<br>`add_library(mylib STATIC lib.cpp)` |
| `target_link_libraries`      | 대상(target)에 다른 라이브러리 연결<br>`target_link_libraries(main PRIVATE mylib)`                                                                       |
| `include_directories`        | 헤더 파일 검색 경로 추가<br>`include_directories(${CMAKE_SOURCE_DIR}/include)`                                                                         |
| `find_package`               | 외부 패키지/라이브러리 검색<br>`find_package(OpenCV REQUIRED)`                                                                                           |
| `target_include_directories` | 특정 target에만 헤더 경로 추가<br>`target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS})`                                                    |
| `set`                        | 변수 정의<br>`set(변수명 값)` 또는 `set(변수명 값1 값2 값3)`<br>변수는 `${변수명}` 형태로 사용<br>예시 1: `set(SRC_FILES a.c b.c)`<br>예시 2: `set(CMAKE_CXX_STANDARD 17)`  |
| `option`                     | ON/OFF 설정 옵션 정의<br>`option(USE_MYLIB "Use my custom library" ON)`                                                                            |
| `if / else / endif`          | 조건문<br>`if(USE_MYLIB)`<br>&nbsp;&nbsp;`add_subdirectory(mylib)`<br>`else()`<br>&nbsp;&nbsp;`message(STATUS "USE_MYLIB is OFF")`<br>`endif()` |
| `message`                    | 빌드 설정 과정에서 메시지 출력<br>`message(STATUS "Building project...")`                                                                                 |
| `add_subdirectory`           | 하위 디렉터리 포함<br>`add_subdirectory(src)`                                                                                                        |
| `install`                    | 빌드 결과물 설치 규칙 정의<br>`install(TARGETS main DESTINATION bin)`                                                                                   |
#### 기본적인 CMakeLists.txt
```CMake
cmake_minimum_required(VERSION 3.22)
project(HelloCMake LANGUAGES CXX VERSION 0.1.0) # project : 이름, 언어, 버전까지 명시 가능

add_executable(hello main.cpp) # 실 프로그램은 add_excutable/add_library로 만듦

#권장 : 표준/경고 등 컴파일 옵션은 타깃에 부여
target_compile_features(hello PRIVATE cxx_std_17)
```
#### 빌드와 실행
```shell
#빌드 폴더 따로 생성, 빌드 폴더만 지우면 깨끗한 재구성 가능
$mkdir build && cd build

#CMake 실행(상위 소스 지정)
$cmake ..

# 빌드 수행
$cmake --build .
```
#### 컴파일러 명시
```bash
# 1회성 지정 (첫 cmake 실행에만 유효)
CC=/usr/bin/gcc-11 CXX=/usr/bin/g++-11 cmake ..
# 캐시 변수로 지정 (유지됨)
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-11 -D CMAKE_CXX_COMPILER=/usr/bin/g++-11 ..
```
#### 모던 CMake 핵심 : 타깃 기반 접근
* 타깃 정의
	* add_executable 또는 add_library로 타깃을 만든 뒤, 그 타깃에 필요한 속성 국소적 부여
* include 경로
	* target_include_directories 사용
	* 범위는 PRIVATE/INTERFACE/PUBLIC 중 선택
		* PRIVATE : 현 타깃 빌드 시 필요
		* INTERFACE : 현 타깃을 사용하는 타 다킷에만 필요(헤더 전파 등)
		* PUBLIC : 현 타깃과 그 타깃을 사용하는 타 타킷 모두에 필요
* 링크
	* target_link_libraries로 연결, 상대 타킷 또는 시스템/패키지 라이브
* 라이브러리 + 실행 파일 예시
```cmake
# 라이브러리 정의
add_library(mathFunctions
src/mathFunctions.cpp
include/mathFunctions.hpp
)
# 라이브러리의 헤더 경로 전파: 사용처가 포함해야 하므로 INTERFACE/ PUBLIC 사용
target_include_directories(mathFunctions
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)
# 실행 파일 정의
add_executable(tutorial main.cpp)
# 실행 파일에 라이브러리 연결
target_link_libraries(tutorial PRIVATE mathFunctions)
```
=> 왜 모던 방식인가: 전역 include_directories, add_definitions
등은 프로젝트 전체에 퍼져 관리가 어렵기 때문에 타깃에만 필요
한 정보를 부여하면 의존성 경로와 옵션이 자연스럽게 전파되고,
문제 추적이 용이
#### 외부 라이브러리, 테스트, 패키징
* 외부 라이브러리 찾기와 연결
	* find_package : 설치된 패키지 탐색, 타깃 가져옴
```cmake
find_package(fmt CONFIG REQUIRED)
target_link_libraries(tutorial PRIVATE fmt::fmt)
```
* 가져온 타깃을 그대로 링크하면 include 경로/컴파일 옵션/정의 등이 함께 전파
#### CMake
* 단위 테스트 추가
	* CTest + GoogleTest 조합 추천
```cmake
enable_testing()
add_executable(math_tests tests/math_tests.cpp)
target_link_libraries(math_tests PRIVATE mathFunctions GTest::gtest_main)
add_test(NAME math_tests COMMAND math_tests)
```
* 실행 : ctest -V로 테스트, CI와도 쉽게 연동
* 설치와 배포(기초)
```cmake
# 설치 규칙
install(TARGETS tutorial mathFunctions
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
```
* cmake --install로 시스템에 배포
	* e.g ) cmake --install build --prefix /my/install/path
#### 실무 팁과 트러블슈팅
* 빌드 폴더만 삭제
	* 구성 초기화 필요 시 build 폴더 지우면 클린 빌드 / 재시작 가능
* 경로 공백
	* Win처럼 공백이 있는 경로를 변수로 전달할 땐 큰따옴표 사용
* 컴파일러 강제 지정
	* 시스템이 Clang/GCC를 뒤섞어 선택하거나 구식 버전을 잡을 때는 CC/CXX또는 CMAKE_\*\_COMPILER로 명시, 혼선 최소화
* 전역 설정 지양
	* 모든 타킷에 영향을 주지 말 것, 대신 target_\*API로 필요한 범위에만 적용
#### 정적/공유 라이브러리 빌드 및 설치
```cmake
# STATIC 또는 SHARED 선택 가능 
option(BUILD_SHARED_LIBS "Build using shared libraries" ON) add_library(mathFunctions mathFunctions.cpp) target_include_directories(mathFunctions PUBLIC $ $ ) 
# 설치 규칙 
install(TARGETS mathFunctions 
		EXPORT mathFunctionsTargets 
		ARCHIVE DESTINATION lib 
		LIBRARY DESTINATION lib 
		RUNTIME DESTINATION bin) 
install(FILES mathFunctions.h DESTINATION include)
```
## Docker & Git
#### Docker
* 컨테이너를 생성/관리/배포하는 오픈소스 플랫폼
	* 운영체제 수준 가상화(컨테이너) 기술 활용, 소프트웨어 패키징/배포하는 플랫폼
	* PaaS(Platform as a Service)를 구현할 때 기반 기술로 활용
	* Docker != PaaS
		* Docker는 PaaS를 만들기 위한 기본 기술
* 애플리케이션을 인프라와 분리, 빠르게 배포 가능
	* 운영체제 위에 설치, 컨테이너 단위로 애플리케이션 실행
	* 컨테이너 안에 필요한 환경 포함, 호스트 운영체제와 무관하게 동일한 실행 환경 제공
* 개발->테스트->배포의 흐름 일관되게 유지 가능
#### On-Premiss
* 조직 내부에 모든 HW와 SW를 설치하고 관리하는 전통적인 IT 인프라 방식
* 장점
	* 데이터 내부 존재, 보안 통제 용이
	* 전체 시스템에 대한 제어권과 커스터마이징 가능
	* 규제 대응이 필요한 금융, 공공기관에 적합
* 단점
	* 초기 설치 비용 높음(서버, 네트워크 등)
	* 유지보수와 인력 관리에 따른 운영 비용 증가
	* 자원 확장에 제약 -> 수요 변화에 대한 유연한 대응 어려움
#### 컨테이너
* 애플리케이션 실행에 필요한 코드, 라이브러리, 설정 파일 등을 하나로 묶은 실행 패키지하고 격리하는 기술
* 특징
	* 경량화된 가상화 기술, 빠른 실행 속도
	* 격리된 환경에서 애플리케이션 실행
	* 운영체제 공유로 자원 효율성 우수
* 장점
	* 개발 환경과 운영 환경 간의 일관성 보장
	* 이식성과 배포 유연성 향상
	* 독립적 실행으로 안정성 및 보안성 강화
* Container
	* 운영체제 수준 가상화(커널 공유)
	* OS 커널 공유, 앱과 종속성만 포함
	* 가벼움
	* 이식성 매우 뛰어남 -> 어디서나 실행 가능
	* 부팅속도 빠름
* VM
	* 하드웨어 가상화(전체 OS 포함)
	* OS+App+Lib 등 모든 계층 포함
	* 무거움
	* 환경에 따라 제약 발생 -> 이식성 저하
	* 부팅속도 느림(OS 부팅 필요)
#### 실행 구조
* build 단계 
	* 코드 + OS + Lib -> Dockerfile(애플리케이션에 필요한 환경(코드, 라이브러리, OS 등)을 하나의 도커 이미지로 만들기 위한 명령어 모음 파일) -> build로 이미지 생성
* Run 단계
	* Docker 이미지 -> 도커 run -< 컨테이너 실행(로컬 환경에 독립적)
* 이식성 
	* 같은 이미지를 AWS, GCP, Azure 등 다른 OS/컴퓨터에서도 동일하게 실행 가능
#### 아키텍처
* Client
	* 사용자 명령어 실행 -> 도커 데몬에 요청 전달
* Host
	* Docker Demon : 요청 처리 및 컨테이너 관리
	* Images : 앱 실행용 이미지 저장
	* Containers : 실행 중인 컨테이너 인스턴스
* Registry 
	* 이미지 저장소
	* 공식 이미지, 확장 기능, 플러그인 포함
* 흐름
	* docker pull -> registry에서 이미지 가져오기
	* docker build -> dockerfile로 이미지 생성
	* docker run -> 이미지로 컨테이너 실행
#### 도커 엔진 아키텍처
* docker client : 사용자가 docker run 등 명령 실행
* docker daemon : api 요청 수신 및 처리, containerd에게 gRPC 요청 전달
* containerd : 컨테이너 생성, 이미지 관리 등 고수준 런타임
* shim : 독립적인 중간 프로세스, runc와 통신하며 컨테이너 유지 지원
* runc : 리눅스에서 컨테이너 실제 실행(OCI 준수)
* containers : runc가 실행한 실제 컨테이너 인스턴스
## Git
#### Git?
* DVCS, Distributed Version Control System
* 소스 코드 변경 사항을 효과적으로 관리, 협업을 용이하게 하기 위해 개발된 도구
* 버전 관리
	* 파일 변경 이력 시간순 저장
	* 이전 상태 되돌리기
	* 변경 내용 추적
* 백업
	* 로컬 + 원격 저장소
	* push만 해도 백업
	* 복구 용이
* 협업
	* 브랜치 기반 병렬 작업
	* pull/push로 변경 공유
	* PR(Pull Request)로 코드 리뷰 가능
-> git init을 통해 초기화 -> 버전관리 대상 지정
#### 파일 저장 단계
* 작업 트리 변경 사항 만들기
* 스테이지에 변경 사항 올리기 -> git add
* 스테이징한 파일 커밋 -> git commit