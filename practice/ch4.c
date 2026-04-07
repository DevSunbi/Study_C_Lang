#include <stdio.h>
#define _CRT_NO_SECURE_WARNING
int main(void) {
  char ch; // 문자 저장 변수

  printf("input string : "); // 입력 안내 메세지
  scanf("%c", &ch);          // 변수 ch에 문자 입력
  printf("%d\n", ch);        // 변환해서 출력
  return 0;
}