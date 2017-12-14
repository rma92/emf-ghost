# emf-ghost
Joke software that plays the Lavender Town / Shion Town theme and moves
a window containing a picture of a ghost around the screen.

# Use instructions
Run the app.  It disables the close button, resizes the window, and 
starts playing the music while moving around the screen.

To close it, hit Alt+F4 with the window focused.

# Compilation instructions
The default build configuration uses:
-Tiny C Compiler (tcc.exe)
-Windres.exe from MinGW
-UPX.exe
and expects these items to be in the path.

The relevant commands are in build.cmd, which should be edited to
suit your needs.

The program expects to have the image, and sound files stored as
resources.  This requires compiling the resource script (rc) file along
with the resources using a resource compiler, and then passing that on
to the compiler.

The code must then be compiled, and linked with the winmm library to 
facilitate playing music.

The executable is then UPXed to minimize the size of the resulting 
binary.  This is entirely optional.

## Compiling resources
This is accomplished using windres from MinGW.

`windres -O coff win32.rc -o win32.res`

## Compiling and linking executable
This is accomplished using tiny c compiler by default to minimize the
size of the resultant binary, as performance is not critical either.

`tcc win32.c win32.res -lwinmm -o win32.exe`

TCC automatically links against gdi32.

GCC can be used as well.

`gcc win32.c win32.res -lwinmm -lgdi32 -o win32-gcc.exe`

## UPX
UPX is used to shrink the resulting binary for more efficient distribution.
This step is entirely optional.

`upx --ultra-brute -9 win32.exe`


