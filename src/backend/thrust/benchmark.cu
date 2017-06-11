#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>

#include "../../benchmark.hpp"

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

// FIXME: static cause the following problem    
//     terminate called after throwing an instance of 'thrust::system::system_error'
//   what():  cudaFree in free: driver shutting down
    // static thrust::device_vector<T> d_vec;
    thrust::device_vector<T> d_vec;
    
    thrust::host_vector<T> h_vec(num);
    std::generate(h_vec.begin(), h_vec.end(), rand);
    d_vec = h_vec;
    cudaDeviceSynchronize();
    thrust::sort(d_vec.begin(), d_vec.end());
    cudaDeviceSynchronize();

    std::cout << "sort finished" << std::endl;
}
}
}

int main(int argc, char **argv)
{
   return aya::bench::launch(argc, argv);
}