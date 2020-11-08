#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>

static char doc[] = "aion - fast and simple timeseries database";
const char *argp_program_version = "aion 0.0.1";
const char *argp_program_bug_address = "<magicforesterrors@gmail.com>";
static struct argp_option options[] = {
	{ "host", 'h', "host", 0, "Bind host" },
	{ "port", 'p', "port", 0, "Bind port" },
	{ "data-dir", 'd', "", 0, "Data dir (TBD)" },
	{ "config-file", 'c', "", 0, "Config file (TBD)" },
	{ "pid-file", 'l', "", 0, "pid file path to lock" },
	{ 0 }
};

struct arguments {
	char *bind_host;
	int bind_port;
	char *data_dir;
	char *config_file;
	char *pid_file;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
	struct arguments *arguments = state->input;
	switch (key)
	{
		case 'h':
			arguments->bind_host = arg;
			break;
		case 'p':
			arguments->bind_port = arg ? atoi(arg) : 1895;
			break;
		case 'd':
			arguments->data_dir = arg;
			break;
		case 'c':
			arguments->config_file = arg;
			break;
		case 'l':
			arguments->pid_file = arg;
			break;
		case ARGP_KEY_END:
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

void fail(char *msg, int code) {
	syslog(LOG_ERR, "%s - %s", msg, strerror(code));
	exit(code);
}

void daemonize() {
	umask(0);
	pid_t pid = fork();
	if (pid < 0) 
		fail("Cannot fork", 1);
	if (pid > 0)
		exit(EXIT_SUCCESS);

	// ignore the result as it can fail when already a session leader - see man 2 setsid.
	// also ignore sighup because it's sent when session leader dies (also see man)
	setsid(); 
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		fail("Cannot ignore SIGHUP", 3);

	pid = fork();
	if (pid < 0) 
		fail("Cannot fork", 4);
	if (pid > 0)
		exit(EXIT_SUCCESS);

	if (chroot("/") != 0) 
		fail("Cannot chroot", 5);

	struct rlimit rl;
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0 || rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (rlim_t i = 0; i < rl.rlim_max; i++)
		close(i);
	int fd0 = open("/dev/null", O_RDWR);
	int fd1 = dup(fd0);
	int fd2 = dup(fd0);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "Cannot assign stdout, stderr, stdin to /dev/null = 0=%d,1=%d,2=%d", fd0, fd1, fd2);
		exit(6);
	}
}

void ensure_one_process(char *pid_file) {
	int fd = open(pid_file, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if (fd < 0)
		fail("Cannot create pid file", 7);
	struct flock fl;
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	if (fcntl(fd, F_SETLK, &fl) < 0)
		fail("Cannot acquire lock on a pid file", 8);
	
	if (ftruncate(fd, 0) < 0)
		fail("Cannot truncate pid file", 9);
	char buf[19];
	sprintf(buf, "%ld", (long)getpid());
	int bytes = strlen(buf) + 1;
	if (write(fd, buf, bytes) != bytes)
		fail("Cannot write my pid into pid file", 10);
}

static struct argp argp = { options, parse_opt, 0, doc };

int main(int argc, char **argv) {
	openlog("aion", LOG_CONS, LOG_DAEMON);
	struct arguments arguments;
	arguments.bind_host = "0.0.0.0";
	arguments.bind_port = 189008;
	arguments.config_file = "/etc/aion.conf";
	arguments.data_dir = "/var/aion/";
	arguments.pid_file = "/var/run/aion.pid";
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	daemonize();
	ensure_one_process(arguments.pid_file);
	syslog(LOG_INFO, "aion is started");
	// epoll loop
	while(1) {

	}
}
