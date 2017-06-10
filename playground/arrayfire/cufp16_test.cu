#include <cuda_fp16.h>
#include <iostream>
#include <cmath>
#include <cfloat>

using namespace std;

// nvcc -ccbin clang++-3.8 cufp16_test.cu
// NOTE: didn't get any error like building ArrayFire
int main()
{
   cout << isinf(NAN) << endl; // 0
   cout << isinf(INFINITY) << endl; // 1
}
