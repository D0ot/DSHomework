/**
 * @file : ch02/q9.h
 * @author : D0ot at github
 * @date : 2019/9/23
 *      this applies to question 2.6 2.7
 */

#ifndef CH02Q9_H
#define CH02Q9_H

#include "q3.h"

/**
 * it is same with :
 *      a = a - b;
 */
template<typename T>
void SeqSetMinusInPlace(SeqSet<T>& a, const SeqSet<T>& b)
{
    size_t i = 0, j = 0, k = 0;
    while(i < a.size() && j < b.size())
    {
        if(a[i] < b[j])
        {
            a[k] = a[i];
            ++i;
            ++k;
        } else 
        {
            if(a[i] == b[j])
            {
                ++i;
            }
            ++j;
        }
    }
    a.resize(k);
}


#endif