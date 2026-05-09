#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

int Sum(int* arr, int n) // 시간 복잡도 : O(1)
{
	int sum = 0;

	for (int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

int RecurSum(int* arr, int n) // 시간 복잡도 : O(n)
{
	/* 힌트: 역순으로 더하기 (매개변수에 시작 인덱스를 추가하지 않아도 되기 때문)
	  (1 + 2 + ... 8 + 9 + 10)
	= (1 + 2 + ... 8 + 9) + 10
	= ((1 + 2 + ... 8) + 9) + 10
	= ...
	*/
	
	if (n == 0)
		return 0;
	
	cout << arr[n - 1];
	if (n > 1)
		cout << " + ";
	else
		cout << endl;

	return arr[n - 1] + RecurSum(arr, n - 1);
} 

int main()
{
	// Sum vs RecurSum

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << Sum(arr, n) << endl;
	cout << RecurSum(arr, n) << endl;

	return 0;
}
