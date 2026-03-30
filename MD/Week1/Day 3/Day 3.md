## HyperLink
* [[MD/Week1/Day 3/CodeBase|CodeBase]]
* [[MD/Week1/Day 3/QnA|QnA]]
---
## 데이터 입력
### scanf
* 변수 및 adress 이해 필수 => 포인터 개념이 일부 필요
* scanf("%d", &a); => &a : 인자의 주소값 전달
* main함수에서 a라는 공간 할당(User Program) => Stack 공간 할당
	* 함수 호출 -> 함수로 제어권 넘김 -> 새로 호출된 func의 Stack 공간 생성(local val 등 생성)
	* scanf 호출 -> main함수에서 scanf 만나는 point 저장, scanf로 점프 후 실행 준비
	* 함수마다 본인의 Stack 공간 있음 -> 함수만의 변수 제어 공간, 할당된 공간에만 접근 가능
	* Stack 공간 할당 후 Segment Mapping(인자 전달) 수행
	* & -> 뒤 따라오는 변수의 메모리 주소를 지시
		* 각 메모리에 고유한 주소 값 존재 => 각 함수는 local value를 모르니 주소 참조
![[Pasted image 20260325101623.png]]
* 가변 길이 인자 존재, 포인터 존재 => 가변 길이 인자의 주소를 참조(실제로는 포인터 들어감)
	* 포인터 변수 사용 -> 포인터 주소를 사용해 타 함수의 변수에 간접적으로 접근
	* \*p1 = n; => n 주소 접근, p1의 값을 바꾸면 n의 값이 변동(주소 변동)
	* OS 내부에서도 포인터를 통해 연결
		* 키보드 input -> scan code 작동 -> 해당 Data가 OS Buffer로 전달 및 기록 -> Enter가 Buffer(1, 2, 3, Enter) 적재 -> User Program으로 들어가야하는데.. scanf가 받음 => 결국 포인터를 통해 변수 주소 간접 접근 -> 변수 입력
	* scanf 작동 끝나면 Stack 공간 할당 해제 -> save point로 재진입 후 main func 진행
* &a가 아닌 a를 전달 -> 주소가 아닌 저장 값이 넘어감 -> 주소 값 변화 -> 권한 없는 주소 접근 가능성 존재 => 문제 발생(Segment Fault)
* 변수에 & 붙이면 포인터 변수와 호환 가능
* 배열은 포인터 변수와 동격 (배열에는 & 안써도 됨, 배열 명은 주소와 동격)
---
## 연산자
* Operand 2개 -> Bin 연산자
* 대입 연산자의 우선순위가 가장 낮음
* 전위 연산자 -> 단독은 아무 차이 없음
* 후위 연산자 -> 단독은 아무 차이 없음
* 먼저 증가 후 계산, 먼저 계산 후 증가 차이 존재
* 특정 공간에 연산 값 저장됨 -> 영구 지속이 아닌 임시 공간에 저장, 사용 안하면 휘발
* C언어에 Boolean 없음 -> 0이 F, 그 외 T로 판별

#### 형 변환 연산자
* 연산할 때 피연산자의 형태가 다르면 자동으로 일치 -> 정수 + 실수 => 실수 + 정수
* 형 변환 연산자는 피 연산자의 값을 원하는 형태로 변환
* 명시적 형변환 -> (datatype) identifier

#### 비트 연산자
* 논리곱/논리합 
* <<, >> Bit Shift 연산자
* 연산자 우선 순위 => 대개 좌측이 우선(동일 기준)
* 대입 연산자 우선 순위 -> 수식의 결과를 공간에 넣음 => 우측 우선
* 우선순위 변동 => ( ) 사용 시 
* 극한으로 밀어버리면 Sign Bit 건들 가능서 ㅇ존재
---
## 선택문(분기문)
#### if
* 중첩 반복문 사용 -> 실행 효율의 증진 효과
	* 여러 분기 검사의 횟수를 줄일 수 있다

#### switch
* 특정한 조건에 특정한 값에 mapping
* switch-case 문에서 조건에는 변수 가능, case에는 상수 형태만 존재 가능
* 조건과 case는 동일한 type 이여야 함
* break가 없으면 모든 문장 실행
---
## 반복문
#### while문
* while 내 조건문이 참인 동안 내부 실행문 실행
* 조건문이 F면 내부 실행문 실행 안할 경우 존재
* while( 조건문 ){ 반복문 } 형태를 취함

#### do-while문
* 최소 1번은 실행(do 문) -> 이후 마지막 단락 while문의 조건 성립 여부 판단 후 반복 결정
* do { 반복문 }while( 조건문 ) 형태를 취함

#### for문
* 보통 배열과 함께 사용한다 생각하는게 좀 더 편함
* for( 초기식; 조건식; 증감식 ) => 내부 식은 인덱스 변수라 명칭 
	* 위 형태를 취함
	* 초기식 최초 한 번만 실행
	* 조건식 참이면 반복문 실행
	* 반복문 실행 후 증감식으로 올라감

#### 중첩 반복문
* func block 내부에 index value가 선언 되어있으면 해당 block 안에서만 사용(Scope Rule)
* break -> break문과 가장 가까운 block을 탈출
* continue -> 반복문의 일부를 건너 뜀 => 블록의 끝으로 간 후 다시 반복

#### 무한 반복문
* while(1) => 항상 참임 조건문 부정이 없으니 무한 반복
* for(;;) => 조건문 도달 조건 없음 무한 반복
---
## 함수
#### 함수 정의
* 함수명, 매개변수, 반환형으로 함수 원형 만듦
	* 함수명 : 함수의 기능에 맞는 이름
	* 매개변수 : 함수가 기능을 수행하는 데 필요한 데이터
	* 반환형 : 함수가 수행된 후 의 결과
	* ```C
	  int sum(int x, int y)
	  {
		  int temp; 
		  temp = x + y;
		  return temp;
	  }
	  ```
* 함수 정의 시 선정의 필요(main 함수 상단에 정의 필요함)
	* 어? int add(param)은 되는데요? => 컴파일러에서 암시적 선언(int겠거니)를 수행
	* 하지만 double, 구조체인 경우는 큰 문제 야기 가능, 선정의(prototype) 필요
* 형식 인자의 변수 명은 구태여 기재 할 필요는 없음(Prototype에서)
	* 쓰는 것을 권장

### 별개(User Program Area)
#### Code Segment
* 컴파일 후 Link에 의해 .exe로 만들어 졌을 때 bin로 구성, 실 코드가 올라가는 공간
* .exe 파일 실행 시 OS가 읽을 때 가장 먼저 띄움 => main func 바로 호출(invoke main)
* main 함수부터 실행, 이 때 Data Segment를 본다

#### Data Segment(실습 8기준 설명)
* Stack
* Heap
* Static(Global)
* Stack 공간 -> func별로 생성(func들 만의 공간 할당)
	* 제일 먼저 main stack 공간 할당 => Parameter : void -> pass
	* main 함수 하향식 구문 분석 시작
		* 내부 선언 변수(local 변수) 공간 할당 e.g) int a, int b, int result ...
	* sum func 도달(동시에 save point 지정) => sum func의 stack 공간 할당
		* 내부 선언 변수 x, y 공간 할당(main func으로부터 Parameter Passing)
	* call by value -> caller의 인자를 그대로 전달
	* return by value -> call by value로 왔던 것이 함수 내부 연산 후 인자 리턴
		* 리턴 후 함수의 할당 Stack 해제
	* 이후 main func 진행 => main func 종료 후 stack 공간 할당 해지
	* Code Segment의 .exe도 할당 해제





