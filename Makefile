CC = g++
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags

.PHONY:
wakatime:
	$(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp $(LIBS)