## IOMultiplexing - epoll
#### select / poll 문제점
* 동시 접속 수가 증가하면 문제 일어나기 시작

* select -> 프로세스 내의 모든 파일 디스크립터를 대상으로 하는 함수로 사용 예시
```c
while(1) {
	read_fds = mask;
	select(sd+1, &read_fds, NULL, NULL, NULL);	
}
```
* 첫 번째 인자는 파일(소켓) 디스크립터의 개수, 0부터 개수만큼 이벤트 발생했는지 각각 모니터링
* 3번/78번 발생 -> 0번부터 78번까지 모두 모니터 == 감지 시간 지연
* 오픈 되어있는 파일 또는 소켓이 수십 개 정도라면 감지 시간의 지연이 그리 크진 않지만 수 백개라면 상당히 길어짐
* 함수를 호출하기 앞서 항상 감지를 요청하는 파일 디스크립터들을 새로 등록해야 함
* 호출 시 전달하는 파일 디스크립터의 정보가 저장되지 않고 그 변수에 실제로 이벤트가 발생한 파일 디스크립터의 정보가 다시 저장되기 때문

* poll -> 이벤트를 감지하려는 파일 디스크립터만 모아 모니터링
```c
struct pollfd client_list[500];

while(1) {
	n = poll(client_list, max+1, 1000);
	if(client_list[0].revents & POLLIN) {
		socklen=sizeof(client_addr);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &socklen);
		for(i=1;i<MAX;i++) {
			if(client_list[i].fd < 0) {
				client_list[i].fd = client_sockfd;
				client_list[i].events = POLLIN;
				break;
			}
		}
	}
}
```
* client_list 배열이 이벤트 감지에 대한 정보 저장
* 수 십개 정도의 파일 디스크립터에 대한 정보가 모여 있는 경우 select에 비해 성능 우수
* 수 백 개의 파일 디스크립터 모니터링 시 select 함수와 큰 차이 없음
#### EPOLL
