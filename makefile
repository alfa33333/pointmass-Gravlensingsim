# description: Compiles the lens and the library
#

CC = g++

# this line gives compiler optimizations that are geared towards g++ and Pentium4 
# computers. Comment it out if you don't have a Pentium 4 (or Athlon XP) or up

# CFLAGS = -O3 -Wno-deprecated -mcpu=pentium4 -march=pentium4 \
# -mfpmath=sse -msse -mmmx -msse2 -pipe -fomit-frame-pointer -s 

# Uncomment these two lines to use with any Pentium with MMX or up.

# CFLAGS = -Wno-deprecated -mcpu=pentium -march=pentium -pipe \
# -fomit-frame-pointer -mmmx -funroll-all-loops -s

# Uncomment these lines for some "safe" optimization flags

CFLAGS = -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s

EasyBMPTest: EasyBMP.o Lensmain.o
	g++ $(CFLAGS) EasyBMP.o Lensmain.o -o EasyBMPtest

EasyBMP.o: EasyBMP.cpp EasyBMP*.h
	cp ../EasyBMP*.h .
	cp ../EasyBMP.cpp .
	g++ $(CFLAGS) -c EasyBMP.cpp

Lensmain.o: Lensmain.cpp
	g++ -c Lensmain.cpp

clean: 
	rm EasyBMP*.h
	rm EasyBMP.cpp
	rm EasyBMPtest*
	rm EasyBMPoutput*.bmp
	rm -f *.o
