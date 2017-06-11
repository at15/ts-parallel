#include <iostream>

struct BenchmarkBackend {
    virtual void generate() = 0;
    virtual void copy() = 0;
};

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
};

int main(){

}