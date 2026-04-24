#### QMainWindow
* QWidget -> 하나의 화면, 데이터 처리 불가
* 복잡한 윈도우 GUI 쓸거면 QMainWindow
![[Pasted image 20260417091140.png]]
* `QApplication a(argc, argv)` -> 메모리 상에서 돌아가는 프로그램
* `a.exec` -> 어떤 Signal이 오는지 기다리고, while(1) 상태, 종료 신호 전까지 진행
* `MainWindow w` -> UI 객체
* `w.show()` -> 표시

mainwindow.cpp
* `tr("&New")` -> 단축키 지정 형태(번역을 위한 함수)
	* tr -> translate
	* & -> 가속키를 지정하는특수 기호, 특정 알파벳 앞에 &를 붙이면 해당 알파벳 아래에 밑줄이 생겨 Alt키와 함께 바로 실행 가능
* `setShortcuts` -> 단축키 선언
* `setStatusTip` -> 커서 올려두면 힌트 나오게 하는 것
* `QDockWidget` -> ![[Pasted image 20260417094729.png|150]]
* 위젯 객체 생성, 생성된 객체의 위치(`setAllowedAreas`) 규정
	* `setAllowedAreas(Qt::LeftDockWidgetArea ...);`
	* 일종의 컨테이너 형태로 아이템을 포함 할 수 있다
	* `addDockWidget(Qt::RightDockWidgetArea, dock);` -> 오른쪽에 생성, 위 허용 범위 지정과 달리 생성 위치를 선언함
	* `setCentalWidget(new MDIMainWindow());` -> 보통 MDI 특성을 갖는 형태로 만들어짐
		* 하나의 창 안에 여러 파일을 동시에 띄움
		* 메인 윈도우 안에 자식 창을 관리하는 컨테이너를 올림
---
#### Stream
* Data(Bin) 형태로 / Text 형태로 열람 가능
	* 다만 Text 형태로 하면 변형이 있을 수 있다
	* TextStream은 Log 열람 시
	* DataStream은 데이터 저장 시
* DataStream 쓰는게 정보 변조 방지에 좋음
* TextStream은 인코딩 정보에 따라 변조 발생 가능성 존재함

#### explicit / implicit
* 명시적/묵시적 형변환 키워드
* 생성자에 인자 할당 -> QString <-> QByte 상속 관계 없음
	* explicit 안하면 명시적 형변환이 아니여도 형변환 진행 가능성 존재

#### File I/O
* 데이터 양에 따른 변화 존재
* stream의 사용을 권장

#### Property
* 값에 접근하기 위한 Getter, Setter
* 멤버 변수에 QProperty 선언, Getter/Setter 없이 값의 변경 가능
* Getter/Setter와 달리 일일이 제어하는 것이 아닌 자동으로 갱신
* 어떤 함수로 값을 읽고 쓰고, 어느 변수에 값을 넣을지 지정 가능

#### Model n View
* QListWidget, QTableWidget, QTreeWidget, QListView, QTableView, QTreeView, QColumnView 등 존재 
* 어떻게 보여야한다만 구성, 실 데이터 조작 코드는 없음
* Ui는 모습만 갖고 있고, Ui에 데이터를 세팅한다라는 느낌
* Model -> 데이터 다룸
* View -> 보이기만 하면 됨
![[Pasted image 20260417122753.png]]
![[Pasted image 20260417122838.png]]
-> Model-View Architecture
![[Pasted image 20260417123112.png]]
* 데이터 가공 형태가 Model
* Model의 데이터를 기반으로 View를 변경
* 데이터 수정 -> Signal 전송 => Slot을 통해 데이터 변경 반영
* Delegate(위임) -> 특정한 함수를 통해 간접적으로 호출(Virtual func 느낌)
![[Pasted image 20260417123544.png]]
* 모델 형태의 예시임
* QStringListModel -> List에서 자주 사용
* DB 연동 시 QSqlTable 많이 사용
* OORDB 많이 씀 
DB-ListView
![[Pasted image 20260417124309.png]]
* ListView는 데이터를 넣는 기능 자체가 없음
* Model에 데이터 저장 후 Model과 View를 연동해 출력하는 방식이 최선
```cpp title="widget.cpp"
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 300);
    QStringList strList;
    strList << "Monday" << "Tuesday" << "Wedneday"
            << "Thurday" << "Friday";

    QAbstractItemModel *model = new QStringListModel(strList); // 모델 선언

    QListView *view = new QListView(); // 뷰 선언
    view->setModel(model); // 모델-뷰 연결

    QModelIndex index = model->index(3, 0); // 모델에 데이터 할당
    QString text = model->data(index, Qt::DisplayRole).toString(); // 할당 데이터 가공

    QLabel *lbl = new QLabel("");
    lbl->setText(text);

    QVBoxLayout *lay = new QVBoxLayout();
    lay->addWidget(view);
    lay->addWidget(lbl);

    setLayout(lay);

}

Widget::~Widget()
{

}

```
* 과제
	* add 누르면 데이터 추가
	* Remove 누르면 데이터 삭제
	* Label -> 클릭하면 레이블에 텍스트가 따라 바뀌도록 수정(list 내부 아이템)
#### QPainter 클래스를 이용한 2D 그래픽스
```cpp
#include "widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    
    painter.end();
}

Widget::~Widget() = default;

```
* Painter를 사용 할 때의 기본 포멧
* begin, end는 필수로 먼저 만들어두기
* 코드는 begin-end 사이에 삽입
* setPen을 통해 brush의 색상 지정 가능
* drawLine을 통해 시작 좌표, x, y축의 길이를 통해 작성 가능
* 외에도 동일
