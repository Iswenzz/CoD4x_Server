@ECHO OFF
set PATH=C:\Dev\MinGW\bin;%PATH%

echo. & echo [+] Compile & echo.
mingw32-make

echo. & echo [+] Copy Binary & echo.
xcopy /FY "%~dp0\bin\cod4x18_dedrun.exe" "D:\Program Files (x86)\Activision\Cod4Mod\cod4x18_dedrun.exe"
