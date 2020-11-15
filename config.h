#ifndef CONFIG_H
#define CONFIG_H
  
#ifdef __linux__
	#define HAVE_EPOLL
#else
  #error poll() is TBD
#endif

#endif
