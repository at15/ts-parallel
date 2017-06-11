# ArrayFire

https://github.com/arrayfire/arrayfire

## Install

- made a post https://groups.google.com/d/msg/arrayfire-users/s7nka4S21dc/Wc7YfREBAgAJ
- solved: **Use GCC 5.x**

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
sudo make install
sudo ldconfig
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
- https://github.com/Microsoft/CNTK/issues/1019 is exactly the same
- https://groups.google.com/forum/#!topic/digits-users/MpWhRFhllZs similar

after checkout to 3.4.2, got error again ....

````
make[2]: *** No rule to make target 'src/backend/cuda/cuda_compile_ptx_generated_arith.cu.ptx', needed by 'src/backend/cuda/arith.ptx'.  Stop.
CMakeFiles/Makefile2:653: recipe for target 'src/backend/cuda/CMakeFiles/cuda_ptx_headers_bin_target.dir/all' failed
make[1]: *** [src/backend/cuda/CMakeFiles/cuda_ptx_headers_bin_target.dir/all] Error 2
````

https://github.com/arrayfire/arrayfire/issues/1755 need to use new version .... wtf

````
-- Install configuration: "Release"
-- Up-to-date: /usr/local/include
-- Installing: /usr/local/include/af
-- Installing: /usr/local/include/af/opencl.h
-- Installing: /usr/local/include/af/gfor.h
-- Installing: /usr/local/include/af/lapack.h
-- Installing: /usr/local/include/af/image.h
-- Installing: /usr/local/include/af/data.h
-- Installing: /usr/local/include/af/index.h
-- Installing: /usr/local/include/af/exception.h
-- Installing: /usr/local/include/af/array.h
-- Installing: /usr/local/include/af/arith.h
-- Installing: /usr/local/include/af/vision.h
-- Installing: /usr/local/include/af/cuda.h
-- Installing: /usr/local/include/af/internal.h
-- Installing: /usr/local/include/af/blas.h
-- Installing: /usr/local/include/af/signal.h
-- Installing: /usr/local/include/af/backend.h
-- Installing: /usr/local/include/af/defines.h
-- Installing: /usr/local/include/af/seq.h
-- Installing: /usr/local/include/af/util.h
-- Installing: /usr/local/include/af/macros.h
-- Installing: /usr/local/include/af/statistics.h
-- Installing: /usr/local/include/af/features.h
-- Installing: /usr/local/include/af/traits.hpp
-- Installing: /usr/local/include/af/random.h
-- Installing: /usr/local/include/af/algorithm.h
-- Installing: /usr/local/include/af/dim4.hpp
-- Installing: /usr/local/include/af/version.h
-- Installing: /usr/local/include/af/timing.h
-- Installing: /usr/local/include/af/sparse.h
-- Installing: /usr/local/include/af/compatible.h
-- Installing: /usr/local/include/af/graphics.h
-- Installing: /usr/local/include/af/constants.h
-- Installing: /usr/local/include/af/device.h
-- Installing: /usr/local/include/af/complex.h
-- Installing: /usr/local/include/arrayfire.h
-- Up-to-date: /usr/local/include/af/version.h
-- Up-to-date: /usr/local/lib
-- Installing: /usr/local/lib/libforge.so.0
-- Installing: /usr/local/lib/libforge.so.0.9.2
-- Installing: /usr/local/lib/libforge.so
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireConfig.cmake
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireConfigVersion.cmake
-- Installing: /usr/local/share/ArrayFire/examples
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/logistic_regression.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/softmax_regression.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/deep_belief_net.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/neural_network.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/knn.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/geneticalgorithm.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/mnist_common.h
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/rbm.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/naive_bayes.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/kmeans.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/bagging.cpp
-- Installing: /usr/local/share/ArrayFire/examples/machine_learning/perceptron.cpp
-- Installing: /usr/local/share/ArrayFire/examples/CMakeLists.txt
-- Installing: /usr/local/share/ArrayFire/examples/image_processing
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/morphing.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/optical_flow.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/edge.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/image_editing.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/brain_segmentation.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/pyramids.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/binary_thresholding.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/adaptive_thresholding.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/image_demo.cpp
-- Installing: /usr/local/share/ArrayFire/examples/image_processing/filters.cpp
-- Installing: /usr/local/share/ArrayFire/examples/CMakeModules
-- Installing: /usr/local/share/ArrayFire/examples/CMakeModules/FindOpenCL.cmake
-- Installing: /usr/local/share/ArrayFire/examples/financial
-- Installing: /usr/local/share/ArrayFire/examples/financial/black_scholes_options.cpp
-- Installing: /usr/local/share/ArrayFire/examples/financial/input.h
-- Installing: /usr/local/share/ArrayFire/examples/financial/monte_carlo_options.cpp
-- Installing: /usr/local/share/ArrayFire/examples/financial/heston_model.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics
-- Installing: /usr/local/share/ArrayFire/examples/graphics/gravity_sim_init.h
-- Installing: /usr/local/share/ArrayFire/examples/graphics/plot2d.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/conway_pretty.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/conway.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/gravity_sim.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/surface.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/fractal.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/histogram.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/field.cpp
-- Installing: /usr/local/share/ArrayFire/examples/graphics/plot3.cpp
-- Installing: /usr/local/share/ArrayFire/examples/getting_started
-- Installing: /usr/local/share/ArrayFire/examples/getting_started/vectorize.cpp
-- Installing: /usr/local/share/ArrayFire/examples/getting_started/integer.cpp
-- Installing: /usr/local/share/ArrayFire/examples/getting_started/rainfall.cpp
-- Installing: /usr/local/share/ArrayFire/examples/getting_started/convolve.cpp
-- Installing: /usr/local/share/ArrayFire/examples/benchmarks
-- Installing: /usr/local/share/ArrayFire/examples/benchmarks/fft.cpp
-- Installing: /usr/local/share/ArrayFire/examples/benchmarks/cg.cpp
-- Installing: /usr/local/share/ArrayFire/examples/benchmarks/pi.cpp
-- Installing: /usr/local/share/ArrayFire/examples/benchmarks/blas.cpp
-- Installing: /usr/local/share/ArrayFire/examples/README.md
-- Installing: /usr/local/share/ArrayFire/examples/lin_algebra
-- Installing: /usr/local/share/ArrayFire/examples/lin_algebra/lu.cpp
-- Installing: /usr/local/share/ArrayFire/examples/lin_algebra/svd.cpp
-- Installing: /usr/local/share/ArrayFire/examples/lin_algebra/cholesky.cpp
-- Installing: /usr/local/share/ArrayFire/examples/lin_algebra/qr.cpp
-- Installing: /usr/local/share/ArrayFire/examples/computer_vision
-- Installing: /usr/local/share/ArrayFire/examples/computer_vision/susan.cpp
-- Installing: /usr/local/share/ArrayFire/examples/computer_vision/fast.cpp
-- Installing: /usr/local/share/ArrayFire/examples/computer_vision/matching.cpp
-- Installing: /usr/local/share/ArrayFire/examples/computer_vision/harris.cpp
-- Installing: /usr/local/share/ArrayFire/examples/common
-- Installing: /usr/local/share/ArrayFire/examples/common/idxio.h
-- Installing: /usr/local/share/ArrayFire/examples/common/progress.h
-- Installing: /usr/local/share/ArrayFire/examples/unified
-- Installing: /usr/local/share/ArrayFire/examples/unified/basic.cpp
-- Installing: /usr/local/share/ArrayFire/examples/helloworld
-- Installing: /usr/local/share/ArrayFire/examples/helloworld/helloworld.cpp
-- Installing: /usr/local/share/ArrayFire/examples/pde
-- Installing: /usr/local/share/ArrayFire/examples/pde/swe.cpp
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/spider.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/trees_ctm.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/sudoku.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/brain.png
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/fight.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/vegetable-woman.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/nature.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/README.md
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/circle_left.ppm
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/arrow.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/atlantis.png
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/bimodal.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/noisy_square.png
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/house.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/man.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/square.png
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/circle_center.ppm
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/images/sunset_emp.jpg
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/data
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/data/mnist
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/data/mnist/images-subset
-- Installing: /usr/local/share/ArrayFire/examples/assets/examples/data/mnist/labels-subset
-- Installing: /usr/local/lib/libafcpu.so.3.5.0
-- Installing: /usr/local/lib/libafcpu.so.3
-- Installing: /usr/local/lib/libafcpu.so
-- Set runtime path of "/usr/local/lib/libafcpu.so.3.5.0" to ""
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireCPU.cmake
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireCPU-release.cmake
-- Installing: /usr/local/lib/libafcuda.so.3.5.0
-- Installing: /usr/local/lib/libafcuda.so.3
-- Installing: /usr/local/lib/libafcuda.so
-- Set runtime path of "/usr/local/lib/libafcuda.so.3.5.0" to ""
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireCUDA.cmake
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireCUDA-release.cmake
-- Installing: /usr/local/lib/libafopencl.so.3.5.0
-- Installing: /usr/local/lib/libafopencl.so.3
-- Installing: /usr/local/lib/libafopencl.so
-- Set runtime path of "/usr/local/lib/libafopencl.so.3.5.0" to ""
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireOpenCL.cmake
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireOpenCL-release.cmake
-- Installing: /usr/local/lib/libaf.so.3.5.0
-- Installing: /usr/local/lib/libaf.so.3
-- Installing: /usr/local/lib/libaf.so
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireUnified.cmake
-- Installing: /usr/local/share/ArrayFire/cmake/ArrayFireUnified-release.cmake
````
