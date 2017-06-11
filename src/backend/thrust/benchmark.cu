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

template <typename T>
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

template <typename T>
struct ThrustBenchmarkBackend : BenchmarkBackend<T>
{
    ~ThrustBenchmarkBackend()
    {
        std::cout << "thrust benchmark backend destructor called" << std::endl;
    }

    void generate(int num)
    {
        std::cout << "generateing !\n";
        h_vec.resize(num);
        std::generate(h_vec.begin(), h_vec.end(), rand);
        std::cout << "generated !\n";
    }

    void copy()
    {
        d_vec = h_vec;
        cudaDeviceSynchronize();
    }

    void sort()
    {
        std::cout << "start sorting\n";
        thrust::sort(d_vec.begin(), d_vec.end());
        cudaDeviceSynchronize();
        std::cout << "sort finished\n";
    }

  private:
    thrust::host_vector<T> h_vec;
    thrust::device_vector<T> d_vec;
};

template <typename T>
BenchmarkBackend<T> *init()
{
    return new ThrustBenchmarkBackend<T>;
}
}
}

int main(int argc, char **argv)
{
    return aya::bench::launch(argc, argv);
}