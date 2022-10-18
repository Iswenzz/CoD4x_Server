#!/bin/bash
echo -e "[+] Compile SR\n"
cmake --build src/SR/build

echo -e "[+] Compile CoD4x\n"
mingw32-make

echo -e "[+] Copy Binary\n"
cp -v bin/cod4x18_dedrun.exe "/d/Program Files (x86)/Activision/Cod4Mod"
