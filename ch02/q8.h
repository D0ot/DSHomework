/**
 * @file : ch02/q8.h
 * @author : D0ot at github
 * @date : 2019/9/23
 *      this applies to question 2.6 2.7
 */

#ifndef CH02Q8_H
#define CH02Q8_H

#include "q3.h"

/**
 * it is same with :
 *      a = a & b
 * 
 */
template<typename T>
void SeqSetAndInPlace(SeqSet<T>& a, const SeqSet<T>& b)
{
    size_t i = 0, j = 0, k = 0;
    while(i < a.size() && j < b.size())
    {
        if(a[i] < b[j])
        {
            ++i;
        } else if (a[i] > b[j])
        {
            ++j;
        } else 
        {
            a[k] = b[j];
            ++i;
            ++j;
            ++k;
        }
    }
    a.resize(k);
}



#endif