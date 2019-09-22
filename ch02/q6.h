/**
 * @file : ch02/q6.h
 * @author : D0ot at github
 * @date : 2019/9/22
 *      this applies to question 2.6 2.7
 */

#ifndef CH02Q6_H
#define CH02Q6_H

#include <array>

// return size of result

template<typename T>
size_t makeItUnique(std::array<T, 0> data)
{
    return 0;
}

template<typename T, size_t N>
size_t makeItUnique(std::array<T, N> &data)
{
    size_t ret = 0;
    for(size_t i = 1; i < N; ++i)
    {
        if(data[ret] != data[i])
        {
            data[++ret] = data[i];
        }

    }
    return ret + 1;
}


#endif