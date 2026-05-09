#### 순차 탐색
* if문 사용해서 하나하나 탐색
* Worst O(N)

#### 이진 탐색
* 말은 쉬움 ㅋㅋ
* 정렬이 무조건 되어있어야 효율적
* sort 우선(Worst -> O(n^2)) => O(nlogn)을 써야 좀 먹을만함
* 범위가 축소된다..
	* 코드 구현 시 Mid / L / R 3가지 섹션으로 분할됨
	* Left = 0 / Right=9
	* == index\[0] Left, index\[9] Right
	* Mid 추측이 필요함(0-9 사이 수에서 3을 찾아보자)
		* ( Left + Right ) / 2 하면 나옴
		* 0-9 기준, Mid=4
		* 이후 findValue 기준으로 Mid와 비교, 작으면 Left, 크면 Right로 범위 축약
		* 이후 다시금 Mid 추측, Mid = 1
		* findValue 못찾음, Right 재탐색
		* 다시 Mid 추측, Mid = 2
		* 왜 아직도 3이 아닌가..
			* 결국 3 나옴
=> Worst = O(log2^n)