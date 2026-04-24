#include <stdio.h>
#include <stdlib.h>

int A[100005];

int compare(const void *a, const void *b) {
  if (*(int *)a > *(int *)b)
    return 1;
  else if (*(int *)a < *(int *)b)
    return -1;
  else
    return 0;
}

int binarySearch(int n, int target) {
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    int middle = (left + right) / 2;
    if (A[middle] > target) {
      right = middle - 1;
    } else if (A[middle] < target) {
      left = middle + 1;
    } else {
      return 1;
    }
  }
  return 0;
}

int main() {
  int N, M, target;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  qsort(A, N, sizeof(int), compare);

  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int x;
    scanf("%d", &x);
    if (binarySearch(N, x)) {
      printf("1\n");
    } else {
      printf("0\n");
    }
  }
}