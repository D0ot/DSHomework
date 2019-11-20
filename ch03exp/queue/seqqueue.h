#ifndef SEQ_QUEUE_H
#define SEQ_QUEUE_H

#include "queuebase.h"




template<typename T, size_t N = 100>
class SeqQueue : public IQueue<T>
{

  private:
    T d_data[N];
    size_t d_front;
    size_t d_rear;
  public:
    SeqQueue() : d_front(0), d_rear(0) {};
    virtual void enQueue(const T& e);
    virtual void deQueue();
    virtual bool full();
    virtual bool empty();
    virtual const T& front();
    virtual size_t size();
    virtual void traverse(std::function<void(const T&)> f);
};


template<typename T, size_t N>
void SeqQueue<T, N>::enQueue(const T& e)
{
    if(!full())
    {
        d_rear = (d_rear + 1) % N;
        d_data[d_rear] = e;
    }
    else
    {
        throw QueueException("a full called enQueue()");
    }
}


template<typename T, size_t N>
void SeqQueue<T, N>::deQueue()
{
    if(!empty())
    {
        d_front = (d_front + 1) % N;
    }
    else 
    {
        throw QueueException("an empty called deQueue()");
    }
}
template<typename T, size_t N>
bool SeqQueue<T, N>::full()
{
    return (d_rear + 1)%N == d_front;
}
template<typename T, size_t N>
bool SeqQueue<T, N>::empty()
{
    return d_rear == d_front;
}
template<typename T, size_t N>
const T& SeqQueue<T, N>::front()
{
    if(!empty())
    {
        return d_data[(d_front + 1) % N];
    }

    throw QueueException("an empty called front()");
}
template<typename T, size_t N>
size_t SeqQueue<T, N>::size()
{
    return (N + d_rear - d_front) % N;
}


template<typename T, size_t N>
void SeqQueue<T, N>::traverse(std::function<void(const T&)> f)
{

    size_t i = d_front;
    while(i != d_rear)
    {
        i = (i + 1) % N;
        f(d_data[i]);
    }
}
#endif