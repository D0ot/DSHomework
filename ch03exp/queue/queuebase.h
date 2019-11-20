#ifndef QUEUEBASE_H
#define QUEUEBASE_H


#include <iostream>
#include <exception>
#include <functional>

class QueueException : public std::exception
{
  private:
    std::string msg;
  public:
    QueueException(const std::string& m) : msg(m) {};
    virtual const char *what() const noexcept { return msg.c_str(); };
};


template<typename T>
class IQueue
{
    public:
    virtual void enQueue(const T& e) = 0;
    virtual void deQueue() = 0;
    virtual bool full() = 0;
    virtual bool empty() = 0; 
    virtual const T& front() = 0;
    virtual size_t size() = 0;
    virtual void traverse(std::function<void(const T&)> f) = 0;
    virtual ~IQueue() {};
};

#endif