#ifndef CH02_EXP_H
#define CH02_EXP_H

/**
 * @file : ch02exp.h
 * @author : doot
 * @date : 2019/10/15
 * @brief :
 *  the content of "Date Strture" class of chapter 2.
 */

#include <iostream>

void error(const std::string & msg)
{
    std::cerr << "error, msg : " << msg;
    while(1);
}




template<typename T>
class SeqList
{
    // "m_" means "member"
private:
    T* m_ptr;
    size_t m_allocated_size;
    size_t m_size;
public:
    SeqList(size_t n);
    ~SeqList():

    bool insertAtBack(const T& data);

    bool insertAtIndex(size_t index, const T& data);
    bool removeAtIndex(size_t index);

    T& operator[](size_t index);

};


template<typename T>
SeqList<T>::SeqList(size_t n)
{
    if(n == 0)
    {
        error("SeqList::SeqList(size_t n), n == 0")
    }

    m_allocated_size = n;
    m_ptr = new T[n];

    m_size = 0;
}

template<typename T>
SeqList<T>::~SeqList()
{
    delete m_ptr;
}


template<typename T>
T& SeqList<T>::operator[](size_t index)
{
    if(index >= m_size)
    {
        error("SeqList::~SeqList(), index >= m_size;")
    }
    return m_ptr[index];
}




#endif //CH02_EXP_H