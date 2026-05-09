#### 멤버 변수 선언
```cpp title="widget.h"
QLCDNumber *lcd;
QLineEdit *edit;
QProgressBar *bar;
QTabWidget *tab;
```
* 클래스 + 포인터 형식으로 선언
* Segment style -> enumerate style인 경우 다수
	* 열거형으로 쓸 수 있는 스타일들 존재
#### 컨테이너 위젯 / 컴포넌트
* 컨테이너 위젯
	* 타 위젯을 내부에 포함 가능한 위젯
* 컴포넌트
	* 본인이 표출 및 동작만 가능한 위젯, 타 위젯을 내부에 포함 불가함
#### 생성자/소멸자
* 객체 생성 시 내부 파라미터로 this 항상 붙음
	* parent 지정을 통한 lifecycle 종속
		* del 따로 안해줘도 됨
#### Tab Widget
```cpp
 QWidget *first = new QWidget;
QWidget *second = new QWidget;
QWidget *third  = new QWidget;
```
* 위 방식과 동일하게 순서 생성 가능

#### LineEdit
* 임의의 값을 받기 위해 주로 사용
	* 주로 마스킹을 활용해 필터링 된 값을 받을 수 있음
#### ProgressBar
* 진척도를 나타내지만 실 활용을 위해서는 타이머 혹은 쓰레드 프로그래밍을 알아야함
## Layout
* 크기 고정이 아닌, 비율에 맞춰 동작하게 되면 좋지 않을까..
* X, Y, 크기 할당은 고정 배치, 윈도우 크기에 따라 동적으로 변하지 않음
* 레이아웃을 쓰면? 허거걱 윈도우 크기에 따라 동적으로 크기가 변경된다

| 클래스         | 설명              |
| ----------- | --------------- |
| QHBoyLayout | 가로 방향 배치        |
| QVBoxLayout | 세로 방향 배치        |
| QGridLayout | 그리드, 바둑판 스타일 배치 |
| QFormLayout | 2열 배치           |
* 레이아웃 매니저는 코드 상에서 작업하는 경우가 더 많음
* Default 레이아웃 하나를 설정하는데 Design 사용
```cpp title=Layout
Layout *Layout = new Layout();
```
 * 형식으로 선언 가능
 * 이후 어느 레이어에 넣을지는
* ```cpp 
  Layout->addWidget
  ```
#### Qt에서 제공하는 데이터 타입과 클래스
* Cpp에서 문자열은 객체
* C -> char 포인터/char 배열(플랫폼 동일) => 두 문자열은 서로 다름
* Qt에서 쓰는 QString / MFC에서의 CString
	* 얘네는 wrapping 되었다 표현, 무언가 덧붙힌 클래스임
	* 아예 다름
	* 다만 원본(C/Cpp) 형태로 변환은 가능하다
	* 또한 원본에서 해당 wrapping으로 변환이 가능하다
	* 그럼? QString과 CString도 서로 변환이 가능하지 않나
* QString을 QByteArray(char의 배열)로 변환해 전송 => char형으로 사용 가능하니 변환 가능
* 문자열은 그 자체만으로는 사용 불가, 어떤 의미로 만들어졌는가를 내포한 인코딩이 따라붙음
* QChar -> 유니코드임 2Byte짜리 조심
* QLatin1Char/QLatin1String => US-ASCII/Latin-1 인코딩 문자열 지원을 위한 클래스(wchar)
* QLocal -> 사용 언어 분류 기준 => 언어 표현 방식에 맞도록 변환함
* QString -> 유니코드 문자열 캐릭터를 지원하는 클래스
#### QLatain1String vs QString
* 1byte vs 2byte => 두 개 다름
* 근데 둘 다 문자열 표현함
* Operator Overloading을 통해 Qt에서는 변환을 해 둠
* 데이터만 추출해 비교하는 형식으로
```cpp title="find_string"
QString str = "We must be <b>bold</b>, very **bold**"; 
int j = 0; while ((j = str.indexOf("<b>", j)) != -1) 
{ 
	qDebug() << "Found <b> tag at index position" << j; 
	++j; 
}
```
#### QTextStream
* 대량의 텍스트 데이터를 다루기 위해 STREAM 처리 방식 제공
* 로그 파일 까는데 용이함

#### QRegExp
* 정규식 표현 기능을 제공
```cpp
QRegExp rx("^\\d\\d?$"); // 0~99 의 정수값인 경우 
rx.indexIn("123"); // return -1 
rx.indexIn("-6"); // return -1 
rx.indexIn("6"); // return 0
```
-> 전화번호 검증과 같은 상황에서 주로 사용

##### QVariant
* 타입이 정해지지 않은 유형의 형변환을 도움
* 원하는 형태로 가공 가능
```cpp
QDataStream out(...); 
QVariant v(123); // int 형을 저장 
int x = v.toInt(); // x = 123 
out << v; 
v = QVariant("hello"); // QByteArray 타입의 문자열을 저장 
v = QVariant(tr("hello")); // QString 타입의 문자열을 저장 
int y = v.toInt(); 
QString s = v.toString(); 
out << v; 
... 
QDataStream in(...); 
in >> v; 
int z = v.toInt(); 
qDebug("Type is %s", v.typeName()); 
v = v.toInt() + 100; 
v = QVariant(QStringList());
```
## Container Class
#### QMap(/MultiMap)
* BST기반 템플릿
* 많이 씀..
* 정렬이 필요하면 해당 클래스 사용
* QHash에 비해 속도가 느림, 사용 방법 비슷
#### QHash(/MultiHash)
* 정렬이 안되어있음
* Hash Table 기반 Dictionary 제공 템플릿
* 속도가 QMap에 비해 빠름, 사용 방법 비슷
#### QPair
* Key-Value 형식이 아닌 쌍으로 아이템 데이터를 사용
* 쓰긴 하다만 보통 Hash, Map을 애용
#### List/LinkedList
* 단순 형태는 List, 대부분 next가 필요하기에 LinkedList 사용
* 발전된 형태의 Queue, Stack 등 존재
#### QSet
* 중복 불허
* 중복을 허용하지 않는 집합
* 해시 기반 검색
