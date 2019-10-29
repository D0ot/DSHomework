#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <iostream>
#include <exception>
#include <functional>


template<typename T>
struct SLLNode
{
    T data;
    SLLNode<T> *next;
    SLLNode(){}
    SLLNode(const T& d, SLLNode<T>* n) : data(d), next(n){};
};


template<typename T>
class SingleLinkedList
{
    template<typename P>
    friend std::ostream& operator<<(std::ostream& os, SingleLinkedList<P>& sll);
private:
    SLLNode<T> *m_head;
    bool m_log;
protected:
    void init();
    void destory();
    void insert(SLLNode<T> *p, const T& e);
    void remove(SLLNode<T> *p);
    SLLNode<T> *indexToPointer(const size_t index);
    SLLNode<T> *head();
    SLLNode<T> *tail();
    SLLNode<T> *find(std::function<bool(const T& e)> predicate);


public:
    SingleLinkedList();
    virtual ~SingleLinkedList();
    void insert(const size_t index, const T& e);
    void remove(const size_t index);
    size_t size();
    void insertTail(const T& e);
    void insertHead(const T& e);
    T& operator[](const size_t index);
    SLLNode<T> *find(const T&e);

    // for exp purpose

    void enableLog(bool e);
};

template<typename T>
void SingleLinkedList<T>::init()
{
    m_head = new SLLNode<T>();
    m_head->next = nullptr;
    m_log = false;
}

template<typename T>
void SingleLinkedList<T>::destory()
{
    auto tmp = m_head;
    if(m_log)
    {
        std::cout << "Destory the SLL\n";
    }
    while(tmp)
    {
       auto tmp2 = tmp;
       tmp = tmp->next;
       if(m_log)
       {
           std::cout << "Delete the SLLNode{" << tmp2->data  << ", " <<tmp2->next << "} @ " << tmp2 << std::endl;
       }
       delete tmp2;
    }
    m_head = nullptr;
    if(m_log)
    {
        std::cout << "Destory done\n";
    }
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList()
{
    init();
}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    destory();
}


template<typename T>
void SingleLinkedList<T>::insert(SLLNode<T> *p, const T& e)
{
    auto tmp = p->next;
    p->next = new SLLNode<T>(e, tmp);
}

template<typename T>
void SingleLinkedList<T>::remove(SLLNode<T> *p)
{
    auto tmp = p->next->next;
    delete p->next;
    p->next = tmp;
}


// get the parent of the index
template<typename T>
SLLNode<T> *SingleLinkedList<T>::indexToPointer(const size_t index)
{
    if(index == 0)
    {
        throw std::invalid_argument("SingleLinkedList<T>::indexToPointer, index is 0");
    }
    size_t counter = index - 1;
    auto iter = m_head;
    while(iter != nullptr && counter != 0)
    {
        iter = iter->next;
        --counter;
    }

    if(iter == nullptr)
    {
        throw std::invalid_argument("SingleLinkedList<T>::countdwon, index out of range");
    }

    return iter;
}

template<typename T>
SLLNode<T>* SingleLinkedList<T>::head()
{
    return m_head;
}

template<typename T>
SLLNode<T>* SingleLinkedList<T>::tail()
{
    auto last = m_head;
    auto iter = m_head->next;
    while(iter)
    {
        last = iter;
        iter = iter->next;
    }
    return last;
}

template<typename T>
void SingleLinkedList<T>::insert(const size_t index, const T& e)
{
    insert(indexToPointer(index), e);
}

template<typename T>
void SingleLinkedList<T>::remove(const size_t index)
{
    remove(indexToPointer(index));
}

template<typename T>
size_t SingleLinkedList<T>::size()
{
    size_t count = 0;
    auto iter = m_head->next;
    while(iter)
    {
        iter = iter->next;
        ++count;
    }
    return count;
}

template<typename T>
void SingleLinkedList<T>::insertTail(const T& e)
{
    insert(tail(), e);
}

template<typename T>
void SingleLinkedList<T>::insertHead(const T& e)
{
    insert(m_head, e);
}

template<typename T>
T& SingleLinkedList<T>::operator[](const size_t index)
{
    SLLNode<T> *tmp;
    try 
    {
        tmp = indexToPointer(index)->next;
    }
    catch(std::invalid_argument& e)
    {
        throw std::invalid_argument("error, SingleLinkedList<T>::operator[], index out of range");
    }
    if(tmp == nullptr)
    {
       throw std::invalid_argument("error, SingleLinkedList<T>::operator[], index out of range");
    }
    return tmp->data;
    
}

template<typename T>
SLLNode<T> *SingleLinkedList<T>::find(std::function<bool(const T& e)> predicate)
{
    auto iter = m_head->next;
    while(iter)
    {
        if(predicate(iter->data))
        {
            return iter;
        }
    }
    return nullptr;
}

template<typename T>
SLLNode<T> *SingleLinkedList<T>::find(const T& e)
{
    auto predicate = [&e](const T& i) {
        if(i == e)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    return find(predicate);
}


template<typename T>
void SingleLinkedList<T>::enableLog(bool e)
{
    m_log = e;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, SingleLinkedList<T>& sll)
{
    auto iter = sll.head()->next;
    while(iter)
    {
        std::cout << iter->data << ' ';
        iter = iter->next;
    }
    return os;
}

#endif