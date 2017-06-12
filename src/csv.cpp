#include "common.hpp"

#define CSV_INT 1
#define CSV_FLOAT 2
#define CSV_STRING 3

DEFINE_string(file, "at15.csv", "csv file");
DEFINE_string(schema, "", "csv schema");

std::vector<std::string> splitAsString(const std::string line)
{
    std::cout << line << std::endl;
    std::vector<std::string> values;
    std::stringstream line_stream;
    std::string cell;
    line_stream << line;
    while (std::getline(line_stream, cell, ','))
    {
        values.push_back(cell);
    }
    std::cout << values.size() << std::endl;
    return values;
}

int main(int argc, char **argv)
{
    std::string usage = R"HA(
csv
    --file   string sort|reduce
    --schema string s,s,s,i
    --type string int|float|double
)HA";

    google::SetUsageMessage(usage);
    gflags::SetVersionString("0.0.1");

    if (argc < 2)
    {
        std::cout << google::ProgramUsage();
        return 0;
    }

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::string file_name = FLAGS_file;
    std::string schema = FLAGS_schema;
    std::vector<int> column_types;

    if (schema == "")
    {
        std::cout << "must specify schema\n";
        return 1;
    }

    std::stringstream line_stream;
    std::string cell;
    line_stream << schema;
    while (std::getline(line_stream, cell, ','))
    {
        if (cell == "i")
        {
            column_types.push_back(CSV_INT);
        }
        else if (cell == "f")
        {
            column_types.push_back(CSV_FLOAT);
        }
        else if (cell == "s")
        {
            column_types.push_back(CSV_STRING);
        }
        else
        {
            std::cout << "unknown column type " << cell << std::endl;
            return 1;
        }
    }

    for (const auto &i : column_types)
    {
        std::cout << i << " ";
    }

    std::ifstream f(file_name);
    if (!f.is_open())
    {
        std::perror("failed to open file");
        return 1;
    }

    std::string line;
    std::getline(f, line);
    std::cout << line << std::endl;
    std::vector<std::string> header = splitAsString(line);
    std::cout << header.size() << std::endl;
    for (const auto &h : header)
    {
        std::cout << h << " ";
    }

    google::ShutDownCommandLineFlags();
    return 0;
}