/**
 * @file: ch02/q3.cpp
 * @author: D0ot at github
 * @date: 2019/9/21
 *      This file applies to question 2.3 2.8 2.9
 */
#ifndef CH02Q3_H
#define CH02Q3_H
#include <iostream>
#include <cstring>





// The type "T" must can be compared
// maybe we can use concepts later

template<typename T>
class SeqSet
{
    T* m_ptr;
    size_t m_size;
    size_t m_alloc_size;

    bool insertAtIndex(const T& v, size_t index);

    // it will acquire a new space and
    // move the elements to there
    // then release the old memory
    void acquireMemory(size_t alloc_size);

    // will not clear memory allocated
    bool removeAtIndex(size_t index);


    size_t binaryFind(const T& v);

  public:
    SeqSet(size_t pre_size);
    ~SeqSet();
    SeqSet(const SeqSet& s);

    bool insert(const T& v);
    bool remove(const T& v);
    size_t size() const {return m_size;};

    // clear all the acquired memory
    void clear();
    T& operator[](size_t index);
    const T& operator[](size_t index)const;
    SeqSet &operator=(const SeqSet & s);
    SeqSet operator&(const SeqSet & s);
    SeqSet operator|(const SeqSet & s);
    SeqSet operator-(const SeqSet & s);

};

template<typename T>
std::ostream &operator<<(std::ostream & os, const SeqSet<T> & s)
{
    for(size_t i = 0; i < s.size(); ++i)
    {
        os << s[i] << ' ';
    }
    return os;
    
}

template<typename T>
bool SeqSet<T>::insertAtIndex(const T& v, size_t index)
{
    if(index > m_size)
    {
        return false;
    }

    if(m_size + 1 > m_alloc_size)
    {
        acquireMemory((m_size + 1) * 2);
    }

    size_t i = m_size;
    for(; index < i; --i)
    {
        m_ptr[i] = m_ptr[i-1];
    }
    m_ptr[index] = v;

    m_size++;
    return true;
}

template<typename T>
bool SeqSet<T>::removeAtIndex(size_t index)
{
    if(index >= m_size)
    {
        return false;
    }

    m_size--;
    for(size_t i = index; i < m_size; ++i)
    {
        m_ptr[i] = m_ptr[i+1];
    }
    return true;

}

template<typename T>
size_t SeqSet<T>::binaryFind(const T& v)
{
    size_t left = 0, right = m_size-1, middle;
    while(left + 1 < right)
    {
        middle = left + (right - left) / 2;

        if(m_ptr[middle] == v)
        {
            return middle;
        }

        if(m_ptr[middle] < v)
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }

    if(v <= m_ptr[left])
    {
        return left;
    }

    if(v > m_ptr[right])
    {
        return right + 1;
    }

    
    return right;
    
}

// assume the arguments are correct
template<typename T>
void SeqSet<T>::acquireMemory(size_t alloc_size)
{
    auto* old_ptr = m_ptr;
    m_ptr = new T[alloc_size];
    m_alloc_size = alloc_size;

    for(size_t i = 0; i < m_size; ++i)
    {
        m_ptr[i] = old_ptr[i];
    }
    delete[] old_ptr;

}

template<typename T>
SeqSet<T>::SeqSet(size_t pre_size) : m_ptr(new T[pre_size]), m_size(0), m_alloc_size(pre_size)
{
}

template<typename T>
SeqSet<T>::SeqSet(const SeqSet<T> & s)
{
    m_alloc_size = s.m_alloc_size;
    m_ptr = new T[m_alloc_size];
    m_size = s.m_size;
    std::memcpy(static_cast<void*>(m_ptr), static_cast<void*>(s.m_ptr), m_size*sizeof(T));
}

template<typename T>
SeqSet<T>::~SeqSet()
{
    if(m_ptr != nullptr)
    {
        delete[] m_ptr;
        m_ptr = nullptr;
        m_size = 0;
    }
}

template<typename T>
bool SeqSet<T>::insert(const T& v)
{

    if(m_size == 0)
    {
        return insertAtIndex(v, 0);
    }

    size_t pos = binaryFind(v);

    if(pos == m_size)
    {
        return insertAtIndex(v, m_size);
    }

    if(m_ptr[pos] < v)
    {
        return insertAtIndex(v, pos+1);
    } else if (m_ptr[pos] > v)
    {
        return insertAtIndex(v, pos);
    } else
    {
        return false;
    }
}

template<typename T>
bool SeqSet<T>::remove(const T& v)
{
    if(m_size == 0)
    {
        return false;
    }

    size_t pos = binaryFind(v);

    if(m_ptr[pos] == v)
    {
        return removeAtIndex(pos);
    }else
    {
        return false;
    }
}

template<typename T>
void SeqSet<T>::clear()
{
    delete[] m_ptr;
    m_ptr = nullptr;
    m_size = 0;
    m_alloc_size = 0;
}

template<typename T>
T& SeqSet<T>::operator[] (size_t index)
{
    return m_ptr[index];
}

template<typename T>
const T& SeqSet<T>::operator[](size_t index)const
{
    return m_ptr[index];
}

template<typename T>
SeqSet<T> SeqSet<T>::operator&(const SeqSet<T> & s)
{
    SeqSet<T> ret(std::min(m_size, s.m_size));
    size_t i = 0, j = 0;
    while(i < m_size && j < s.m_size)
    {
        if(m_ptr[i] < s.m_ptr[j])
        {
            ++i;
        } else if (m_ptr[i] > s.m_ptr[j])
        {
            ++j;
        } else
        {
            ret.insertAtIndex(m_ptr[i], ret.size());
            ++i;
            ++j;
        }
    }
    return ret;
}

template<typename T>
SeqSet<T> SeqSet<T>::operator|(const SeqSet<T> & s)
{
    SeqSet<T> ret(m_size + s.m_size);
    size_t i = 0, j = 0;
    while(i < m_size && j < s.m_size)
    {
        if(m_ptr[i] < s.m_ptr[j])
        {
            ret.insertAtIndex(m_ptr[i], ret.size());
            ++i;
        } else if(m_ptr[i] > s.m_ptr[j])
        {
            ret.insertAtIndex(s.m_ptr[j], ret.size());
            ++j;
        } else
        {
            ret.insertAtIndex(m_ptr[i], ret.size());
            ++i;
            ++j;
        }
    }

    while(i < m_size)
    {
        ret.insertAtIndex(m_ptr[i++], ret.size());
    }

    while(j < s.m_size)
    {
        ret.insertAtIndex(s.m_ptr[j++], ret.size());
    }

    return ret;
}

template<typename T>
SeqSet<T> SeqSet<T>::operator-(const SeqSet<T> & s)
{
    // a - b
    // in a but not in b
    SeqSet<int> ret(std::max(m_size, s.m_size));
    size_t i = 0, j = 0;
    while(i < m_size && j < s.m_size)
    {
        if(m_ptr[i] < s.m_ptr[j])
        {
            ret.insertAtIndex(m_ptr[i], ret.size());
            ++i;
        } else if(m_ptr[i] > s.m_ptr[j])
        {
            ++j;
        } else
        {
            ++i;
            ++j;
        }
    }

    while(i < m_size)
    {
        ret.insertAtIndex(m_ptr[i], ret.size());
        ++i;
    }

    return ret;
}

#endif 