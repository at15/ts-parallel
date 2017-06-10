#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

namespace aya
{
// NOTE: we need inline to avoid `multiple definition of` error https://stackoverflow.com/a/685467/4116260
// > Include the inline keyword so they are not exported by each object file
inline void ping()
{
    std::cout << "pong from util" << std::endl;
}

inline int toEpoch(const std::string &date)
{
    // std::cout << date << std::endl;
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
}