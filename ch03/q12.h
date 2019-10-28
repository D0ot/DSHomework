#ifndef CH03_Q12_H
#define CH03_Q12_H

#include <iostream>

// q12 q13 q14

void P1(int w)
{
    int a, b;
    a = w - 1;
    b = w + 1;
    std::cout << a << b;
}

void P2(int w)
{
    int a, b;
    a = 2 * w;
    b = w * w;
    P1(a);
    P1(b);
    std::cout << a << b;
}


void P(int w)
{
    if(w > 0)
    {
        P(w-1);
        P(w-1);
        std::cout << w;
    }
}

void P3(int N, int* F)
{
    if(N == 0)
    {
        *F = 0;
    }else
    {
        P3(N-1, F);
        *F = *F + N;
    }
}

int ack(int m, int n)
{
    if(m == 0)
    {
        return n + 1;
    } else if (n == 0)
    {
        return ack(m-1, 1);
    } else
    {
        return ack(m-1, ack(m, n-1));
    }
}


#endif