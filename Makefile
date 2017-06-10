CC = clang++-3.8
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags
NVCC = nvcc --std c++11 -ccbin $(CC)

.PHONY: all
all: wakatime bench

.PHONY: wakatime
wakatime: 
	$(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp $(LIBS)
	
.PHONY: boost
boost: 
# $(CC) $(CCFLAGS) -c -o build/boost.o src/backend/boost.compute/benchmark.cpp
	$(CC) $(CCFLAGS) -o bin/bench_boost src/backend/boost.compute/benchmark.cpp $(LIBS) -lOpenCL

.PHONY: thrust
thrust: 
# $(CC) $(CCFLAGS) -c -o build/thrust.o src/backend/thrust/benchmark.cpp
	$(NVCC) -o build/bench_thrust src/backend/thrust/benchmark.cu -Xcompiler -Wall $(LIBS)

.PHONY: bench
bench: boost thrust
# $(CC) $(CCFLAGS) -c -o build/bench.o src/bench.cpp $(LIBS)
# FIXED: can't use static in header for declaration https://stackoverflow.com/questions/10812769/static-function-declared-but-not-defined-in-c
# $(CC) $(CCFLAGS) -o bin/bench_thrust build/thrust.o build/bench.o
# $(CC) $(CCFLAGS) -o bin/bench_boost build/boost.o build/bench.o

.PHONY: clean
clean:
	rm -f *.o	