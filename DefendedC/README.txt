Updates:
java- math overflow printed out error message, now it outputs correct number.
output file cannot be the same as input file

C- revamped directory lock

Team:
Avery Scheiwiller
Andy Sorensen
Devan Gifford

Contact: teamnullpointerdejection@gmail.com

Java:
   Compiler: JDK 1.8.0_151-b12
   OS: Windows 10 Home
   IDE: NetBeans 8.2
   Instructions: Just compile and run using the given compiler/os. 
	

C: (Makefile provided)
   Compiler: GNU MinGW-w64 7.2.0 (Important!!)
   Link:https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.2.0/threads-win32/seh/x86_64-7.2.0-release-win32-seh-rt_v5-rev0.7z/download
   OS: Windows 10 Home
   IDE: NetBeans 8.2
   Compile commands: (Or run make w/ provided makefile)
	gcc -pedantic -Wall -Wextra -Werror -c -g -MMD -MP -MF "defendedCode.o.d" -o defendedCode.o defendedCode.c
	gcc -pedantic -Wall -Wextra -Werror -c -g -MMD -MP -MF "sha256.o.d" -o sha256.o sha256.c
	gcc -pedantic -Wall -Wextra -Werror -o defendedcode defendedCode.o sha256.o
   Instructions: Compile with the given compiler/os, run. (Correct makefile now provided)
	Note: You must have an input file within the program directory. Otherwise you won't be able to enter an input filename (as no valid filename exists).