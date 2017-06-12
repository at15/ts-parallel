#pragma once

#include <boost/compute.hpp>

#include "../../common.hpp"

namespace aya
{
namespace backend
{

namespace compute = boost::compute;
void ping()
{
    std::cout << "pong from boost backend\n";
}

template <typename T>
struct Backend
{
    Backend()
    {
        gpu = compute::system::default_device();
        context = compute::context(gpu);
        queue = compute::command_queue(context, gpu);
    }

    ~Backend()
    {
        std::cout << "boost backend destructor called\n";
    }

    std::vector<T> topK(const std::vector<T> &src, unsigned int k)
    {
        auto d_vec = compute::vector<T>(src.size(), context);
        compute::copy(src.begin(), src.end(), d_vec.begin(), queue);
        compute::sort(d_vec.begin(), d_vec.end(), compute::greater<T>(), queue);
        queue.finish();
        if (k > src.size())
        {
            std::cout << "warn: k " << k << " is larger than size " << src.size();
            k = src.size();
        }
        std::vector<T> result(k);
        compute::copy(d_vec.begin(), d_vec.begin() + k, result.begin(), queue);
        queue.finish();
        return result;
    }

    // FIXME: can we keep the cout when using counting iterator?
    // std::vector<unsigned int> topKIndex(const std::vector<T> &src, unsigned int k)
    // {
    //     auto d_vec = compute::vector<T>(src.size(), context);
    //     compute::copy(src.begin(), src.end(), d_vec.begin(), queue);
    //     compute::counting_iterator<T> index(0);
    //     compute::sort_by_key(d_vec.begin(), d_vec.end(), index.begin(), queue);
    // }

  private:
    compute::device gpu;
    compute::context context;
    compute::command_queue queue;
};

template <typename T>
Backend<T> *init()
{
    return new Backend<T>;
}
} // backend
} // aya::backend