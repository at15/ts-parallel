#include <iostream>
#include <fstream>
#include <vector>

// http://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/
// NOTE: must have this base
void varout()
{
    std::cout << std::endl;
}

// parameter pack http://en.cppreference.com/w/cpp/language/parameter_pack
template <typename T, typename... Targs>
void varout(T value, Targs... Fargs)
{
    std::cout << value;
    // https://stackoverflow.com/questions/3628364/count-of-parameters-in-a-parameter-pack-is-there-a-c0x-std-lib-function-for-t
    if (sizeof...(Fargs) != 0)
    {
        std::cout << ",";
    }
    varout(Fargs...);
}

struct CSVWriter
{
    CSVWriter(std::string file_name) : f(file_name)
    {
    }
    ~CSVWriter()
    {
        f.close();
    }
    void WriteLine()
    {
        f << std::endl;
    }
    template <typename T, typename... TArgs>
    void WriteLine(T value, TArgs... FArgs)
    {
        f << value;
        if (sizeof...(FArgs) != 0)
        {
            f << ",";
        }
        WriteLine(FArgs...);
    }

  private:
    std::ofstream f;
};

void write2(CSVWriter &writer)
{
    writer.WriteLine(3, "jimmy");
}

int main()
{
    // varout(1, 1.2);
    // std::ofstream f("written_by_cpp.csv");
    // f << "id"
    //   << ","
    //   << "name"
    //   << "\n";
    // f << 1 << ","
    //   << "jack"
    //   << "\n";
    // f << 2 << ","
    //   << "marry"
    //   << "\n";
    // f.close();
    CSVWriter writer("written_by_cpp.csv");
    writer.WriteLine("id", "name");
    writer.WriteLine(1, "jack");
    writer.WriteLine(2, "marry");
    write2(writer);
}