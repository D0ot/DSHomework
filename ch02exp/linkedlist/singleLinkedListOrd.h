#ifndef SINGLE_LINKED_LIST_ORD_H_
#define SINGLE_LINKED_LIST_ORD_H_

#include "singleLinkedList.h"

// Type "T" must can be compared
template<typename T>
class SingleLinkedListOrd : public SingleLinkedList<T>
{
    template<typename P>
    friend void interSectionList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2, SingleLinkedListOrd<P> &l3);
    template<typename P>
    friend void interSectionList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2);
    template<typename P>
    friend void unionList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2, SingleLinkedListOrd<P> &l3);
    template<typename P>
    friend void unionList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2);
    template<typename P>
    friend void combineList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2);
    template<typename P>
    friend void differenceList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2, SingleLinkedListOrd<P> &l3);
    template<typename P>
    friend bool isSubsetOf(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2);

    template<typename T>
    friend T bothMidValue(SingleLinkedList<T> &l1, SingleLinkedList<T> &l2)

public:
    SingleLinkedListOrd(){/*doing nothing*/};
    virtual ~SingleLinkedListOrd(){/*doing nothing*/};
    void insertOrd(const T& e);
    void uniqueSelf();

};

template<typename T>
void SingleLinkedListOrd<T>::insertOrd(const T& e)
{
    auto last = this->head();
    auto iter = this->head()->next;
    while(iter)
    {
        if(iter->data >= e)
        {
            SingleLinkedList<T>::insert(last, e);
            return;
        }
        last = iter;
        iter = iter->next;
    }
    SingleLinkedList<T>::insert(last, e);
}


template<typename T>
void SingleLinkedListOrd<T>::uniqueSelf()
{
    auto iter = this->head()->next;
    while(iter && iter->next)
    {
        if(iter->data == iter->next->data)
        {
            SingleLinkedList<T>::remove(iter);
        }
        else 
        {
            iter = iter->next;
        }
    }
}

template<typename T>
void interSectionList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2, SingleLinkedListOrd<T> &l3)
{
    auto iter1 = l1.head()->next;
    auto iter2 = l2.head()->next;

    while(iter1 && iter2)
    {
        if(iter1->data == iter2->data)
        {
            l3.insertTail(iter1->data);
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
        else if(iter1->data < iter2->data)
        {
            iter1 = iter1 -> next;
        }
        else
        {
            iter2 = iter2 -> next;
        }
    }
}

template<typename T>
void interSectionList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2)
{
    auto iter1 = l1.head()->next;
    auto last1 = l1.head();
    auto iter2 = l2.head()->next;

    while(iter1 && iter2)
    {
        if(iter1->data == iter2->data)
        {
            last1= iter1;
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
        else if(iter1->data < iter2->data)
        {
            l1.remove(last1);
        }
        else
        {
            iter2 = iter2 -> next;
        }
    }
}

template<typename T>
void unionList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2, SingleLinkedListOrd<T> &l3)
{
    auto i1 = l1.head()->next;
    auto i2 = l2.head()->next;

    while(i1 && i2)
    {
        if(i1->data == i2->data)
        {
            l3.insertTail(i1->data);
            i1 = i1->next;
            i2 = i2->next;
        } 
        else if(i1->data > i2->data)
        {
            l3.insertTail(i2->data);
            i2 = i2->next;
        }
        else  // < 
        {
            l3.insertTail(i1->data);
            i1 = i1->next;
        }
    }

    while(i1)
    {
        l3.insertTail(i1->data);
        i1 = i1->next;
    }

    while(i2)
    {
        l3.insertTail(i2->data);
        i2 = i2->next;
    }
}

template<typename T>
void unionList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2)
{
    auto i1 = l1.head()->next;
    auto last1 = l1.head();
    auto i2 = l2.head()->next;

    while(i1 && i2)
    {
        if(i1->data == i2->data)
        {
            last1 = i1;
            i1 = i1->next;
            i2 = i2->next;
        } 
        else if(i1->data > i2->data)
        {
            l1.insert(i1,i2->data);
            i2 = i2->next;
        }
        else  // < 
        {
            last1 = i1;
            i1 = i1->next;
        }
    }


    while(i2)
    {
        l1.insertTail(i2->data);
        i2 = i2->next;
    }
   
}


// l3 = l1 - l2
template<typename T>
void differenceList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2, SingleLinkedListOrd<T> &l3)
{
    auto i1 = l1.head()->next;
    auto i2 = l2.head()->next;

    while(i1 && i2)
    {
        if(i1->data == i2->data)
        {
            i1 = i1->next;
            i2 = i2->next;
        } 
        else if(i1->data > i2->data)
        {
            i2 = i2->next;
        }
        else  // < 
        {
            l3.insertTail(i1->data);
            i1 = i1->next;
        }
    }


    while(i1)
    {
        l3.insertTail(i1->data);
        i1 = i1->next;
    }
   
}

template<typename T>
void combineList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2)
{
    auto i1 = l1.head();
    auto i2 = l2.head();

    while(i1->next && i2->next)
    {
        if(i1->next->data == i2->next->data)
        {
            i1 = i1->next;
            i2 = i2->next;
        } 
        else if(i1->next->data > i2->next->data)
        {
            auto tmp = i2->next;
            i2->next = tmp->next;

            tmp->next = i1->next;
            i1->next = tmp;
        }
        else  // < 
        {
            i1 = i1->next;
        }
    }

    if(i2->next)
    {
        i1->next = i2->next;
        i2->next = nullptr;
    }
}

template<typename T>
bool isSubsetOf(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2)
{
    auto i1 = l1.head()->next;
    auto i2 = l2.head()->next;

    while(i1 && i2)
    {
        if(i1->data == i2->data)
        {
            i1 = i1->next;
            i2 = i2->next;
        } 
        else if(i1->data > i2->data)
        {
            i2 = i2->next;
        }
        else  // < 
        {
            return false;
        }
    }


    if(i1)
    {
        return false;
    }

    return true;
}




#endif