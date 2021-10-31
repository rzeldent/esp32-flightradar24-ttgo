#pragma once

#include <stddef.h>

template<typename T, typename A>
const T* binary_array_lookup(const T* array, const size_t array_size, const A item, int (*compare_function)(const T& other, const A value))
{
    // Do a binary search
    auto first = (size_t)0;
    auto last = array_size - 1;
    while (first <= last)
    {
        size_t middle = (first + last) / 2;
        auto result = (*compare_function)(array[middle], item);
        if (result < 0)
            first = middle + 1;
        else if (result > 0)
            last = middle - 1;
        else if (result == 0)
            return &array[middle];
    }

    return nullptr;
}