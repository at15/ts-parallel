#include <boost/compute.hpp>

#include "../../backend.hpp"

namespace compute = boost::compute;

namespace aya
{
namespace backend
{
template <typename T>
struct BoostBackend : Backend<T>
{
    ~BoostBackend()
    {
        std::cout << "boost backend destructor called\n";
    }

    std::vector<T> topK(const std::vector<T> &src, int k)
    {
        auto d_vec = compute::vector<T>(src.size(), context);
        compute::copy(src.begin(), src.end(), d_vec.begin(), queue);
        compute::sort(d_vec.begin(), d_vec.end(), std::greater<T>(), queue);
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

  private:
    compute::device gpu;
    compute::context context;
    compute::command_queue queue;
};

template <typename T>
Backend<T>* init(){
    return new BoostBackend<T>;
}
} // backend
} // aya::backend