#ifndef SINGLE_LINKED_LIST_ORD_H_
#define SINGLE_LINKED_LIST_ORD_H_

#include "singleLinkedList.h"

// Type "T" must can be compared
template<typename T>
class SingleLinkedListOrd : public SingleLinkedList<T>
{

public:
    SingleLinkedListOrd(){/*doing nothing*/};
    virtual ~SingleLinkedListOrd(){/*doing nothing*/};
    void insertOrd(const T& e);
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
            insert(iter, e);
            return;
        }
        last = iter;
        iter = iter->next;
    }
    insert(last, e);
}


#endif