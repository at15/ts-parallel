CC = g++
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags

.PHONY: all
all: wakatime bench

.PHONY: wakatime
wakatime: 
	$(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp $(LIBS)
	
.PHONY: boost
boost: 
	$(CC) $(CCFLAGS) -c -o build/boost.o src/backend/boost.compute/benchmark.cpp

.PHONY: thrust
thrust: 
	$(CC) $(CCFLAGS) -c -o build/thrust.o src/backend/thrust/benchmark.cpp

.PHONY: bench
bench: boost thrust
	$(CC) $(CCFLAGS) -c -o build/bench.o src/bench.cpp	
# $(CC) $(CCFLAGS) -o bin/bench_thrust build/thrust.o build/bench.o
# $(CC) $(CCFLAGS) -o bin/bench_thrust src/benchmark.cpp build/thrust.o
# $(CC) $(CCFLAGS) -o bin/bench_thrust src/backend/thrust/benchmark.cpp src/benchmark.cpp
# FIXED: can't use static ... https://stackoverflow.com/questions/10812769/static-function-declared-but-not-defined-in-c
# $(CC) $(CCFLAGS) -o bin/bench_thrust src/bench.cpp src/util.cpp src/backend/thrust/benchmark.cpp $(LIBS)
	$(CC) $(CCFLAGS) -o bin/bench_thrust build/thrust.o build/bench.o $(LIBS)
	
.PHONY: clean
clean:
	rm -f *.o	