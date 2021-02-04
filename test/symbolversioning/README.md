# symbolversioning

An example of Linux/glibc symbol versioning.

# demo:

$ make 
rm -f libfoo.1.so
cc foo.c -g -Wl,--version-script=symver.map -fpic -o libfoo.1.so -Wl,-soname,libfoo.so -shared
rm -f libfoo.so
ln -s libfoo.1.so libfoo.so
cc caller.c -g -Wl,-rpath,`pwd` -o caller1 -lfoo -L.

$ ./caller1 
foo@@V1: 1

$ nm caller1 | grep foo
                 U foo@@MYSTUFF_1.1
$ make v2
rm -f libfoo.2.so
cc foo.2.c -g -Wl,--version-script=symver.2.map -fpic -o libfoo.2.so -Wl,-soname,libfoo.so -shared
rm -f libfoo.so
ln -s libfoo.2.so libfoo.so
cc caller.2.c -g -Wl,-rpath,`pwd` -o caller2 -lfoo -L.

$ ./caller1
foo@@V1: 1

$ ./caller2
foo@@V2: 1 2
$ nm caller2 | grep foo
                 U foo@@MYSTUFF_1.2
