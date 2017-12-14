@REM gcc win32.c -lgdiplus -o win32.exe
windres -O coff win32.rc -o win32.res
tcc win32.c win32.res -lwinmm -o win32.exe
upx --ultra-brute -9 win32.exe
