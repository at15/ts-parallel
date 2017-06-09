#include <iostream>
#include <gflags/gflags.h>

// https://jieliu.gitbooks.io/systemlevelapplicationdev/content/%E7%AC%AC%E4%BA%8C%E7%AB%A0_1.1%E5%91%BD%E4%BB%A4%E8%A1%8C%E5%8F%82%E6%95%B0.html
// http://dreamrunner.org/blog/2014/03/09/gflags-jian-ming-shi-yong/

DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german",
              "comma-separated list of languages to offer in the 'lang' menu");

int main(int argc, char **argv)
{
    google::SetUsageMessage("usage?");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "argc=" << argc << std::endl;
    if (FLAGS_big_menu)
    {
        std::cout << "big menu is true" << std::endl;
    }
    else
    {
        std::cout << "big menu is false" << std::endl;
    }
}