#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <sys/mman.h>

bool symbols_loaded;
static void *(*_mmap)(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
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
	_mmap = dlsym(handle, "mmap");
	if (dlerror()) {
		perror("dlsym");
		abort();
	}

	symbols_loaded = true;
}

/* Prepopulate anonymous writable mappings */
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	load_symbols();
	if ((prot & (PROT_READ|PROT_WRITE)) == (PROT_READ|PROT_WRITE) &&
	    (flags & (MAP_PRIVATE|MAP_ANONYMOUS)) == (MAP_PRIVATE|MAP_ANONYMOUS) &&
	    fd == -1)
		flags |= MAP_POPULATE;

	return (*_mmap)(addr, length, prot, flags, fd, offset);
}
