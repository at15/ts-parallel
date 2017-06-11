#pragma once
#include "common.hpp"

namespace aya
{
namespace backend
{

void ping();

template <typename T>
struct Backend
{
    virtual ~Backend() {}
    virtual std::vector<T> topK(const std::vector<T> src, int k);
};

template <typename T>
Backend<T> *init();

inline Backend<int> *initInt()
{
    return init<int>();
}

} // backend
} // aya::backend