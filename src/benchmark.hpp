#pragma once
#include "common.hpp"

DEFINE_string(type, "int", "data type int|float|double");
DEFINE_uint64(num, 1000, "length of vector");

namespace aya
{
namespace bench
{
void ping();
std::string name();
template <typename T>
void sort(int num);

// template <typename T>
// void benchSort()
// {
// }

int launch(int argc, char **argv)
{
    std::string usage = "Benchmark " + name() + R"HA(
bench --type int --num 1000
    --type string int|float|double
    --num  uint64 larger than 1000000000 fails on GPU #5
)HA";

    google::SetUsageMessage(usage);
    gflags::SetVersionString("0.0.1");

    // only show usage when no argument is provided
    if (argc < 2)
    {
        std::cout << google::ProgramUsage();
        return 0;
    }

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "Run some benchmark" << std::endl;
    ping();
    sort<int>(FLAGS_num);

    google::ShutDownCommandLineFlags();
    return 0;
}
}
}