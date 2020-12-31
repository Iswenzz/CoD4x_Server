#!/bin/sh

echo Cleanup
rm *.o
rm *.so

echo Compiling: release
gcc -m32 -Wall -O1 -s -fvisibility=hidden -mtune=core2 -c *.c

echo Linking
gcc -m32 -s -shared -static-libgcc -static-libstdc++ -o antiadvert.so *.o libdre2_unix.a
