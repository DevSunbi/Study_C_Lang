#include <stdio.h>

int main(void) {
  int a, b, tot;
  double avg;

  printf("two subject's score : ");
  scanf("%d %d", &a, &b); // 점수 입력
  tot = a + b;
  avg = tot / 2.0;
  printf("avg : %lf\n", avg);
  return 0;
} // 두 과목의 점수 : 70 85, 평균 : 77.5