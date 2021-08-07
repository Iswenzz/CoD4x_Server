#!/bin/bash
echo -e "[+] Compile\n"
make

echo -e "[+] Copy Binary\n"
cp bin/cod4x18_dedrun /home/cod4/cod4x18_dedrun && chmod u+x /home/cod4/cod4x18_dedrun
