
CFLAGS += -g

all : v1

v1: libfoo.1.so caller1
v2: libfoo.2.so caller2

libfoo.1.so: foo.c
	rm -f $@
	$(CC) $^ $(CFLAGS) -Wl,--version-script=symver.map -fpic -o $@ -Wl,-soname,libfoo.so -shared
	rm -f libfoo.so
	ln -s libfoo.1.so libfoo.so

caller1: caller.c
	$(CC) $^ $(CFLAGS) -Wl,-rpath,`pwd` -o $@ -lfoo -L.

libfoo.2.so: foo.2.c
	rm -f $@
	$(CC) $^ $(CFLAGS) -Wl,--version-script=symver.2.map -fpic -o $@ -Wl,-soname,libfoo.so -shared
	rm -f libfoo.so
	ln -s libfoo.2.so libfoo.so

caller2: caller.2.c
	$(CC) $^ $(CFLAGS) -Wl,-rpath,`pwd` -o $@ -lfoo -L.

clean:
	rm -f *.so *.o caller1 caller2
