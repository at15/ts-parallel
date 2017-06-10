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
}
}

int main(int argc, char ** argv)
{
    aya::bench::launch(argc, argv);
}