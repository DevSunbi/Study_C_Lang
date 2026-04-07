#include <stdio.h>

int main(void) {
  int kor = 3, eng = 5, math = 4; // 국어, 영어, 수학의 학점 초기화
  int total = 0;                  // 전체 학점을 저장할 변수
  double result = 0;              // 연산 결과를 저장할 변수
  double kor_s = 3.8, eng_s = 4.4, math_s = 3.9; // 각 과목의 평점 초기화
  total = kor + eng + math;                      // 전체 학점 계산
  result = (kor_s + eng_s + math_s) / 3.0;       // 평점의 평균 계산
  result = (total >= 10 && result > 4.0);        // 전체 학점이 10학점 이상이고
  printf("result : %d\n", result); // 평점 평균이 4.0보다 크면 참이므로 결과는
                                   // 1, 그렇지 않으면 거짓이므로 결과는 0
  return 0;
}