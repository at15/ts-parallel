#pragma once
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>

#include "../../common.hpp"

namespace aya
{
namespace backend
{

void ping()
{
    std::cout << "pong from thrust backend\n";
}

template <typename T>
struct Backend
{
    Backend()
    {
    }

    ~Backend()
    {
        std::cout << "thrust backend destructor called\n";
    }

    std::vector<T> topK(const std::vector<T> &src, unsigned int k)
    {
        thrust::device_vector<int> d_vec(src.begin(), src.end());
        if (k > src.size())
        {
            std::cout << "warn: k " << k << " is larger than size " << src.size();
            k = src.size();
        }
        std::vector<T> result(k);
        thrust::copy(d_vec.begin(), d_vec.begin() + k, result.begin());
        return result;
    }

  private:

};

template <typename T>
Backend<T> *init()
{
    return new Backend<T>;
}
} // backend
} // aya::backend