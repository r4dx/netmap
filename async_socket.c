#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "fail.h"

#ifdef HAVE_EPOLL
#include "async_socket_epoll.c"
#endif


int async_listen(char *host, char *port, int listen_backlog) {
	struct addrinfo *res;
	int r = getaddrinfo(host, port, 0, &res);
	if (r != 0) 
		fail(gai_strerror(r), 101);
	int fd = -1;
	for (struct addrinfo *cur = res; cur != 0; cur = cur->ai_next) {
		fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
		if (fd == -1)
			continue;
		if (bind(fd, cur->ai_addr, cur->ai_addrlen) == 0)
			break;
		close(fd);
		fd = -1;
	}
	freeaddrinfo(res);
	if (fd == -1)
		fail("Cannot init/bind socket", 102);

	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0)
		fail("Cannot set listen socket to be nonblocking", 103);
	if (listen(fd, listen_backlog) != 0)
		fail("listen() has failed", 104);
	return fd;
}
