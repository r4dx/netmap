#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void fail(const char *msg, int code) {
	syslog(LOG_ERR, "%s (last errno='%s')", msg, strerror(errno));
	exit(code);
}
