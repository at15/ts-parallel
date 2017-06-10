#include "common.hpp"

DEFINE_string(data, "../data/at15.json", "wakatime json dump");

int toEpoch(const std::string &date)
{
    std::cout << date << std::endl;
    std::istringstream ss(date);
    // TODO: it seems {} is a must, otherwise we got trash value
    std::tm t = {};
    ss >> std::get_time(&t, "%Y-%m-%d");
    if (ss.fail())
    {
        std::cout << "failed to convert time" << std::endl;
    }
    // FIXME: the hour, minute, second are all -1, see playgroudn/cpp/date.cpp
    return std::mktime(&t);
}

int main(int argc, char **argv)
{
    std::string usage("Wakatime dump analysis. \n");
    usage += "\t--data string data file location (default is ../data/at15.json)\n";
    google::SetUsageMessage(usage);
    gflags::SetVersionString("0.0.1");

    // NOTE: gflags will change argc, so we check it before parse
    if (argc < 2)
    {
        std::cout << google::ProgramUsage();
        return 0;
    }

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::string data_path = FLAGS_data;
    std::cout << "open file " << data_path << std::endl;
    std::ifstream data_stream(data_path);
    json data_json;
    data_stream >> data_json;
    std::cout << "number of entries " << data_json.size() << std::endl;
    std::cout << "number of days " << data_json["days"].size() << std::endl;
    for (auto &day : data_json["days"])
    {
        std::string date = day.value("date", "");
        std::cout << day["date"] << std::endl;
        // std::cout << toEpoch(day["date"]) << std::endl;
        std::cout << toEpoch(date) << std::endl;
    }

    // TODO: access value https://github.com/nlohmann/json/blob/develop/doc/examples/basic_json__value.cpp

    google::ShutDownCommandLineFlags();
    return 0;
}