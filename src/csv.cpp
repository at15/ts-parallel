#include "common.hpp"

#ifdef WAKA_BOOST
#include "backend/boost/backend.hpp"
#endif

#ifdef WAKA_THRUST
#include "backend/thrust/backend.hpp"
#endif

#define CSV_INT 1
#define CSV_FLOAT 2
#define CSV_STRING 3

DEFINE_string(file, "at15.csv", "csv file");
DEFINE_string(schema, "s,s,s,i", "csv schema");

std::vector<std::string> splitAsString(const std::string line)
{
    std::vector<std::string> values;
    std::stringstream line_stream;
    std::string cell;
    line_stream << line;
    while (std::getline(line_stream, cell, ','))
    {
        values.push_back(std::move(cell));
    }
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
    line_stream.clear();

    for (const auto &i : column_types)
    {
        std::cout << i << std::endl;
    }

    std::ifstream f(file_name);
    if (!f.is_open())
    {
        std::perror("failed to open file");
        return 1;
    }

    std::string line;
    std::getline(f, line);

    std::vector<std::string> header = splitAsString(line);

    std::cout << header[0] << std::endl;
    std::cout << header[1] << std::endl;

    // FIXME: we use fixed data
    std::vector<std::string> days;
    std::vector<std::string> projects;
    std::vector<std::string> file_names;
    std::vector<int> edit_durations;
    int unsupported_rows = 0;
    while (std::getline(f, line))
    {
        int i = 0;
        line_stream << line;
        while (std::getline(line_stream, cell, ','))
        {
            switch (i)
            {
            case 0:
                days.push_back(std::move(cell));
                break;
            case 1:
                projects.push_back(std::move(cell));
                break;
            case 2:
                file_names.push_back(std::move(cell));
                break;
            case 3:
                try
                {
                    // broken by 2015-10-17,LostMie,"/Users/gpl/repos/github.com/dyweb/LostMie/index,hs.js",16
                    edit_durations.push_back(std::stoi(cell));
                }
                catch (const std::invalid_argument)
                {
                    unsupported_rows++;
                    edit_durations.push_back(0);
                }

                break;
            }
            i++;
        }
        line_stream.clear();
    }
    std::cout << "unsupported rows (due to quote) " << unsupported_rows << std::endl; // just 1 ... ok

    auto int_backend = aya::backend::init<int>();
    auto top_10 = int_backend->topK(edit_durations, 10);
    for (int i = 0; i < 10; i++)
    {
        std::cout << top_10[i] << std::endl;
    }
    std::vector<int> indices(10);
    top_10 = int_backend->topK(edit_durations, 10, indices);
    for (int i = 0; i < 10; i++)
    {
        std::cout << top_10[i] << " " << indices[i] << std::endl;
    }
    delete int_backend;

    google::ShutDownCommandLineFlags();
    return 0;
}