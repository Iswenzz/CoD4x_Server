#!/bin/bash
echo -e "[+] Compile SR\n"
cmake --build src/SR/build

echo -e "[+] Compile CoD4x\n"
make

echo -e "[+] Copy Binary\n"
cp -v bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
