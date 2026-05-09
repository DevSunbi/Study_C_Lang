.global _start              @ 시작 심볼(_start)을 외부에 공개
.text                       @ 코드(텍스트) 섹션
_start:                     @ 프로그램 시작
    MOV R0, #1              @ R0 = 1 (현재 검사할 숫자: 1부터 100까지)
    MOV R1, #1              @ R1 = 1 (3으로 나눈 나머지 카운터: 1,2,3 반복)

loop:                       @ 메인 루프
    CMP R0, #101            @ R0가 101인지 비교(= 100까지 실행)
    BEQ end_program         @ R0 == 101이면 종료

    CMP R1, #3              @ R1이 3인지 비교(= 현재 R0가 3의 배수 타이밍)
    BEQ multiple_of_3       @ R1 == 3이면 3의 배수 처리로 분기

    ADD R0, R0, #1          @ R0++ (다음 숫자)
    ADD R1, R1, #1          @ R1++ (나머지 카운터 진행: 1->2->3)
    B loop                  @ 루프 계속

multiple_of_3:              @ R0가 3의 배수일 때 처리
    @ TODO: 여기서 LED 출력 등 "배수일 때" 동작 수행
    ADD R0, R0, #1          @ R0++ (다음 숫자)
    MOV R1, #1              @ R1을 1로 리셋(다음 사이클 시작)
    B loop                  @ 루프 계속

end_program:                @ 종료
    BX LR                   @ 호출자에게 복귀(환경에 따라 종료 처리 필요)
