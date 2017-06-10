#include "common.hpp"
#include "benchmark.hpp"

// benchmark use different backend and
int main()
{
    std::cout << "let's run some benchmark" << std::endl;
    aya::bench::ping();
}