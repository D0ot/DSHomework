#include <iostream>
#include "seqqueue.h"
#include "listqueue.h"
#include "tools.h"

template<typename T>
void QueueTest(IQueue<T>& q)
{
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(1));

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(2));

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());
 
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(3));

   
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());
    
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());
    
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());
}

int main(void)
{
    return 0;
}