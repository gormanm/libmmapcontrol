#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <sys/mman.h>

bool symbols_loaded;
static int (*_select)(int nfds, fd_set *readfds, fd_set *writefds,
			fd_set *exceptfds, struct timeval *timeout);

static void load_symbols()
{
	void *handle;

	if (symbols_loaded)
		return;

	handle = dlopen("libc.so.6", RTLD_LAZY);
	if (!handle) {
		perror("dlopen");
		abort();
	}

	dlerror();
	_select = dlsym(handle, "select");
	if (dlerror()) {
		perror("dlsym");
		abort();
	}

	symbols_loaded = true;
}

/* Force select to timeout */
int select(int nfds, fd_set *readfds, fd_set *writefds,
			fd_set *exceptfds, struct timeval *timeout)
{
	load_symbols();
	if (!timeout->tv_sec && !timeout->tv_usec)
		timeout->tv_usec = 10000;

	return (*_select)(nfds, readfds, writefds, exceptfds, timeout);
}
