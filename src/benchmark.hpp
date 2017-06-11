#pragma once
#include "common.hpp"

DEFINE_uint64(num, 1000, "length of vector");

namespace aya
{
namespace bench
{
void ping();
std::string name();
template<typename T> void sort(int num);

int launch(int argc, char **argv)
{
    std::string usage = "Benchmark " + name() + "\n";
    google::SetUsageMessage(usage);
    gflags::SetVersionString("0.0.1");

    // only show usage when no argument is provided
    if (argc < 2)
    {
        std::cout << google::ProgramUsage();
        return 0;
    }

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "let's run some benchmark" << std::endl;
    aya::ping();
    ping();
    sort<int>(FLAGS_num);

    google::ShutDownCommandLineFlags();
    return 0;
}
}
}