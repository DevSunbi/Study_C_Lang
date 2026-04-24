.global _start              @ 시작 심볼(_start)을 외부에 공개
.text                       @ 코드(텍스트) 섹션
_start:                     @ 프로그램 시작
    MOV R0, #1              @ R0 = 1 (1부터 100까지 검사할 현재 값)

loop_numbers:               @ 메인 루프
    CMP R0, #101            @ R0가 101인지 비교(= 100까지 실행)
    BEQ end_program         @ R0 == 101이면 종료

    MOV R1, R0              @ R1 = R0 (3으로 나눈 나머지 계산용)

check_multiple:             @ 3을 반복해서 빼며 나머지 계산
    CMP R1, #3              @ R1과 3 비교
    BLT not_multiple        @ R1 < 3이면 감산 종료(나머지 후보)
    SUB R1, R1, #3          @ R1 -= 3
    B check_multiple        @ 반복

is_multiple:                @ R0가 3의 배수일 때 처리(나머지 0)
    @ led 출력              @ TODO: LED 출력 동작을 여기서 수행
    B next_number           @ 다음 숫자로

not_multiple:               @ R1 < 3인 상태에서 나머지 확인
    CMP R1, #0              @ 나머지가 0인지 확인
    BEQ is_multiple         @ 0이면 3의 배수

next_number:                @ 다음 값으로 진행
    ADD R0, R0, #1          @ R0++
    B loop_numbers          @ 루프 계속

end_program:                @ 종료
    BX LR                   @ 호출자에게 복귀(환경에 따라 종료 처리 필요)
.end                        @ 소스 끝
