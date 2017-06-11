# All the stuff I don't know about CPP


## static

- can't declare static functions in header without definition
  - array fire valhalla defined static function in header, but is it just called in other header file

````
g++ -Wall -std=c++11 -o bin/bench_thrust src/benchmark.cpp src/backend/thrust/benchmark.cpp -lgflags
In file included from src/benchmark.cpp:2:0:
src/benchmark.hpp:7:13: warning: ‘void aya::bench::ping()’ declared ‘static’ but never defined [-Wunused-function]
 static void ping();
             ^~~~
src/backend/thrust/benchmark.cpp:8:13: warning: ‘void aya::bench::ping()’ defined but not used [-Wunused-function]
 static void ping()
             ^~~~
/tmp/ccpBWCwP.o: In function `main':
benchmark.cpp:(.text+0x2d): undefined reference to `aya::bench::ping()'
collect2: error: ld returned 1 exit status
Makefile:19: recipe for target 'bench' failed
make: *** [bench] Error 1
````

## inline

- when put definition in a header, and this header is included by more than one cpp files, you compile those cpp files into separate o files and link them,
you will get `multiple definition of` error
- the way is to add `inline` so the object files does not export those functions
  - https://stackoverflow.com/a/685467/4116260
  - > Include the inline keyword so they are not exported by each object file
- https://stackoverflow.com/questions/15159561/static-libraries-importing-and-exporting-inline-functions
  - > being inline means that multiple (identical) definitions of the same function can exist without causing a problem

````
/tmp/ccchOaib.o: In function `aya::ping()':
bench.cpp:(.text+0x0): multiple definition of `aya::ping()'
build/thrust.o:benchmark.cpp:(.text+0x0): first defined here
/tmp/ccchOaib.o: In function `aya::toEpoch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)':
bench.cpp:(.text+0x2f): multiple definition of `aya::toEpoch(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
build/thrust.o:benchmark.cpp:(.text+0x2f): first defined here
collect2: error: ld returned 1 exit status
Makefile:22: recipe for target 'bench' failed
make: *** [bench] Error 1
````

## parameter pack

- use to implement variadic functions
- http://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/
- need a base function
- use `sizeof...(Args)` to get the size of parameters
- see playground/csv/write.cpp

## class

- abstract class need virtual destructor
  - https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
