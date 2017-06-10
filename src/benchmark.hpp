#pragma once

namespace aya
{
namespace bench
{
void ping();

static void launch(int argc, char **argv)
{
    std::cout << "let's run some benchmark" << std::endl;
    aya::ping();
    ping();
}
}
}