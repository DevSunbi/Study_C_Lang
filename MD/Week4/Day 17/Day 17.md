## HyperLink
* [[MD/Week4/Day 17/CodeBase|CodeBase]]
---
#### 컴포넌트
* 컴포넌트를 위젯이라 함
	* Signal과 연결해 동작을 시킬 수 있는 기능이 연결
	* 하나의 바구니의 역할을 수행 할 수 있는 GroupBox
* 제일 바깥에 있는 것이 최 상위 컨테이너
![[Pasted image 20260414093941.png]]
* 그래서 My_First_Window라는 커다란 위젯 내부에 6개의 체크 박스, 그룹 박스를 통한 지정
* 구조
* 위젯(컨테이너)
	* GroupBox
		* CheckBox
=> 순차적으로 컨테이너에 쌓이는 구조가 기초, 나중에 넣을 수 있음
![[Pasted image 20260414094216.png]]
![[Pasted image 20260414094914.png]]
* 황색 : 선조의 속성(상속, QWidget)
* 녹색 : QGroupBox만의 속성
* 계층적 구조 구성을 위해 GroupBox 생성 후 CheckBox 생성 필수
![[Pasted image 20260414095906.png]]
![[Pasted image 20260414102400.png]]
* Qt는 모든 객체가 QObject를 상속받음
	* 메모리 상에서 만들어지는 모든 객체를 QObject라 명칭
	* 가장 Main Event -> destroyed() 
		* 객체 파괴 시 소멸자 호출
		* 없어질 때 Signal 발생 == destroyed signal
* QWidget -> 보여지는 컴포넌트(Window를 갖는 컴포넌트)
#### Designer
* Designer를 통해(UI)를 통해 작업하는 것은
	* 내부 컴파일러를 통해 자동으로 코드 생성
	* 해당 코드가 내가 작성한 코드와 연결되어 작동
#### Connect Func
* 수동으로 연결해주기 위함
* connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_clicked()));
* sender -> 이벤트 발생 객체
* 선조의 포인터(QCheckBox \*)로 후손 객체(QObject \*)를 가리킴
#### resources
```cpp
m_exclusive[0]->setIcon(QIcon(":resources/browser.png")); 
m_exclusive[1]->setIcon(QIcon(":resources/calendar.png")); 
m_exclusive[2]->setIcon(QIcon(":resources/chat.png")); 
m_non_exclusive[0]->setIcon(QIcon(":resources/editor.png")); m_non_exclusive[1]->setIcon(QIcon(":resources/mail.png")); 
m_non_exclusive[2]->setIcon(QIcon(":resources/users.png"));
```
* 에셋 먹이는 방법(QMake)
	* setIcon(QIcon(":경로"));
#### 수동적인 프로그래밍
* UI가 없는 상태
* 헤더에 내가 생성해야할 함수의 포인터 생성
* 동작을 정의한 파생 클래스 생성
* 생성자와 동작 메소드 추가
	* 헤더 파일에 생성해야 할 위젯들의 객체가 생성 되어있어야 함
* 위젯의 생성자 함수에서 상세 작동 명시(객체 생성)
* geometry를 통해 객체를 표기의 크기 명시
* 로직의 적용을 위해 slot 함수 선언
	* 해당 slot 함수는 반드시 connect에 의해 적절한 signal과 연결되어야함 
	* connect 인자 : 
		* sender -> 이벤트 발생 객체
		* SIGNAL -> 시그널에 해당하는 함수/변수 지정
		* this ->  receiver 객체(본인)
		* SLOT -> 실행 할 slot 함수
#### Design을 활용한 프로그래밍
* ui에 선언된 형태를 빌려 쓰는 형태로 연결 되어있음
* Object inspector 내부에 정의 되어있는 위젯의 이름으로 사용
* 기본 적인 생성자에서 자동적으로 Ui 만들어짐(ui->setupUi(this))
* 자동으로 함수가 생성됨 , 함수의 코드를 직접적으로 작성 해야함
	* 시그널에 대한 특정 작업 실행하도록
## CMake에서 resource 넣기
```cmake
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
```
* 이상 세 항목을 CMakeLists.txt에 항상 넣어야 함
