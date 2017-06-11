CC = g++-5
CCFLAGS = -Wall -std=c++11
LIBS = -lgflags
NVCC = nvcc -ccbin $(CC) -std=c++11 -arch=sm_53

.PHONY: all
all: wakatime bench

.PHONY: loc
loc:
	cloc src

.PHONY: wakatime
wakatime: 
# $(CC) $(CCFLAGS) -o bin/wakatime src/wakatime.cpp $(LIBS)
	$(CC) $(CCFLAGS) -c -o build/wakatime.o src/wakatime.cpp $(LIBS)
	$(CC) $(CCFLAGS) build/boost.o build/wakatime.o -o bin/wakatime $(LIBS) -lOpenCL

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

.PHONY: boost_bench
boost_bench: src/benchmark.hpp src/backend/boost/benchmark.cpp
	$(CC) $(CCFLAGS) -o bin/bench_boost src/backend/boost/benchmark.cpp $(LIBS) -lOpenCL

.PHONY: boost_backend
boost_backend:
	$(CC) $(CCFLAGS) -c -o build/boost.o src/backend/boost/backend.cpp $(LIBS) -lOpenCL

.PHONY: boost
boost: boost_bench boost_backend
# $(CC) $(CCFLAGS) -c -o build/boost.o src/backend/boost.compute/benchmark.cpp
# $(CC) $(CCFLAGS) -o bin/bench_boost src/backend/boost/benchmark.cpp $(LIBS) -lOpenCL

.PHONY: thrust
thrust:
# FIXME: got warnning from json.hpp
# TODO: http://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#using-separate-compilation-in-cuda
	$(NVCC) -o bin/bench_thrust src/backend/thrust/benchmark.cu $(LIBS)

.PHONY: clean
clean:
	rm -f *.o	