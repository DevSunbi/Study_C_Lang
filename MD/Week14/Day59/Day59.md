#### review ftrace
![[Pasted image 20260622092444.png]]
* 해당 디렉터리의 파일들은 실제 디스크에 저장된 일반 파일이 아니라, 커널의 ftrace 기능을 제어하고 trace 결과를 조회하기 위한 가상 파일 인터페이스이다.
![[Pasted image 20260622092556.png]]
* 배포판 커널들
* ftrace 매핑이 안되어있을 때 -> `mount -t debugfs nodev /sys/kernel/debug`
![[Pasted image 20260622093519.png]]
-> 이벤트 => 서브시스템
![[Pasted image 20260622093540.png]]
* 서브시스템 안에 이벤트들이 포함되어 있음
https://www.kernel.org/doc/html/v6.12/trace/events.html
-> v6.12 ftrace docs 참고
#### 실습
![[Pasted image 20260622101017.png]]
-> 추적중인가? => 1-추적 0-멈춤
![[Pasted image 20260622101119.png]]
* 현재 설정되어 있는 추적기
![[Pasted image 20260622101137.png]]
* 사용 가능한 추적기들
* 이벤트만 추적 - nop
* 커널 함수 - function_graph, function
![[Pasted image 20260622101337.png]]
* set_ftrace_filter에 등록된 함수만 필터링해서 추적
* available_filter_functions 파일 열람을 통해 필터링 가능한 함수 목록 출력 가능
![[Pasted image 20260622101425.png]]
![[Pasted image 20260622102346.png]]
* 모듈 적재 전/후 diff로 비교 -> 함수 이름 파악, 후 필터 추가
## strace
![[Pasted image 20260622112133.png]]
* `write(4, "fopen: Permission denied\n", 25fopen: Permission denied` permission denied 부분 확인
* `openat(AT_FDCWD, "/etc/shadow", O_RDONLY) = -1 EACCES (Permission denied)`
![[Pasted image 20260622112745.png]]
* 네트워킹 strace
* ppoll 중임을 확인 가능
![[Pasted image 20260622112847.png]]
* 추가 연결 전 후 strace 결과
![[Pasted image 20260622112932.png]]
* 네트워크만 검출 시작
![[Pasted image 20260622113020.png]]
* 연결 전 후 결과
## uftrace
* Linux 환경에서 함수 호출 흐름(call graph)와 실행 시간(perfirmance)을 추적하는 도구
* 유저레벨 프로그램 뿐 아니라 커널 함수까지 추적 가능

| 함수 호출 흐름 추적          | 프로그램이 어떤 함수를 어떤 순서로 호출하는지 확인           |
| -------------------- | -------------------------------------- |
| 함수 실행 시간 측정          | 각 함수의 total/avg/min/max 실행 시간 분석       |
| argument/return 값 추적 | 함수 인자 및 반환값 확인 가능                      |
| filtering 기능         | 특정 함수만 추적<br>특정 라이브러리만 추적 <br>depth 제한 |
| flame graph 생성       | 병목 구간을 시각적으로 분석                        |
* uftrace 동작 방식
	* ptrace 기반
	* uprobes/kprobes 활용 가능
	* dwarf 심볼 기반으로 함수 이름 추출
	* 함수 진입/종료 시점에 timestamp 기록
* 기본 사용법

| 도구      | 명령     | 옵션                                                                                         |
| ------- | ------ | ------------------------------------------------------------------------------------------ |
| uftrace |        | 실행파일명<br>: 실행하면서 함수 호출 추적. 함수 단위 소요 시간 출력                                                  |
|         | record | -k 커널 내부 함수 호출<br>-a 매개변수와 전달되는 값도 모두 저장                                                   |
|         | replay | -D depth 함수 호출 depth<br>-F( ) 함수명 특정 함수 만 추적 (호출한 함수도 같이 출력) -t 시간<br>지정된 시간 이상 소요된 함수만 출력 |
|         | report | 수집된 데이터를 보고서 형태로 출력                                                                        |
![[Pasted image 20260622123631.png]]
![[Pasted image 20260622123650.png]]
![[Pasted image 20260622123825.png]]
-> a option 추가, replay 결과
=> 매개변수에 전달되는 값 저장 됐음을 확인
![[Pasted image 20260622123918.png]]
* k옵션 추가를 통해 커널 함수까지 포함된 결과 확인 가능
![[Pasted image 20260622124100.png]]
* a/k 옵션 모두 부여
![[Pasted image 20260622144803.png]]
-> system map 파일로 kernel function 디버깅
## OpenSSL
#### OpenSSL
* 오픈소스 프로젝트, 널리 사용되는 보안 및 암호화 라이브러리
* SSL(Secure Socket Layer) 및 TLS(Transport Layer Security) 프로토콜을 이용한 다양한 암호화 알고리즘 제공
* 신뢰성
	* 오픈소스
	* 광범위한 가용
	* 지속적인 업데이트 및 유지보수
* 대칭 키 암호화와 비대칭 키 암호화 방식 혼용하여 사용
![[Pasted image 20260622151156.png]]
![[Pasted image 20260622151616.png]]
#### OpenSSL 명령
* 버전 확인
	* openssl version
* 파일 암호화
	* openssl enc -aes -256 -cbc -e -in \[입력 파일 경로] -out \[출력 파일 경로]
* 파일 복호화
	* openssl enc -aes -256 -cbc -d -in \[암호화된 파일 경로] -out \[복호화된 파일 경로]
* 폴더 암호화
	* tar czv folder-name | openssl enx -aes-256-cdc-out
* 폴더 복호화
	* openssl enc -aes-256-cdc-d-in foldername.tar.gz.enc | tar xzv
* 인증서 생성 
	* 새로운 RSA 개인 키와 자체 서명된 인증서를 생성하는 명령으로 서버용 SSL/TLS 인증서를 만들 때 유용
	* `openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 `
* 공개 키와 개인 키 생성
	* `openssl genpkey -algorithm RSA -out private_key.pem`
	* RSA 알고리즘을 사용하여 새로운 개인 키를 생성,. 공개 키는 개인 키에서 파생
* 개인 키에서 공개 키 추출 
	* `openssl rsa -pubout -in private_key.pem -out public_key.pem `
	*  개인 키 파일에서 공개 키를 추출, 공개 키는 다른 사람들과 안전하게 공유 가능. 
* 파일 해시 값 생성
	* `openssl dgst -sha256 filename`
	* 파일의 SHA-256 해시를 생성하여 파일 무결성 검사나 디지털 서명 생성에 사용
* 디지털 서명 생성
	* `openssl dgst -sha256 -sign private_key.pem -out signature.bin file.txt`
	* 주어진 파일에 대한 디지털 서명을 생성하여 해당 파일의 무결성과 출처를 검증하는 데 사용.
* 디지털 서명 검증
	* `openssl dgst -sha256 -verify public_key.pem -signature signature.bin file.txt`
	* 디지털 서명이 유효한지 검증. 파일과 서명이 모두 제공되어야 함.
#### OpenSSL 명령
* SSL/TLS 연결 테스트
	* `openssl s_client -connect host:port`
	* 지정된 호스트와 포트에 대한 SSL/TLS 연결을 시도하여, 서버 설정을 테스트하거나 연결 문제를 진단
* 암호화 및 복호화 관련 함수

|함수|원형|역할|
|---|---|---|
|`AES_set_encrypt_key`|`int AES_set_encrypt_key(const unsigned char *userKey, const int bits, AES_KEY *key);`|AES 암호화 키를 설정하는 함수|
|`AES_set_decrypt_key`|`int AES_set_decrypt_key(const unsigned char *userKey, const int bits, AES_KEY *key);`|AES 복호화 키를 설정하는 함수|
|`AES_encrypt`|`void AES_encrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key);`|AES 암호화를 수행하는 함수|
|`AES_decrypt`|`void AES_decrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key);`|AES 복호화를 수행하는 함수|
* RSA 암호화 관련 함수

|함수|원형|역할|
|---|---|---|
|`RSA_generate_key_ex`|`int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *e, BN_GENCB *cb);`|RSA 키를 생성하는 함수|
|`RSA_public_encrypt`|`int RSA_public_encrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);`|RSA 공개키 암호화 수행|
|`RSA_private_decrypt`|`int RSA_private_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);`|RSA 개인키 복호화 수행|
* SSL/TLS 관련 함수

|함수|원형|역할|
|---|---|---|
|`SSL_library_init`|`int SSL_library_init(void);`|OpenSSL 라이브러리를 초기화하는 함수|
|`SSL_CTX_new`|`SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);`|SSL 컨텍스트를 생성하는 함수|
|`SSL_new`|`SSL *SSL_new(SSL_CTX *ctx);`|SSL 객체를 생성하는 함수|
|`SSL_set_fd`|`int SSL_set_fd(SSL *ssl, int fd);`|SSL 객체에 파일 디스크립터를 설정하는 함수|
|`SSL_accept`|`int SSL_accept(SSL *ssl);`|서버에서 SSL/TLS 핸드셰이크를 수행하는 함수|
|`SSL_connect`|`int SSL_connect(SSL *ssl);`|클라이언트에서 SSL/TLS 핸드셰이크를 수행하는 함수|
|`SSL_read`|`int SSL_read(SSL *ssl, void *buf, int num);`|SSL 연결에서 데이터를 읽는 함수|
|`SSL_write`|`int SSL_write(SSL *ssl, const void *buf, int num);`|SSL 연결에서 데이터를 쓰는 함수|
* X.509 인증서 관련 함수

|함수|원형|역할|
|---|---|---|
|`X509_new`|`X509 *X509_new(void);`|새로운 X509 인증서를 생성하는 함수|
|`X509_free`|`void X509_free(X509 *cert);`|X509 인증서를 해제하는 함수|
|`PEM_read_X509`|`X509 *PEM_read_X509(FILE *fp, X509 **x, pem_password_cb *cb, void *u);`|PEM 형식의 인증서를 읽는 함수|
|`PEM_write_X509`|`int PEM_write_X509(FILE *fp, X509 *x);`|PEM 형식으로 인증서를 저장하는 함수|
![[Pasted image 20260622153455.png]]
-> SSL/TSL 없이 만든 서버 => packet 받아보면 바로 보임
![[Pasted image 20260622154449.png]]
-> tls_server 실행 화면 => 복호화 돼서 패킷 내부 내용 확인 불가