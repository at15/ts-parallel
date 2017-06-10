CC = g++
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags

.PHONY:
wakatime:
	$(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp src/util.cpp $(LIBS)

.PHONY:
thrust:
	$(CC) $(CCFLAGS) -c -o build/thrust.o src/backend/thrust/benchmark.cpp

.PHONY:
bench:
# $(CC) $(CCFLAGS) -c -o build/bench.o src/benchmark.cpp	
# $(CC) $(CCFLAGS) -o bin/bench_thrust build/thrust.o build/bench.o
# $(CC) $(CCFLAGS) -o bin/bench_thrust src/benchmark.cpp build/thrust.o
# $(CC) $(CCFLAGS) -o bin/bench_thrust src/backend/thrust/benchmark.cpp src/benchmark.cpp
# FIXED: can't use static ... https://stackoverflow.com/questions/10812769/static-function-declared-but-not-defined-in-c
	$(CC) $(CCFLAGS) -o bin/bench_thrust src/bench.cpp src/util.cpp src/backend/thrust/benchmark.cpp $(LIBS)
	

.PHONY:
clean:
	rm -f *.o	