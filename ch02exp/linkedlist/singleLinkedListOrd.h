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
    friend void unionList(SingleLinkedListOrd<P> &l1, SingleLinkedListOrd<P> &l2);

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
void unionList(SingleLinkedListOrd<T> &l1, SingleLinkedListOrd<T> &l2)
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




#endif