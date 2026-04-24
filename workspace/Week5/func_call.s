.arm // arm으로 시작
.text // 텍스트 코딩 시작(.end까지)
//명령어 순차 실행
.global main // program의 entry point
.type main, %function // main의 type def

main: // main문 시작
	
	bl factorial
	bx lr //함수 종료 후 return(link register -> return func addr 들어가 있음)

.global factorial
.type factorial, %function
factorial:
	
.end//끝