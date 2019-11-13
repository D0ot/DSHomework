#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#include <iostream>
#include <exception>
#include <string>
#include "stackbase.h"


constexpr size_t MAXLEN = 100;

template<typename T>
class SeqStack : public IStack<T>
{
  private:
    T data[MAXLEN];
    size_t length;
  public:
    SeqStack() { length = 0; };
    virtual ~SeqStack() {};
    virtual bool empty() { return length == 0; };
    virtual bool full() { return length == MAXLEN; };
    virtual void push_back(const T& e);
    virtual void pop_back();
    virtual T& back() { return data[length-1];};
    size_t size() { return length; };
    T& operator[](size_t index);

};

template<typename T>
void SeqStack<T>::push_back(const T& e)
{
    if(!full())
    {
        data[length] = e;
        ++length;
    } else
    {
        throw StackException("SeqStack push_back push a full stack");
    }
}

template<typename T>
void SeqStack<T>::pop_back()
{
    if(!empty())
    {
        --length;
    } else
    {
        throw StackException("SeqStack pop_back pop a empty stack");
    }
}
template<typename T>
T& SeqStack<T>::operator[](size_t index)
{
    if(index < length)
    {
        return data[index];
    }
}

#endif