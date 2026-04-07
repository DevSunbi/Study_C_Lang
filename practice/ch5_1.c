#include <stdio.h>
#define _CRT_NO_SECURE_WARNING

int main(void) {
  double a = 4.0, b = 1.2;
  printf("%.1f + %.1f = %.1f\n", a, b, a + b);
  printf("%.1f - %.1f = %.1f\n", a, b, a - b);
  printf("%.1f * %.1f = %.1f\n", a, b, a * b);
  printf("%.1f / %.1f = %.1f\n", a, b, a / b);
  // double형이므로 소수점까지 계산
  // 소수점 이하 첫째 자리까지 출력해야 하므로 % 다음에 .1을 사용한다
  return 0;
} // 실행 결과 4.0+1.2=5.2 4.0-1.2=2.8 4.0*1.2=4.8 4.0/1.2=3.3