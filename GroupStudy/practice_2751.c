#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void bubble_sort(int *arr, int size);
void selection_sort(int *arr, int size);
void insertion_sort(int *arr, int size);

int main(void) {
  int arr[6] = {0};
  int size = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  bubble_sort(arr, size);
  selection_sort(arr, size);
  insertion_sort(arr, size);
}

void bubble_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
} // time complexity O(n^2) -> failed

void selection_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int min_idx = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[min_idx] > arr[j]) {
        min_idx = j;
      }
    }
    int tmp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = tmp;
  }
  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
} // time complexity O(n^2) -> failed

void insertion_sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int key = arr[i];
    int j = i - 1;
    for (; j >= 00 && arr[j] > key; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
  for (int i = 0; i < size; i++) {
    printf("%d\n", arr[i]);
  }
} // time complexity O(n^2) -> failed
