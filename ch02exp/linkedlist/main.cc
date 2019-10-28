/**
 * @file : main2.cc
 * @author : d0ot
 * @date : 2019/10/16
 * @brief : 
 *  test for list exp
 */

#include <iostream>
#include "linkedList.h"
#include "tools.h"
#include <vector> 

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
    int a;
    while(1)
    {
        std::cout << "输入数字";
        std::cin >> a;

        switch (a)
        {
        case 0:
            return;
            break;
        
        default:
            break;
        }

    }


}



int main(void)
{
    std::vector<int> v;
    getIntSequence(v);
    
    for(const auto& x: v)
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    

    return 0;
}