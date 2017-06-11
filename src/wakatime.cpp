#include "common.hpp"
#include "../third_party/json.hpp"

#include "backend.hpp"

using json = nlohmann::json;

DEFINE_string(data, "../data/at15.json", "wakatime json dump");

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

    std::vector<int> days;
    std::vector<std::string> projects;
    std::vector<std::string> file_names;
    std::vector<int> edit_durations;

    for (auto &day : data_json["days"])
    {
        std::string date = day.value("date", "");
        // std::cout << day["date"] << std::endl;
        // std::cout << toEpoch(day["date"]) << std::endl;
        // std::cout << toEpoch(date) << std::endl;
        for (auto &project : day["projects"])
        {
            std::string project_name = project.value("name", "");
            // std::cout << project["name"] << std::endl;
            for (auto &entity : project["entities"])
            {
                // std::cout << entity["name"] << std::endl;
                std::string file_name = entity.value("name", "");
                int edit_duration = entity.value("total_seconds", 0);
                days.push_back(aya::toEpoch(date));
                projects.push_back(project_name);
                file_names.push_back(std::move(file_name));
                edit_durations.push_back(edit_duration);
            }
        }
    }

    int num_rows = days.size();
    std::cout << "total " << num_rows << " rows" << std::endl;
    for (int i = 0; i < 20; i++)
    {
        std::cout << i << " " << days[i] << " " << projects[i] << " " << file_names[i] << " " << edit_durations[i] << std::endl;
    }

    auto int_backend = aya::backend::init<int>();
    auto top_10 = int_backend->topK(edit_durations, 10);
    for (int i = 0; i < 10; i++)
    {
        std::cout << top_10[i] << std::endl;
    }
    delete int_backend;

    google::ShutDownCommandLineFlags();
    return 0;
}