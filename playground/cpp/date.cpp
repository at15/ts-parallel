#include <iostream>
#include <sstream>
#include <iomanip>

int main()
{
    std::istringstream d("2017-05-23");
    std::tm t;
    d >> std::get_time(&t, "%Y-%m-%d");
    if (d.fail())
    {
        std::cout << "failed to parse time" << std::endl;
    }
    else
    {
        std::cout << std::put_time(&t, "%c") << std::endl;
    }
    // convert to epoch
    // http://en.cppreference.com/w/cpp/chrono/c/mktime
    std::cout << std::mktime(&t) << std::endl;

    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;

    // FIXME: it becomes Mon May 22 00:00:00 2017
    std::cout << std::put_time(&t, "%c") << std::endl;
    std::cout << std::mktime(&t) << std::endl;
    // convert it manually ... wait, that's a little bit naive ... there are 365 and 366 days ...
    // int ts = 0;
    // ts += (t.tm_year - 1970) * ()
}
