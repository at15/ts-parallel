CC = g++-5
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags
NVCC = nvcc -ccbin $(CC) -std=c++11 -arch=sm_53

.PHONY: all
all: wakatime bench

.PHONY: loc
loc:
	cloc src

.PHONY: csv
csv:
	$(CC) $(CCFLAGS) -o bin/csv src/csv.cpp $(LIBS)

.PHONY: wakatime_thrust
wakatime_thrust:
	cp src/wakatime.cpp src/wakatime.cu
	$(NVCC) -DWAKA_THRUST -o bin/wakatime_thrust src/wakatime.cu $(LIBS)

.PHONY: wakatime_boost
wakatime_boost: 
# $(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp $(LIBS)
# $(CC) $(CCFLAGS) -c -o build/wakatime.o src/wakatime.cpp $(LIBS)
# $(CC) $(CCFLAGS) build/wakatime.o build/boost.o -o bin/wakatime $(LIBS) -lOpenCL
# $(CC) $(CCFLAGS) -o bin/wakatime src/backend/boost/backend.cpp src/wakatime.cpp $(LIBS) -lOpenCL
	$(CC) $(CCFLAGS) -DWAKA_BOOST -o bin/wakatime_boost src/wakatime.cpp $(LIBS) -lOpenCL
	

.PHONY: bench
bench: boost thrust serial
# $(CC) $(CCFLAGS) -c -o build/bench.o src/bench.cpp $(LIBS)
# FIXED: can't use static in header for declaration https://stackoverflow.com/questions/10812769/static-function-declared-but-not-defined-in-c
# $(CC) $(CCFLAGS) -o bin/bench_thrust build/thrust.o build/bench.o
# $(CC) $(CCFLAGS) -o bin/bench_boost build/boost.o build/bench.o

# -------------------
# Backends
# -------------------
.PHONY: serial
serial:
	$(CC) $(CCFLAGS) -o bin/bench_serial src/backend/serial/benchmark.cpp $(LIBS)

.PHONY: boost
boost: src/benchmark.hpp src/backend/boost/benchmark.cpp
# $(CC) $(CCFLAGS) -c -o build/boost.o src/backend/boost.compute/benchmark.cpp
	$(CC) $(CCFLAGS) -o bin/bench_boost src/backend/boost/benchmark.cpp $(LIBS) -lOpenCL

.PHONY: thrust
thrust:
# FIXME: got warnning from json.hpp
# TODO: http://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#using-separate-compilation-in-cuda
	$(NVCC) -o bin/bench_thrust src/backend/thrust/benchmark.cu $(LIBS)

.PHONY: clean
clean:
	rm -f *.o	