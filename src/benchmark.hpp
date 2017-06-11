#pragma once
#include "common.hpp"

DEFINE_string(op, "sort", "operation sort|reduce");
DEFINE_uint64(num, 1000, "length of vector");
DEFINE_string(type, "int", "data type int|float|double");

static bool ValidateOp(const char *flagname, const std::string &value)
{
    if (value == "sort")
    {
        return true;
    }
    else if (value == "reduce")
    {
        return true;
    }
    else
    {
        std::cout << "unknown operation " << value << std::endl;
        return false;
    }
}

static bool ValidateType(const char *flagname, const std::string &value)
{
    if (value == "int")
    {
        return true;
    }
    else if (value == "float")
    {
        return true;
    }
    else if (value == "double")
    {
        return true;
    }
    else
    {
        std::cout << "unknown value type " << value << std::endl;
        return false;
    }
}

DEFINE_validator(op, &ValidateOp);
DEFINE_validator(type, &ValidateType);

namespace aya
{
namespace bench
{

void ping();
std::string name();

std::string reportFileName()
{
    std::ostringstream os;
    os << name() << "_" << FLAGS_op << "_" << FLAGS_num << "_" << FLAGS_type << ".csv";
    return os.str();
}

template <typename T>
struct BenchmarkBackend
{
    virtual void generate(int) = 0;
    virtual void copy() = 0;
    virtual void sort() = 0;
    virtual void reduce() = 0;
    virtual ~BenchmarkBackend() {}
};

template <typename T>
BenchmarkBackend<T> *init();

int elapsedNano(const std::chrono::steady_clock::time_point &begin)
{
    auto now = std::chrono::steady_clock::now();
    // FIXME: when using nanoseconds, we got negative value ... std::chrono::nanoseconds
    return std::chrono::duration_cast<std::chrono::microseconds>(now - begin).count();
}

template <typename T>
void run_bench()
{
    aya::CSVWriter w(reportFileName());
    w.W("stage", "duration");
    auto begin = std::chrono::steady_clock::now();

    auto back_end = init<T>();
    w.W("init", elapsedNano(begin));
    begin = std::chrono::steady_clock::now();

    back_end->generate(FLAGS_num);
    w.W("generate", elapsedNano(begin));
    begin = std::chrono::steady_clock::now();

    back_end->copy();
    w.W("copy", elapsedNano(begin));
    begin = std::chrono::steady_clock::now();

    if (FLAGS_op == "sort")
    {
        back_end->sort();
    }
    else if (FLAGS_op == "reduce")
    {
        back_end->reduce();
    }
    else
    {
        std::cout << "unknown operation " << FLAGS_op << std::endl;
        // TODO: we should return non-zero, but we also need to copy the clean up code
    }
    w.W("run", elapsedNano(begin));
    begin = std::chrono::steady_clock::now();

    delete back_end;
    w.W("delete", elapsedNano(begin));
}

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
    std::cout << reportFileName() << std::endl;

    // BenchmarkBackend *back_end;

    if (FLAGS_type == "int")
    {
        // back_end = init<int>();
        run_bench<int>();
    }
    else if (FLAGS_type == "float")
    {
        // back_end = init<float>();
        run_bench<float>();
    }
    else if (FLAGS_type == "double")
    {
        // back_end = init<double>();
        run_bench<double>();
    }
    else
    {
        // TODO: this should not be triggered if we defined option validator
        std::cout << "unknown type " << FLAGS_type << std::endl;
        return 1;
    }

    google::ShutDownCommandLineFlags();
    return 0;
}

} // bench
} // aya::bench
