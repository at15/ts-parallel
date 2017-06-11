#pragma once

namespace aya
{
namespace bench
{
void ping();
std::string name();
template<typename T> void sort(int num);

int launch(int argc, char **argv);
}
}