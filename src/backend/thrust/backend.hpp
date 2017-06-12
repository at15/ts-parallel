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
        thrust::device_vector<T> d_vec(src.begin(), src.end());
        if (k > src.size())
        {
            std::cout << "warn: k " << k << " is larger than size " << src.size() << std::endl;
            k = src.size();
        }
        thrust::sort(d_vec.begin(), d_vec.end(), thrust::greater<T>());
        std::vector<T> result(k);
        thrust::copy(d_vec.begin(), d_vec.begin() + k, result.begin());
        return result;
    }

    // FIXME: this is all empty
    std::vector<T> topK(const std::vector<T> &src, unsigned int k, std::vector<int> &index)
    {
        thrust::device_vector<T> d_vec(src.begin(), src.end());
        // Initialize the indices
        // https://stackoverflow.com/questions/6617066/sorting-3-arrays-by-key-in-cuda-using-thrust-perhaps
        // https://stackoverflow.com/a/6618780/4116260
        thrust::counting_iterator<int> iter(0);
        thrust::device_vector<int> d_indices(src.size());
        // std::cout << d_indices.size() << std::endl;
        thrust::copy(iter, iter + d_indices.size(), d_indices.begin());
        // std::cout << d_indices[1] << std::endl;
        thrust::sort_by_key(d_vec.begin(), d_vec.end(), d_indices.begin(), thrust::greater<T>());
        // thrust::sort(d_vec.begin(), d_vec.end(), thrust::greater<T>());
        if (k > src.size())
        {
            std::cout << "warn: k " << k << " is larger than size " << src.size() << std::endl;
            k = src.size();
        }
        index.resize(k);
        std::vector<T> result(k);
        thrust::copy(d_vec.begin(), d_vec.begin() + k, result.begin());
        thrust::copy(d_indices.begin(), d_indices.begin() + k, index.begin());
        cudaDeviceSynchronize();
        return result;
    }

    template <typename K>
    std::vector<K> groupByTopK(const std::vector<K> &keys, const std::vector<T> &values, unsigned int k, std::vector<T> &grouped_values)
    {
        // select name, SUM(time) as sm from project group by name order by sm

        // select name, time from project
        thrust::device_vector<K> d_keys(keys.begin(), keys.end());
        thrust::device_vector<T> d_values(values.begin(), values.end());
        // NOTE: if we know the length of unique keys, we could have allocated much less space
        thrust::device_vector<K> d_grouped_keys(keys.size());
        thrust::device_vector<T> d_grouped_values(keys.size());

        // order by name
        thrust::sort_by_key(d_keys.begin(), d_keys.end(), d_values.begin(), thrust::greater<K>());
        // group by name
        thrust::reduce_by_key(d_keys.begin(), d_keys.end(), d_values.begin(), d_grouped_keys.begin(), d_grouped_values.begin());
        // order by sm
        thrust::sort_by_key(d_grouped_values.begin(), d_grouped_values.end(), d_grouped_keys.begin(), thrust::greater<T>());

        if (k > d_grouped_keys.size())
        {
            std::cout << "warn: k " << k << " is larger than unique keys " << d_grouped_keys.size() << std::endl;
            k = d_grouped_keys.size();
        }
        std::vector<K> grouped_keys(k);
        grouped_values.resize(k);
        thrust::copy(d_grouped_keys.begin(), d_grouped_keys.begin() + k, grouped_keys.begin());
        thrust::copy(d_grouped_values.begin(), d_grouped_values.begin() + k, grouped_values.begin());
        return grouped_keys;
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