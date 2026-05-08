## Thread Programming
* Thread : 프로그램의 흐름
* 멀티 윈도우 프로그램을 사용함에 있어 여러 윈도우를 사용
	* 프로그램도 동일하게 하나의 프로그레스에서 여러 개의 작업들을 실행
	* 이때 각 작업의 단위를 쓰레드라 표현
* 윈도우 프로그램 자체가 하나의 멀티 쓰레드(윈도우 여러 개 펼쳐 놓으시잖아)
* thread가 실행되기 위해선 CPU를 차지해야 함
	* CPU << 중요한 친구면 개추
	* CPU에 로딩, 로딩 후 작업 시작
* Thread Pool -> 여러 개의 객체들이 모여있는 대기 공간
	* Ready Pool -> 여러 개의 쓰레드가 생성, CPU 차지를 위해 대기하고 있는 장소 개념
	* 서로 Race Condition -> 자원 점유를 위한 경쟁 상태
	* 이 때 경쟁을 통제해야 함(할당 및 점유의 권한을 지닌 매니저 단계 필요)
		* 해당 역할은 OS에서 담당하고 있다 표현
	* 각 Thread에는 Priority를 지님 -> 동일한 Thread는 동일한 우선권을 지님
		* 세부적으로 따져 대기 시간순으로 우선권 재부여
		* 점유 및 할당 완료 시 Ready Pool에서 빠져나감
			* CPU를 할당하는 Thread를 Running Thread라 명칭
			* 한 번에 한 개의 Thread를 실행 상태로 갖게 된다
			* 얼마나 걸릴지 모름..
				* 작업이 끝나지 않더라도 할당 해제가 가능함
					* 일정량 이상(일정 시간)의 작업이 완료된 Thread를 Time out 됐다 표현
	* CPU는 일정 시간만 돌아가며 사용 가능하도록 되어있음
	* Time Out된 Thread는 다시금 Ready Pool로 이동 -> 우선순위 낮아짐
	* I/O 진행 시 생각보다 많은 시간 소요 -> I/O Blocking (CPU와 통신이 아닌 I/O 장비와 통신)
		* I/O Pool이 따로 있음 -> I/O 후 바로 CPU로 이동해 작업을 수행하는 것이 아닌 Ready Pool로 돌아가 대기
	* 종료된 Thread는 Dead Pool로 이동 => 메모리 할당 해제(종료)
##### Cycle
* Ready Pool -> Running Therad -> Time Out -> Ready Pool

#### Data Sharing
* 2개 이상의 Thread가 하나의 데이터(공유 자원 경쟁)에 접근을 함 -> 실행 순서에 따라 결과 값이 달라지는 현상 발생(Atomicity의 결여)
	* 데이터 보호를 위해 상호배제(Mutex)를 사용
		* 한 번에 하나의 스레드만 락을 획득, 자원에 접근하도록 제어
```cpp
m_mutex.lock();
...
m_mutex.unlock();
sleep(1);
```

#### Dead Lock
* 데이터 공유 문제를 해결 하기 위해 Lock을 과도하게 사용하거나 잘못 관리 한 경우
* 두 개 이상의 Thread가 서로 가진 락이 해제 되기를 기다리는 상태
	* 발생 조건 : Mutual Exclusion(Mutex), Hold and Wait, No Preemption, `Circular Wait`

