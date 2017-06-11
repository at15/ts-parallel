#pragma once
#include "common.hpp"

namespace aya
{
namespace backend
{

template<typename T>
struct Backend
{
    virtual ~Backend() {}
    virtual std::vector<T> topK(const std::vector<T> src, int k);
};

template <typename T>
Backend<T>* init();

} // backend
} // aya::backend