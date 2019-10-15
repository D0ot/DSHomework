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
#include <string>
#include <cstring>
#include <exception>


template<typename T>
class SeqList
{
    T* m_ptr;
    size_t m_size;
    size_t m_alloc_size;


    // it will acquire a new space and
    // move the elements to there
    // then release the old memory
    void acquireMemory(size_t alloc_size);

    // will not clear memory allocated
    size_t binaryFind(const T& v);

  public:
    SeqList();
    SeqList(size_t pre_size);
    ~SeqList();
    SeqList(const SeqList& s);


    // get the back element
    // WARNING : there are no check
    T& back() { return m_ptr[m_size-1];};


    // insert an element at 'index'
    bool insertAtIndex(const T& v, size_t index);

    // insert an element at back of SeqList
    // same as "insertAtIndex(v, m_size)"
    void insertAtBack(const T& v);

    bool removeAtIndex(size_t index);

    bool uniqueOrderedInsert(const T& v);


    bool orderedInsert(const T& v);
    bool uniqueInsert(const T& v);


    bool remove(const T& v);


    size_t size() const {return m_size;};

    // clear all the acquired memory
    void clear();

    // resize SeqList to length 
    // m_size = length
    // and elements beyond length will be discarded
    bool resize(size_t length);

    T& operator[](size_t index);
    const T& operator[](size_t index)const;
    SeqList &operator=(const SeqList & s);
    SeqList operator&(const SeqList & s);
    SeqList operator|(const SeqList & s);
    SeqList operator-(const SeqList & s);

};

template<typename T>
std::ostream &operator<<(std::ostream & os, const SeqList<T> & s)
{
    for(size_t i = 0; i < s.size(); ++i)
    {
        os << s[i] << ' ';
    }
    return os;
    
}

template<typename T>
bool SeqList<T>::insertAtIndex(const T& v, size_t index)
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
void SeqList<T>::insertAtBack(const T& v)
{
    insertAtIndex(v, m_size);
}


template<typename T>
bool SeqList<T>::removeAtIndex(size_t index)
{
    if(index >= m_size)
    {
        return false;
    }

    for(size_t i = index; i < m_size; ++i)
    {
        m_ptr[i] = m_ptr[i+1];
    }

    m_size--;

    return true;

}

template<typename T>
size_t SeqList<T>::binaryFind(const T& v)
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
void SeqList<T>::acquireMemory(size_t alloc_size)
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
SeqList<T>::SeqList()
{
    m_ptr = nullptr;
    m_size = 0;
    m_alloc_size = 0;
}

template<typename T>
SeqList<T>::SeqList(size_t pre_size) : m_ptr(new T[pre_size]), m_size(0), m_alloc_size(pre_size)
{
}

template<typename T>
SeqList<T>::SeqList(const SeqList<T> & s)
{
    m_alloc_size = s.m_alloc_size;
    m_ptr = new T[m_alloc_size];
    m_size = s.m_size;
    std::memcpy(static_cast<void*>(m_ptr), static_cast<void*>(s.m_ptr), m_size*sizeof(T));
}

template<typename T>
SeqList<T>::~SeqList()
{
    if(m_ptr != nullptr)
    {
        delete[] m_ptr;
        m_ptr = nullptr;
        m_size = 0;
    }
}

template<typename T>
bool SeqList<T>::uniqueOrderedInsert(const T& v)
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
bool SeqList<T>::remove(const T& v)
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
bool SeqList<T>::orderedInsert(const T& v)
{
    if(m_size == 0)
    {
        return insertAtIndex(v, 0);
    }

    size_t i = 0;

    if(v < m_ptr[0])
    {
        return insertAtIndex(v, 0);
    }

    while(++i < m_size)
    {
        if(m_ptr[i-1] <= v && v < m_ptr[i])
        {
            return insertAtIndex(v, i);
        }
    }

    

    insertAtIndex(v, m_size);
}

template<typename T>
bool SeqList<T>::uniqueInsert(const T& v)
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
    else if(m_ptr[pos] == v)
    {
        // found element having same value, inserting fails. 
        return false;
    }

    return insertAtIndex(v, pos);
}


template<typename T>
void SeqList<T>::clear()
{
    delete[] m_ptr;
    m_ptr = nullptr;
    m_size = 0;
    m_alloc_size = 0;
}

template<typename T>
bool SeqList<T>::resize(size_t length)
{
    m_size = length;
    return true;
}


template<typename T>
T& SeqList<T>::operator[] (size_t index)
{
    if(index >= m_size)
    {
        throw std::invalid_argument("error, SeqList<T>::operator[], index >= m_size");
    }
    return m_ptr[index];
}

template<typename T>
const T& SeqList<T>::operator[](size_t index)const
{
    if(index >= m_size)
    {
        throw std::invalid_argument("error, SeqList<T>::operator[], index >= m_size");
    }
    return m_ptr[index];
}

template<typename T>
SeqList<T> & SeqList<T>::operator=(const SeqList<T> & s)
{
    if(m_alloc_size < s.m_size)
    {
        acquireMemory(s.m_size);
    }
    memcpy(static_cast<void*>(m_ptr), static_cast<void*>(s.m_ptr), s.m_size * sizeof(T));
    m_size = s.m_size;
}



template<typename T>
SeqList<T> SeqList<T>::operator&(const SeqList<T> & s)
{
    SeqList<T> ret(std::min(m_size, s.m_size));
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
SeqList<T> SeqList<T>::operator|(const SeqList<T> & s)
{
    SeqList<T> ret(m_size + s.m_size);
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
SeqList<T> SeqList<T>::operator-(const SeqList<T> & s)
{
    // a - b
    // in a but not in b
    SeqList<T> ret(std::max(m_size, s.m_size));
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

template<typename T>
void splitByPredicate(const SeqList<T> &orgin, SeqList<T> &t, SeqList<T> &f, bool(*p)(const T& v))
{
    for(size_t i = 0; i < orgin.size(); ++i)
    {
        if(p(orgin[i]))
        {
            t.insertAtBack(orgin[i]);
        }else
        {
            f.insertAtBack(orgin[i]);
        }
    }
}



// input SeqList must be ordered.
template<typename T>
void makeItUnique(SeqList<T> &s)
{

    if(s.size() == 0)
    {
        std::cerr << "error, SeqList empty\n";
        return;
    }

    std::cout << "origin SeqList : " << s << std::endl;

    size_t i = 1, j = 0, count = 0;

    //j points to last save element

    while(i < s.size())
    {
        if(s[i] != s[j])
        {
            ++j;
            if(j != i)
            {
                s[j] = s[i];
                std::cout << "steps : " << j << ", move '" << s[j] << "' from " << i << " to " << j << std::endl;
                ++count;
            }
        }
        ++i;
    }

    s.resize(j+1);

    std::cout << "total move count : " << count << std::endl;
    std::cout << "result SeqList : " << s << std::endl;
}

template<typename T>
void combineIntoSet(SeqList<T> &L1, SeqList<T> &L2)
{
    SeqList<T> temp;

    size_t iter1 = 0, iter2 = 0, save = 0;
    if(L1[0] > L2[0])
    {
        temp.insertAtBack(L2[0]);
        iter2++;
    }
    else
    {
        temp.insertAtBack(L1[0]);
        iter1++;
    }

    while(iter1 < L1.size() && iter2 < L2.size())
    {
        if(L1[iter1] < L2[iter2])
        {
            if(temp[save] != L1[iter1])
            {
                temp.insertAtBack(L1[iter1]);
                ++save;
            }
            ++iter1;
        } else if(L1[iter1] > L2[iter2])
        {
            if(temp[save] != L2[iter2])
            {
                temp.insertAtBack(L2[iter2]);
                ++save;
            }
            ++iter2;
        } else
        {
            if(temp[save] != L1[iter1])
            {
                temp.insertAtBack(L1[iter1]);
                ++save;
            }
            ++iter1;
            ++iter2;
        }
    }

    while(iter1 < L1.size())
    {
        if(temp.back() != L1[iter1])
        {
            temp.insertAtBack(L1[iter1]);
        }
        ++iter1;
    }
    while(iter2 < L2.size())
    {
        if(temp.back() != L2[iter2])
        {
            temp.insertAtBack(L2[iter2]);
        }
        ++iter2;
    }

    L1 = temp;
}


// if 'sub' if a subset of 's', returning true, else false

template<typename T>
bool isSubSetOf(SeqList<T> &s, SeqList<T> &sub)
{
    if(sub.size() > s.size())
    {
        return false;
    }

    if(sub.size() == 0)
    {
        return true;
    }

    size_t i = 0, j = 0;

    while(i < s.size() && j < sub.size())
    {
        if(sub[j] == s[i])
        {
            ++j;
        }
        ++i;
    }

    if(j < sub.size())
    {
        return false;
    } else 
    {
        return true;
    }



}




#endif //CH02_EXP_H