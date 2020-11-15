#ifndef ASYNC_SOCKET_H
#define ASYNC_SOCKET_H
#include "config.h"

typedef void (*on_accept_func)();
typedef void (*on_data_func)();
typedef void (*on_error_func)();

int async_listen(char *host, char *port, int listen_backlog);
void async_set_on_accept(on_accept_func on_accept);
void async_set_on_data(on_data_func on_data);
void async_set_on_error(on_error_func on_error);
void async_loop_block();

#endif
