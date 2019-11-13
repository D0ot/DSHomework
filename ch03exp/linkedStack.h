#ifndef LINKED_STACK_H
#define LINKED_STACK_H


#include "stackbase.h"

template <typename T>
struct Node
{
    T data;
    Node<T> *next;
};

template <typename T>
class LinkedStack : public IStack<T>
{
  private:
    Node<T> *head;

    void destory();
    
  public:
    LinkedStack() {
        head = new Node<T>;
        head->next = nullptr;
    };

    virtual void push_back(const T& e);
    virtual void pop_back();
    virtual bool empty() { return head->next == nullptr; };
    virtual bool full() { return false; };
    virtual T& back();
    virtual ~LinkedStack() { destory(); };
};



template <typename T>
void LinkedStack<T>::destory()
{
    Node<T>* iter = head;
    Node<T>* tmp;
    while(iter)
    {
        tmp = iter;
        iter = iter->next;
        delete tmp;
    }
}

template <typename T>
void LinkedStack<T>::push_back(const T& e)
{
    Node<T>* tmp = new Node<T>;
    tmp->data = e;
    tmp->next = head->next;
    head->next = tmp;
}


template <typename T>
void LinkedStack<T>::pop_back()
{
    if(!empty())
    {
       Node<T> *tmp; 
       tmp = head->next;
       head->next = tmp->next;
       delete tmp;
    } else
    {
        throw StackException("LinkedStack pop_back()");
    }
}

template <typename T>
T& LinkedStack<T>::back()
{
    if(!empty())
    {
        return head->next->data;
    } else
    {
        throw StackException("LinkedStack back()");
    }
}



#endif 