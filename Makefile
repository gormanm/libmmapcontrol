all: libmlockall.so libmappopulate.so

libmlockall.so: Makefile libmlockall.c
	${CC} -Wall -O2 -fPIC -shared -Wl,-soname,libmlockall.so -o libmlockall.so -lc libmlockall.c

libmappopulate.so: Makefile libmappopulate.c
	${CC} -Wall -O2 -fPIC -ldl -shared -Wl,-soname,libmpopulate.so -o libmappopulate.so -lc libmappopulate.c

clean:
	rm -f *.o lib*.so*
