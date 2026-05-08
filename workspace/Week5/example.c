int main()
{
	int i = 10;
	int j = i + 11;
	return 0;
}
/* ASM 변환 예제
.text

main:
	mov R0, #10
	mov R1, #11
	add R0, R0, R1
	bx lr
.end
*/