#### Signal n Slot
* 이벤트 처리 매커니즘 - 시그널/슬롯
* 시그널이 발생하면 호출되는 함수 - Slot
* 이벤트 발생 객체 Sender
* 이벤트 받아 처리하는 객체 Receiver
* 스스로 이벤트 발생 및 처리 가능
![[Pasted image 20260416092352.png]]
* Signal만 존재 -> sender
* Signal + Slot => Sender + Receiver
* connect -> Sender에서 Signal을 통해 처리를 위임
	* 1대1 형태(Sender-Receiver)
* 보통은 타 Object에서 발생한 Signal을 처리하는 타 Object에 Slot을 넣어둠
* emit => Signal 이벤트 발생시킴
	* 또한 시그널에는 값이 들어가 있음
```cpp title="Signal"
class SignalSlot : public QObject 
{ 
	Q_OBJECT 
public: 
	void setValue(int val) { 
	emit valueChanged(val); 
	} 
signals: 
	void valueChanged(int newValue); 
private: int m_value; };
```
* 헤더 부분에 Slot 명시함
```cpp title="header.h"
...
public slots:
	void setValue(int val);
};
```
* connect는 widget.cpp에 명시
```cpp
#include "widget.h"
Widget::Widget(QWidget *parent) : QWidget(parent)
{
 lbl = new QLabel("", this);
 lbl->setGeometry(10, 10, 250, 40);
 SignalSlot myObject;
 // New Style
 connect(&myObject, &SignalSlot::valueChanged, this, &Widget::setValue);
/* Old Style
 connect(&myObject, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
 */
 myObject.setValue(50);
}
void Widget::setValue(int val)
{
 QString text = QString("Signal emmit, Value:%1").arg(val);
 lbl->setText(labelText);
}

```
* Call by value 형태로 전달, 값의 복사가 발생
	* param은 대부분의 형태가 call by point address / call by reference
* 시그널 지정은 가능, new style을 사용하면 param 지정 부분이 누락
	* 해당 함수의 이름이 단 하나만 존재 할 때 사용
	* 오버로딩, 오버라이딩의 경우 모호함의 문제 발생되는 경우 존재함
```cpp
cnt1 = new Counter("counter 1");
cnt2 = new Counter("counter 2");
connect(cnt1, SIGNAL(valueChagned(int)), cnt2, SIGNAL(valueChagned(int)));
connect(cnt2, SIGNAL(valueChagned(int)), cnt2, SLOT(setValue(int)));
```
* 시그널의 전파 예시임
![[Pasted image 20260416095629.png]]
* 이벤트 처리의 전파
	* 이벤트가 연결되어 처리된다
* QObject기반, Qt에서만 사용이 가능하다
* 커스텀 Widget을 만들어 써먹는거 아니면 emit은 잘 안씀
	* 보편적인 상황에서는 connect, slot을 많이 씀
#### Qt Desinger를 이용한 GUI 설계
* .moc 폴더를 확인하면 Designer를 통해 생성한 위젯들의 원본 코드를 확인 가능함
* Ui 생성 시 컴파일러가 자동 변환 시작

#### Dialog
| 종류              | 설명                           |
| --------------- | ---------------------------- |
| QInputDiaglog   | 사용자로부터 값을 입력 받을 수 있음         |
| QColorDialog    | 특정 컬러 선택                     |
| QFileDialog     | 파일 또는 디렉토리 선택하는 GUI 인터페이스 제공 |
| QFontDialog     | 폰트 선택                        |
| QProgressDialog | 진행 사항 출력                     |
| QMessageBox     | 모달 방식                        |
* Modal vs Not Modal(Modalless)
	* Modal은 제어권을 Parent로 넘기지 않음
	* Modal(popup느낌)
