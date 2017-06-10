#include "../../common.hpp"
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

template<typename T>
void sort(int num)
{
    std::cout << "sort " << num << std::endl;
}
}
}

int main(int argc, char **argv)
{
   return aya::bench::launch(argc, argv);
}