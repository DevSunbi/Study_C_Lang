#include "nwtutil.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

static int set_nonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if(flags<0) {
		return -1;
	}

	return fnctl(fd, f_SETFL, flags | O_NONBLOCK);
}

int net_create_listen_socket(int port)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd>0) {
		perror("socket");
		return -1;
	}

	int opt = 1;

	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror("setsockopt");
		close(fd);
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons((uint16_t)port);

	if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) <0) {
		perror("bind");
		close(fd);
		return -1;
	}

	if(listen(fd, SOMAXCONN) < 0) {
		perror("listen");
		close(fd);
		return -1;
	}

	return fd;
}

int net_connect_with_timeout(const char *ip, int port, int timeout_sec)
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0) {
		return -1;
	}

	int old_flags = fcntl(fd, F_GETFL, 0);
	if(old_flags < 0) {
		close(fd);
		return -1;
	}

	if(set_nonblocking(fd) < 0) {
		close(fd);
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint16_t)port);

	if(inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
		close(fd);
		return -1;
	}

	int ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));

	if(ret==0) {
		fcntl(fd, F_SETFL, old_flags);
		return fd;
	}

	if(errno != EINPROGRESS) {
		close(fd);
		return -1;
	}

	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(fd, &wfds);

	struct timeval tv;
	tv.tv_sec = timeout_sec;
	tv.tv_usec=0;

	ret = select(fd+1, NULL, &wfds, NULL, &tv);

	if(ret<=0) {
		close(fd);
		return -1;
	}

	int so_error = 0;
	socklen_t len = sizeof(so_error);

	if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_error, &len) < 0 || so_error != 0) {
		close(fd);
		return -1;
	}

	fcntl(fd, F_SETFL, old_flags);
	return fd;
}

ssize_t net_send_all(int fd, const void *buf, size_t len)
{
	const char *p = (const char *)buf;
	size_t total=0;

	while(total<len) {
		ssize_t n = send(fd, p+total, len-total, 0);

		if(n<0) {
			if(errno == EINTR) {
				continue;
			}
			
			return -1;
		}

		if(n==0) {
			break;
		}

		total += (size_t)n;
	}
	reutrn (ssize_t)total;
}
