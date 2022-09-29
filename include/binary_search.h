#pragma once

#include <stddef.h>

template <typename T, typename A, size_t array_size>
const T *binary_array_lookup(const T (&values)[array_size], const A item, int (*compare_function)(const T &other, const A value))
{
    // Do a binary search
    int cmp;
    auto first = 0;
    auto last = (int)array_size - 1;
    while (first <= last)
    {
        auto middle = (first + last) / 2;
        // Compare function should return <0, 0 or >0
        if ((cmp = (*compare_function)(values[middle], item)) == 0)
            return &values[middle];
        if (cmp < 0)
            first = middle + 1;
        else
            last = middle - 1;
    }

    return nullptr;
}