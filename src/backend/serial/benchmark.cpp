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

struct SerialBenchmarkBackend : BenchmarkBackend
{
    void generate()
    {
        std::cout << "generate!\n";
    }

    void copy()
    {
        std::cout << "copy\n";
    }

    void sort()
    {
        std::cout << "sort\n";
    }
};

BenchmarkBackend* init()
{
    return new SerialBenchmarkBackend;
}
}

}

int main(int argc, char **argv)
{
    return aya::bench::launch(argc, argv);
}
