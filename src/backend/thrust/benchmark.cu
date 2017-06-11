#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>

// #include "../../common.hpp"
// #include "../../benchmark.hpp"

#include <iostream>
#include <algorithm>

namespace aya
{
namespace bench
{
void ping()
{
    std::cout << "pong from thrust benchmark backend" << std::endl;
}

std::string name()
{
    return "thrust";
}

template<typename T>
void sort(int num)
{
    std::cout << "sort " << num << std::endl;
    
    static thrust::device_vector<T> d_vec;
    thrust::host_vector<T> h_vec(num);
    std::generate(h_vec.begin(), h_vec.end(), rand);
    d_vec = h_vec;
    cudaDeviceSynchronize();
    thrust::sort(d_vec.begin(), d_vec.end());
    cudaDeviceSynchronize();
}
}
}

int main(int argc, char **argv)
{
//    return aya::bench::launch(argc, argv);
}