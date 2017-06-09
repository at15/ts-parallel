# ArrayFire

https://github.com/arrayfire/arrayfire

## Install

````
sudo apt-get install -y libfreeimage-dev cmake-curses-gui
sudo apt-get install libopenblas-dev libfftw3-dev liblapacke-dev
sudo apt-get install libglfw3-dev libfontconfig1-dev
Ayi git clone github.com/arrayfire/arrayfire
cd ~/workspace/src/github.com/arrayfire/arrayfire
git submodule init
git submodule update
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_CUDA=ON
make -j4
````

````
CMake Error at src/backend/cuda/CMakeLists.txt:106 (message):
  NVCC does not support GCC version 6.0 or greater.
````

````
export CC=/usr/bin/clang-3.8
export CXX=/usr/bin/clang++-3.8
````

**need to remove CMake cache**

````
/usr/include/cuda_fp16.h(3068): error: more than one instance of overloaded function "isinf" matches the argument list:
            function "std::isinf(float)"
            function "isinf(float)"
            argument types are: (float)

/usr/include/cuda_fp16.h(3079): error: more than one instance of overloaded function "isinf" matches the argument list:
            function "std::isinf(float)"
            function "isinf(float)"
            argument types are: (float)

/home/at15/workspace/src/github.com/arrayfire/arrayfire/src/backend/cpu/Array.cpp:26:11: warning: unused variable 'MAX_TNJ_LEN'
      [-Wunused-const-variable]
const int MAX_TNJ_LEN = 20;
          ^
2 errors detected in the compilation of "/tmp/tmpxft_00005216_00000000-7_all.cpp1.ii".
CMake Error at afcuda_generated_all.cu.o.Release.cmake:282 (message):
  Error generating file
  /home/at15/workspace/src/github.com/arrayfire/arrayfire/build/src/backend/cuda/CMakeFiles/afcuda.dir//./afcuda_generated_all.cu.o


src/backend/cuda/CMakeFiles/afcuda.dir/build.make:63: recipe for target 'src/backend/cuda/CMakeFiles/afcuda.dir/afcuda_generated_all.cu.o' failed
make[2]: *** [src/backend/cuda/CMakeFiles/afcuda.dir/afcuda_generated_all.cu.o] Error 1
CMakeFiles/Makefile2:687: recipe for target 'src/backend/cuda/CMakeFiles/afcuda.dir/all' failed
````

- seems relevant https://git.qt.io/consulting-usa/qtbase-xcb-rendering/commit/4c0760d327e390a37d0d6ce2016d3a8c5b87a119

after checkout to 3.4.2, got error again ....

````
make[2]: *** No rule to make target 'src/backend/cuda/cuda_compile_ptx_generated_arith.cu.ptx', needed by 'src/backend/cuda/arith.ptx'.  Stop.
CMakeFiles/Makefile2:653: recipe for target 'src/backend/cuda/CMakeFiles/cuda_ptx_headers_bin_target.dir/all' failed
make[1]: *** [src/backend/cuda/CMakeFiles/cuda_ptx_headers_bin_target.dir/all] Error 2
````

https://github.com/arrayfire/arrayfire/issues/1755 need to use new version .... wtf