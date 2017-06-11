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
void sort(int num)
{
    std::cout << "sort " << num << std::endl;
    std::vector<T> vec(num);
    std::generate(vec.begin(), vec.end(), rand);
    std::sort(vec.begin(), vec.end());
    std::cout << "sort finished " << std::endl;
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

  private:
    std::vector<T> vec;
};

template <typename T>
BenchmarkBackend<T> *init()
{
    return new SerialBenchmarkBackend<T>;
}
}
}

int main(int argc, char **argv)
{
    return aya::bench::launch(argc, argv);
}
