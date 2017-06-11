#include "../../benchmark.hpp"

namespace aya
{
namespace bench
{

void ping()
{
    std::cout << "pong from serial backend" << std::endl;
}

std::string name()
{
    return "serial";
}

template <typename T>
struct SerialBenchmarkBackend : BenchmarkBackend<T>
{
    ~SerialBenchmarkBackend()
    {
        std::cout << "serial benchmark backend destructor called" << std::endl;
    }

    void generate(int num)
    {
        std::cout << "generateing !\n";
        vec.resize(num);
        std::generate(vec.begin(), vec.end(), rand);
        std::cout << "generated !\n";
    }

    void copy()
    {
        std::cout << "no need to copy\n";
    }

    void sort()
    {
        std::cout << "start sorting\n";
        std::sort(vec.begin(), vec.end());
        std::cout << "sort finished\n";
    }

    void reduce()
    {
        std::cout << "start reduce\n";
        std::accumulate(vec.begin(), vec.end(), 0);
        std::cout << "reduce finished\n";
    }

  private:
    std::vector<T> vec;
};

template <typename T>
BenchmarkBackend<T> *init()
{
    return new SerialBenchmarkBackend<T>;
}

} // bench
} // aya::bench

int main(int argc, char **argv)
{
    return aya::bench::launch(argc, argv);
}
