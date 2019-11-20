#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include <iostream>
#include "queuebase.h"


// rear is head of list
// enQueue is tail insert


template<typename T>
struct SLLNode
{
    SLLNode();
    SLLNode(const T& d, SLLNode<T>* const n) : data(d), next(n) {}
    T data;
    SLLNode<T>* next;
    
};


template<typename T>
class ListQueue : public IQueue<T>
{
    SLLNode<T> *d_front;
    SLLNode<T> *d_rear;

    public:
    ListQueue() : d_front(nullptr), d_rear(nullptr) {};
    void destory();
    virtual void enQueue(const T& e);
    virtual void deQueue();
    virtual bool full();
    virtual bool empty(); 
    virtual const T& front();
    virtual size_t size();
    virtual ~ListQueue() { destory(); };
    virtual void traverse(std::function<void(const T&)> f);
};

template<typename T>
void ListQueue<T>::destory()
{
    while (!empty())
    {
        deQueue();
    }
    
}

template<typename T>
void ListQueue<T>::enQueue(const T& e)
{
    SLLNode<T> *p = new SLLNode<T>(e, nullptr);
    if(d_rear == nullptr)
    {
        d_rear = p;
        d_front = p;
    } else
    {
        d_rear->next = p;
        d_rear = p;
    }
}

template<typename T>
void ListQueue<T>::deQueue()
{
    if(empty())
    {
        throw QueueException("an empty called deQueue");
    }

    if(d_front == d_rear)
    {
        delete d_front;
        d_front = nullptr;
        d_rear = nullptr;
    } else
    {
        SLLNode<T>* p = d_front->next;
        delete d_front;
        d_front = p;
    }
}


template<typename T>
bool ListQueue<T>::full()
{
    return false;
}

template<typename T>
bool ListQueue<T>::empty()
{
    return d_front == nullptr;
}


template<typename T>
const T& ListQueue<T>::front()
{
    if(!empty())
    {
        return d_front->data;
    }
    else
    {
        throw QueueException("an empty call front()");
    }

}


template<typename T>
size_t ListQueue<T>::size()
{
    SLLNode<T> *iter = d_front;
    size_t count = 0;
    while(iter)
    {
        ++count;
        iter = iter->next;
    }
    return count;
}


template<typename T>
void ListQueue<T>::traverse(std::function<void(const T&)> f)
{
    SLLNode<T> *iter = d_front;
    while(iter)
    {
        f(iter->data);
        iter = iter->next;
    }
}





#endif