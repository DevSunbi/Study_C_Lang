// selection sort time complexity : all n^2

#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

struct Element {
  int key;
  char value;
};

bool CheckSorted(int *arr, int size) {
  // TODO: 정렬 확인 함수 구현
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }

  return true;
}

void Print(int *arr, int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

void Print(Element *arr, int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i].key << " ";
  cout << endl;

  for (int i = 0; i < size; i++)
    cout << arr[i].value << " ";
  cout << endl;
}

int main() {
  // 5개라면? 더 많다면?
  {
    // 8 4 2 8 3
    // TODO: ???
    int num[6] = {8, 4, 2, 8, 3};
    int size = sizeof(num) / sizeof(num[0]);
    int minnum = num[0];
    for (int i = 0; i < size; i++) {
      if (num[i] < minnum) {
        minnum = num[i];
      }
    }

    // 8 3 2 5 1 1 2 5 8 9
    // TODO: ???

    // 100개라면?
  }

  // 가장 작은 수 찾기
  {
    int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9}; // 임의의 숫자들, 변경 가능
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(size > 0); // size가 1이상이라고 가정

    // TODO:

    // cout << "Minimum number is " << min_number << endl;
  }

  // 가장 작은 수의 인덱스 찾기
  {
    int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(size > 0); // size가 1이상이라고 가정

    // TODO:
    int min_index = 0;
    for (int j = 1; j < size; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    // cout << "The index of min is " << min_index << endl;
    // cout << "Minimum number is " << arr[min_index] << endl;
  }

  // Selection Sort
  // 힌트: swap()
  {
    int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    int min_index;
    for (int i = 0; i < size - 1; i++) {

      // TODO:
      min_index = i;
      for (int j = i + 1; j < size; j++) {
        if (arr[j] < arr[min_index]) {
          min_index = j;
        }
      }
      swap(arr[i], arr[min_index]);

      Print(arr, size);

      cout << boolalpha;
      cout << CheckSorted(arr, size);
      cout << endl;
    }
    return 0;
  }

  // 비교 횟수 세보기, 더 효율적인 방법은 없을까?
  // https://en.wikipedia.org/wiki/Sorting_algorithm
  {
    ofstream ofile("log.txt");
    for (int size = 1; size < 1000; size++) {
      int count = 0;
      int *arr = new int[size];
      for (int s = 0; s < size; s++) {
        arr[s] = size - s;
      }

      // TODO: count ++;

      // cout << size << ", " << count << endl;
      ofile << size << ", " << count << endl;
      // Print(arr, size);

      delete[] arr;
    }

    ofile.close();
  }

  // [2, 2, 1]
  // [1, 2, 2] // 첫 2가 마지막으로 이동

  // 안정성 확인(unstable)
  {
    Element arr[] = {{2, 'a'}, {2, 'b'}, {1, 'c'}};
    int size = sizeof(arr) / sizeof(arr[0]);

    Print(arr, size); // arr이 Element의 배열

    // TODO:

    Print(arr, size); // arr이 Element의 배열
  }
}