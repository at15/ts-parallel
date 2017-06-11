#pragma once
#include "common.hpp"

DEFINE_string(type, "int", "data type int|float|double");
DEFINE_string(op, "sort", "operation sort|reduce");
DEFINE_uint64(num, 1000, "length of vector");

namespace aya
{
namespace bench
{
void ping();
std::string name();
template <typename T>
void sort(int num);

std::string reportFileName()
{
    std::ostringstream os;
    os << name() << "_" << FLAGS_op << "_" << FLAGS_num << "_" << FLAGS_type << ".csv";
    return os.str();
}

// template <typename T>
// void benchSort()
// {
// }

template <typename T>
struct BenchmarkBackend
{
    virtual void generate(int) = 0;
    virtual void copy() = 0;
    virtual void sort() = 0;
    virtual ~BenchmarkBackend() {}
};

template <typename T>
BenchmarkBackend<T> *init();

int launch(int argc, char **argv)
{
    std::string usage = "Benchmark " + name() + R"HA(
bench --op sort --num 1000 --type int
    --op   string sort|reduce
    --num  uint64 larger than 1000000000 fails on GPU #5
    --type string int|float|double
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

    std::cout << "Let's run some benchmark \\w/" << std::endl;
    // ping();
    // sort<int>(FLAGS_num);
    std::cout << reportFileName() << std::endl;
    auto back_end = init<int>();
    back_end->generate(FLAGS_num);
    back_end->copy();
    back_end->sort();
    delete back_end;

    google::ShutDownCommandLineFlags();
    return 0;
}
}
}
