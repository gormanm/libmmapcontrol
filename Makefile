all: libmlockall.so libmappopulate.so libselecttimeout.so

libmlockall.so: Makefile libmlockall.c
	${CC} -Wall -O2 -fPIC -shared -Wl,-soname,libmlockall.so -o libmlockall.so -lc libmlockall.c

libmappopulate.so: Makefile libmappopulate.c
	${CC} -Wall -O2 -fPIC -ldl -shared -Wl,-soname,libmappopulate.so -o libmappopulate.so -lc libmappopulate.c

libselecttimeout.so: Makefile libselecttimeout.c
	${CC} -Wall -O2 -fPIC -ldl -shared -Wl,-soname,libselecttimeout.so -o libselecttimeout.so -lc libselecttimeout.c

clean:
	rm -f *.o lib*.so*
