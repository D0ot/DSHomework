#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef int elementType;

struct Node
{
    elementType data;
    Node *next;
};

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


// question 2.11
bool deleteNodeByValue(Node* head, elementType &v)
{
    Node* iter = head;
    while(iter->next)
    {
        if(iter->next->data == v)
        {
            deleteNode(iter); // iter is the parent of "the node to delete"
            return true;
        }
        iter = iter->next;
    }

    return false;
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

void insertAtBack(Node *head, elementType &v)
{
    Node* temp = head;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp->next = new Node;
    temp->next->data = v;
}


// question 2.12
Node* linkLoopedList(Node *list1, Node *list2)
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

    return list1;
}


// question 2.18
// A = A or B

void linkedListAndInPlace(Node *A, Node *B)
{
    Node *i = A->next, *j = B->next;
    while(i && j)
    {
        if(i->data < j->data)
        {
            i = i->next;

            // bacaues the result is saved in A, we dont need to insert data in A into A

        } else if(i->data > j->data)
        {
            insertAfter(i, j->data);
            j = j->next;

        } else
        {
            i = i->next;
            j = j->next;
            
        }
    }

    while(j)
    {
        insertAfter(i, j->data);
        i = i->next;
        j = j->next;
    }

}


// question 2.21

void reverseLinkedList(Node *head)
{
    Node* iter = head;
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



}






#endif