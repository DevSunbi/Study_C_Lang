#include <stdio.h>

int main(void) {
  int kor = 70;
  int eng = 80;
  int math = 90; // 세 과목의 변수 선언과 초기화
  int total;     // 총점을 저장할 변수 선언

  total = kor + math + eng; // 세 변수의 값을 더해 총점 변수에 저장
  printf("국어 : %d, 영어 : %d, 수학 : %d\n", kor, eng, math); // 점수 출력
  printf("총점 : %d\n", total);
  return 0; // 총점 출력
} // 국어 70 영어 80 수학 90 총점 240