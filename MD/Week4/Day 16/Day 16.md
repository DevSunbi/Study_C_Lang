## HyperLink
* [[MD/Week4/Day 16/CodeBase|CodeBase]]
---
# QT
#### 주 사용 언어
* C++ 기반이지만, Python으로 하는 경우 존재
	* 하지만 Python은 불러오는 방식, 오버헤드가 존재 할 경우 존재
* Qt Quick
	* QML(Design Logic) + CPP(code)
* QWidget
	* C++(Design Logic) + C++(code)
* Func Logic -> Event Handler
#### MVC Architecture
* Model View Controller
	* Model -> Data
	* View -> UI/UX
	* Controller -> control Logic
* MVCC, MVP 등 여러 모델 존재
#### QT
* C++ Base. QML Base 존재
* 컴파일러와 그래픽 디자이너 툴의 차이가 존재
* QT / VS 차이 존재
	* VS -> 컴파일러로 MSVC 사용, QT 디자이너를 비주얼 스튜디오에서 확장 사용해서 가능
* Qt Linguist Tool
	* 국제화를 위해 반드시 필요
	* 각 국가별로 사용하는 언어에 따라 GUI 언어 표시 가능
		* 통상적으로 한글, 영어, 일어 사용
#### Cmake Build
* Qt에서 프로젝트 생성 시 Cmake, qmake, qbs 등 선택 가능
* makefile -> Compiler, Linker 등 형식 지정 되어있는 파일
#### Start
![[Pasted image 20260413112916.png]]
* Widget -> UI를 갖는 컴포넌트
* MainWindow(기본 동작) -> qMainWindow로, 화면에 창을 출력해준다
	* BaseClass -> 선조 클래스 개념(기본 동작 클래스 상속, +a)
* QT에서 APP을 만든다 -> 기본 동작(qMainWindow)에 나만의 기능을 추가해 Window를 만든다는 개념
```cpp title="main.cpp"
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator; // Linguist
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Week4_Day16_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w; // default 
    w.show();
    return QCoreApplication::exec();
}

```
```cpp title="mainWwindow.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override; // 선조 재정의 /  virtual 없음, 수동 해제 

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

```
```cpp title="mainwindow.cpp"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

```
#### CMake 활용한 Console App 구현
* QCoreApplication?
	* Core -> console 쓰는 전문 Application / 기본적인 부분만 지원
	* qDebug를 활용해 콘솔 화면에서 입출력 가능
```cpp title="CMakeLists.txt"
cmake_minimum_required(VERSION 3.19)
project(ConsoleApplication_CMake LANGUAGES CXX) // 프로젝트 이름 및 언어

find_package(Qt6 6.5 REQUIRED COMPONENTS Core LinguistTools) // 최소 요구 버전

qt_standard_project_setup()

qt_add_executable(ConsoleApplication_CMake
    main.cpp
) // 소스파일 명시, 타 소스 파일도 컴파일에 들어가도록 명시(main은 필수)

qt_add_translations(
    TARGETS ConsoleApplication_CMake
    TS_FILES ConsoleApplication_CMake_ko_KR.ts
)

target_link_libraries(ConsoleApplication_CMake
    PRIVATE
        Qt::Core
) // Lib 지정

install(TARGETS ConsoleApplication_CMake
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

```
```cpp title="mainwindow.cpp"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // 생성한 ui와 연결
}

MainWindow::~MainWindow()
{
    delete ui;
}

```
* MOC -> UI 컴파일 시 자동 생성되는 파일
* RCC -> 자원을 갖고 만들어짐(Resource) 리소스 파일 생성
#### qmake 이용한 프로젝트 빌드
```qmake title="Qmake.pro"
QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \ // escape character
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```
![[Pasted image 20260413140908.png]]
* ui 보면 xml 형태로 작성 되어 있음을 확인 가능
#### 이벤트 처리
* 이벤트의 종류는 여러가지
* QLabel -> 화면에 문자열을 출력하기 위해 만들어지는 widget
* Pressed/Released / Click 등 이벤트 설정 가능
* EventHandler
	* mainwindow에서 이벤트 발생 시, 함수 생성하여 동작 할당 가능
	* slots -> 특정한 위젯에 특정한 동작을 연결해주는 목적으로 쓰임(QT)
* Signal -> 이벤트라고도 함
* Button
	* clicked 등 존재
![[Pasted image 20260413150728.png]]
```cpp title="mainwindow.cpp"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "ㅎㅇㅋㅋ";
}


```
![[Pasted image 20260413150924.png]]
-> 헤더파일 확인해보면 자동 생성된 것을 알 수 있음
* 대부분의 작업들이 eventbased program임
![[Pasted image 20260413151156.png]]
-> mainwindow.cpp 
* 파일 내부에서 제작된 Ui 및 내부 파일들이 자동적으로 연결 및 사용 가능한 구조로 생성
* 특정한 이벤트에 의해 동작 될 때 Slot 함수 명시(Go to Slot)
* 특정한 컴포넌트에서 특정 시그널 발생 -> this 객체의 특정 함수가 처리 담당
```cpp
connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_clicked()));
```
* 첫 인자 - 시그널 발생 오브젝트
* 두 번째 인자 - 시그널 발생 종류
* 세 번째 인자 - 시그널과 연결할 slot 함수가 있는 인스턴스 명
* 마지막 인자 - 호출 할 slot 함수 명시
## Qt GUI Widgets
* C -> char 문자열
* Cpp -> String
* MFC -> CString
* QT -> QString
	* QT는 한번 더 추상화 한 개념
	* Linux / MS에 따라 다르게 동작하게 되는 방식
	* 플랫 폼에 상관 없이 표준화된 클래스
* QString에서 문자열 할당 시 &는 의미가 있음 "S&S"
![[Pasted image 20260413163505.png]]
