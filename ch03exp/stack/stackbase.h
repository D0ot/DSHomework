#ifndef STACKBASE_H
#define STACKBASE_H

template<typename T>
class IStack
{
  public:
    virtual void push_back(const T& e) = 0;
    virtual void pop_back() = 0;
    virtual bool empty() = 0;
    virtual bool full() = 0;
    virtual T& back() = 0;
    virtual ~IStack(){};
};

class StackException : public std::exception
{
  private:
    std::string msg;
  public:
    StackException(const std::string& m) : msg(m) {};
    virtual const char *what() const noexcept { return msg.c_str(); };
};


#endif