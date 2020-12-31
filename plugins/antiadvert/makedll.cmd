@ECHO OFF

echo Cleanup
del *.o
del *.dll

echo Compiling: release
gcc -m32 -Wall -O1 -s -mtune=core2 -c *.c

echo Linking
gcc -m32 -s -shared -static-libgcc -static-libstdc++ -o antiadvert.dll *.o libdre2_win32.a -L..\ -lcom_plugin
