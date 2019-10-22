#ifndef CH03_Q2_H
#define CH03_Q2_H

#include <iostream>

template<typename T, size_t N>
class Stack
{
private:
    T data[N];
    size_t count;
public:
    Stack();
    virtual ~Stack();

    bool empty();
    bool full();
    bool push(const T &e);
    bool pop();
    bool getTop(T &e);
    void print();

};


template<typename T, size_t N>
Stack<T, N>::Stack()
{
    count = 0;
}

template<typename T, size_t N>
Stack<T, N>::~Stack()
{

}


template<typename T, size_t N>
bool Stack<T, N>::empty()
{
    return count == 0;
}


template<typename T, size_t N>
bool Stack<T, N>::full()
{
    return count == N;
}

template<typename T, size_t N>
bool Stack<T, N>::push(const T &e)
{
    if(full())
    {
        return false;
    }

    data[count++] = e;
    return true;
}

template<typename T, size_t N>
bool Stack<T, N>::pop()
{
    if(empty())
    {
        return false;
    }
    --count;
    return true;
}


template<typename T, size_t N>
bool Stack<T, N>::getTop(T &e)
{
    if(empty())
    {
        return false;
    }

    return data[count-1];
}


template<typename T, size_t N>
void Stack<T, N>::print()
{
    for(size_t i = 0; i < count; ++i)
    {
        std::cout << data[i] << ' ';
    }
}


#endif