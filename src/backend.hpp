#pragma once
#include "common.hpp"

namespace aya
{
namespace backend
{

struct Backend
{
    virtual ~Backend() {}
    template <typename T>
    virtual std::vector<T> topK(const std::vector<T> src, int k);
};

Backend* init();

} // backend
} // aya::backend