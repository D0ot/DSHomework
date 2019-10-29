#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<iostream>

typedef int elementType;

struct Node
{
    elementType data;
    Node *next;
};

// 
struct DLNode
{
    elementType data;
    DLNode *next;
    DLNode *prior;
};

using dnode = DLNode;

Node* createList()
{
    Node* head = new Node;
    head->data = 0; //useless data
    head->next = nullptr;
    return head;
}

void freeList(Node*head)
{
    Node* tmp;
    if(head)
    {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

bool deleteNode(Node *parent)
{
    if(parent && parent->next)
    {
        Node *temp = parent->next->next;
        delete parent->next;
        parent->next = temp;
        return true;
        
    }else
    {
        std::cerr << "error, deleteNode, parent == NULL";
    }
}



// make a signle linked list a looped list
void makeLinkedListLoop(Node *head)
{
    Node* iter = head;

    while(iter->next)
    {
        iter = iter -> next;
    }

    iter->next = head;
}


// make a lopped list a single linked list
void makeLinkedListNotLoop(Node *head)
{
    Node* iter = head;
    while(iter->next != head)
    {
        iter = iter->next;
    }
    iter->next = nullptr;
}

// question 2.11
bool deleteNodeByValue(Node* head, elementType &v)
{
    bool flag = false;
    Node* iter = head;
    while(iter->next)
    {
        if(iter->next->data == v)
        {
            deleteNode(iter);
            flag = true;
        }
        else
        {
            iter = iter->next;
        }
        
    }

    return flag;
}

void insertAfter(Node *parent, elementType &v)
{
    Node* temp = parent->next;
    parent->next = new Node;
    parent->next->data = v;
    parent->next->next = temp;

}

void insertAfterHead(Node *head, elementType &v)
{
    Node* newNode = new Node;
    newNode -> next = head -> next;
    head -> next = newNode;
    newNode -> data= v;
}


void insertAtBack(Node *head, const elementType &v)
{
    Node* temp = head;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp->next = new Node;
    temp->next->data = v;
}

bool insertAtIndex(Node *head, int i, elementType &v)
{
    while(i-- && head)
    {
        head = head->next;
    }

    if(head)
    {
        insertAfter(head, v);
        return true;
    } else
    {
        return false;
    }

}


// question 2.12
void linkLoopedList(Node *list1, Node *list2)
{
    Node* tail1 = list1;
    Node* tail2 = list2;

    while(tail1->next != list1)
    {
        tail1 = tail1->next;
    }

    while(tail2->next != list2)
    {
        tail2 = tail2->next;
    }

    tail1->next = list2->next;

    tail2->next = list1;


    delete list2;

}


// question 2.18
// A = A or B

void linkedListOrInPlace(Node *A, Node *B)
{
    Node *i = A->next, *j = B->next;

    Node *p = A;

    while(i != A && j != B)
    {
        if(i->data < j->data)
        {
            p = i;
            i = i->next;
            // bacaues the result is saved in A, we dont need to insert data in A into A

        } else if(i->data > j->data)
        {
            insertAfter(p, j->data);
            p = p->next;
            j = j->next;

        } else
        {
            p = i;
            i = i->next;
            j = j->next;
            
        }
    }

    while(j != B)
    {
        insertAfter(p, j->data);
        p = p->next;
        j = j->next;
    }

}


// question 2.21

void reverseLinkedList(Node *head)
{
    Node* iter = head -> next;
    Node* tmp;

    while(iter->next)
    {
        tmp = iter->next;
        iter->next = tmp->next;
        tmp->next = head->next;
        head->next = tmp;
    }

}

// question 2.22
// return the head node
Node* combineLinkedListReversed(Node *A, Node *B)
{
    Node* head = new Node;

    Node*i = A->next, *j = B->next;

    while(i && j)
    {
        if(i->data < j->data)
        {
            insertAfter(head, i->data);
            i = i->next;

        }else if(i->data > j->data)
        {
            insertAfter(head, j->data);
            j = j->next;
        } else
        {

            // the result is not a set, if we meet same value
            // insert it twice

            insertAfter(head, j->data);
            insertAfter(head, j->data);

            i = i->next;
            j = j->next;
        }
    }

    while(i)
    {
        insertAfter(head, i->data);
        i = i -> next;
    }

    while(j)
     {
        insertAfter(head, j->data);
        j = j -> next;
    }

    return head;
}

dnode* createdlList()
{
    dnode *temp = new dnode;
    temp->data = 0;
    temp->prior = nullptr;
    temp->next = nullptr;
    return temp;
}


// insert after L
void dlListInsert(dnode* L, const elementType &v)
{
    dnode *temp = L->next;

    // new node
    dnode *n = new dnode;
    n->data = v;

    L->next = n;
    n->prior = L;
    n->next = temp;
    if(temp)
        temp->prior = n;
}

void dlListMakeItLoop(dnode* L)
{
    dnode* iter = L;
    while(iter->next)
    {
        iter = iter->next;
    }

    iter->next = L;
    L->prior = iter;

}

bool isDoubleLinkedListSymmetrical(dnode * dlList)
{
    dnode* forward = dlList->next, *backward = dlList->prior;

    dnode* last_forward = dlList;

    while(forward != backward && last_forward != backward) 
    {
        std::cout << "f and b : " << forward->data << ", " << backward->data << std::endl;; 
        if(forward->data != backward->data)
        {
            return false;
        }

        last_forward = forward;

        forward = forward->next;

        backward = backward->prior;
    }
    return true;
}

void reversedlLinkList(dnode* dlList)
{
    dnode* iter = dlList->next;

    dlList->next = dlList->prior;
    dlList->prior = iter;

    dnode* tmp;

    while(iter != dlList)
    {
        tmp = iter->next;
        iter->next = iter->prior; 
        iter->prior = tmp;
        iter = tmp;
    }
}



#endif