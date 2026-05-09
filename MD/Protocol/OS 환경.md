### Non-OS부터 AUTOSAR까지
1. Non-OS(Bare-metal)
	운영체제 없이 무한 루프 내에서 코드가 직접 HW를 제어
	지연 시간(Latency)이 거의 없어 속도가 매우 빠르지만, 코드 관리 어려움

2. RTOS(Real-Time OS)
	일반 windows와 달리 결정론적 동작이 핵심
	어떤 작업이 정해진 시간 내에 끝나는 것을 보장

3. Embedded Linux 
	풍부한 라이브러리와 네트워크 스택을 활용할 때 쓰임
	주로 고성능 AP위에서 영상 처리나 커넥티드 카 기능 구현 시 사용

4. AUTOSAR(Automotive Open System Architecture)
	현대 자동차는 수십 개의 MCU가 통신
	각기 다른 제조사의 부품들이 서로 잘 통신하고
	HW가 바뀌어도 SW를 재사용 할 수 있게 만든 자동차 전용 표준 플랫폼

