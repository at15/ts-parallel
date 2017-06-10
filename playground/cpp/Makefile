# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm
LIBS = -lgflags
CCFLAGS = -Wall -std=c++11

all: mem.bin j.bin flag.bin date.bin
date.bin: date.cpp
	g++ $(CCFLAGS) -o date.bin date.cpp
	./date.bin
mem.bin: mem.cpp
	@g++ -o mem.bin mem.cpp
	@./mem.bin
j.bin: j.cpp
	@g++ -o j.bin j.cpp
	@./j.bin
flag.bin: flag.cpp
# from https://github.com/xunzhang/roraima/issues/1
	g++ -Wall -std=c++11 -o flag.bin flag.cpp -lgflags
	@./flag.bin		
.PHONY:
clean:
	rm -f *.bin