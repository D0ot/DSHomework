/**
 * @file : main2.cc
 * @author : d0ot
 * @date : 2019/10/16
 * @brief : 
 *  test for list exp
 */

#include <iostream>
#include "linkedList.h"

std::ostream& operator<<(std::ostream& os, Node *L)
{
    if(!L)
    {
        return os;
    }

    Node* iter = L->next;
    while(iter && iter!=L)
    {
        std::cout << iter->data << ' ';
        iter = iter->next;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, dnode *L)
{
    if(!L)
    {
        return os;
    }

    dnode* iter = L->next;
    while(iter && iter!=L)
    {
        std::cout << iter->data << ' ';
        iter = iter->next;
    }
    return os;
}



void interface(void)
{
    while(1)
    {
        Node* head = createList();
        Node* iter = head;

        int n, tmp;
        std::cout << "输入要创建的单列表大小:\n";
        std::cin >> n;
        std::cout << "输入单链表中的元素:\n";
    
        while(n--)
        {
            std::cin >> tmp;
            insertAfter(iter, tmp);
            iter = iter->next;
        }


        std::cout << "原地翻转链表\n";
        reverseLinkedList(head);
        std::cout << "链表内容 : " << head << std::endl;
        std::cout << "原地翻转链表\n";
        reverseLinkedList(head);
        std::cout << "链表内容 : " << head << std::endl;

        std::cout << "输入要删除元素:\n";
        std::cin >> n;

        deleteNodeByValue(head, n);
        std::cout << "链表内容 : " << head << std::endl;

        Node* head2 = createList();
        insertAtBack(head2, 1);
        insertAtBack(head2, 2);
        insertAtBack(head2, 3);
        insertAtBack(head2, 5);
        std::cout << "链表2内容 : " << head2 << std::endl;


        makeLinkedListLoop(head);
        makeLinkedListLoop(head2);

        //head = linkLoopedList(head, head2);
        linkedListOrInPlace(head, head2);
        //Node* head3 = combineLinkedListReversed(head, head2);

        std::cout << "链表内容 : " << head << std::endl;


        std::cout << "dl test\n";

        dnode* dh1 = createdlList(); 
        dlListInsert(dh1, 1);
        dlListInsert(dh1, 2);
        dlListInsert(dh1, 3);
        dlListInsert(dh1, 5);
        dlListInsert(dh1, 6);
        dlListInsert(dh1, 7);
        dlListInsert(dh1, 8);
        dlListInsert(dh1, 9);

        std::cout << "dh1 : " << dh1 << std::endl;
        dlListMakeItLoop(dh1);
        std::cout << "dh1 : " << dh1 << std::endl;

        reversedlLinkList(dh1);
        std::cout << "reverse dh1 : " << dh1 << std::endl;

        std::cout << "symm:\n";
        std::cout << isDoubleLinkedListSymmetrical(dh1);
        std::cout << std::endl;
        


    }


}



int main(void)
{
    interface(); 

    return 0;
}