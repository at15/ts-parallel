#include <boost/compute.hpp>

#include "../../benchmark.hpp"

namespace compute = boost::compute;

namespace aya
{
namespace bench
{
void ping()
{
    std::cout << "pong from boost compute benchmark backend" << std::endl;
}
std::string name()
{
    return "boost.compute";
}

template <typename T>
void sort(int num)
{
    static compute::device gpu;
    static compute::context context;
    static compute::command_queue queue;
    static compute::vector<T> d_vec;

    std::cout << "sort " << num << std::endl;
    gpu = compute::system::default_device();
    context = compute::context(gpu);
    queue = compute::command_queue(context, gpu);
    d_vec = compute::vector<T>(num, context);

    // generate random data on host
    std::vector<T> h_vec(num);
    std::generate(h_vec.begin(), h_vec.end(), rand);

    compute::copy(h_vec.begin(), h_vec.end(), d_vec.begin(), queue);
    // TODO: the demo from boost compute does not have this, but array fire valhalla has this
    queue.finish();

    // FIXME: failed when num is 1000000000
    compute::sort(d_vec.begin(), d_vec.end(), queue);
    queue.finish();
}

template <typename T>
struct BoostBenchmarkBackend : BenchmarkBackend<T>
{
    BoostBenchmarkBackend()
    {
        // TODO: is there copy overhead when using assign? but those does not contains data, so I guess it's low
        // for vector, maybe use swap? http://en.cppreference.com/w/cpp/container/vector/swap
        gpu = compute::system::default_device();
        context = compute::context(gpu);
        queue = compute::command_queue(context, gpu);
    }

    ~BoostBenchmarkBackend()
    {
        std::cout << "boost benchmark backend destructor called\n";
    }

    void generate(int num)
    {
        std::cout << "generateing !\n";
        h_vec.resize(num);
        std::generate(h_vec.begin(), h_vec.end(), rand);
        // TODO: bechmark this assign operation? does it copy anything?
        d_vec = compute::vector<T>(num, context);
        std::cout << "generated !\n";
    }

    void copy()
    {
        compute::copy(h_vec.begin(), h_vec.end(), d_vec.begin(), queue);
        queue.finish();
    }

    void sort()
    {
        compute::sort(d_vec.begin(), d_vec.end(), queue);
        queue.finish();
    }

  private:
    std::vector<T> h_vec;
    compute::vector<T> d_vec;
    compute::device gpu;
    compute::context context;
    compute::command_queue queue;
};

template <typename T>
BenchmarkBackend<T> *init()
{
    return new BoostBenchmarkBackend<T>;
}
}
}

int main(int argc, char **argv)
{
    return aya::bench::launch(argc, argv);
}
