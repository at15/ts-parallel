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
        thrust::sort(d_vec.begin(), d_vec.end(), thrust::greater<T>());
        std::vector<T> result(k);
        thrust::copy(d_vec.begin(), d_vec.begin() + k, result.begin());
        return result;
    }

    // FIXME: this is all empty
    std::vector<T> topK(const std::vector<T> &src, unsigned int k, std::vector<int> index)
    {
        thrust::device_vector<int> d_vec(src.begin(), src.end());
        // Initialize the indices
        // https://stackoverflow.com/questions/6617066/sorting-3-arrays-by-key-in-cuda-using-thrust-perhaps
        // https://stackoverflow.com/a/6618780/4116260
        thrust::counting_iterator<int> iter(0);
        thrust::device_vector<int> d_indices(src.size());
        thrust::copy(iter, iter + d_indices.size(), d_indices.begin());
        thrust::sort_by_key(d_vec.begin(), d_vec.end(), d_indices.begin());

        if (k > src.size())
        {
            std::cout << "warn: k " << k << " is larger than size " << src.size();
            k = src.size();
        }
        index.resize(k);
        std::vector<T> result(k);
        thrust::copy(d_vec.begin(), d_vec.begin() + k, result.begin());
        thrust::copy(d_indices.begin(), d_indices.begin() + k, index.begin());
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