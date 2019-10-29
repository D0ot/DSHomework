/**
 * @file : main2.cc
 * @author : d0ot
 * @date : 2019/10/16
 * @brief : 
 *  test for list exp
 */

#include <iostream>
#include "tools.h"
#include <vector> 
#include <iostream>
#include <functional>
#include <limits>
#include <memory>
#include "singleLinkedList.h"
#include "singleLinkedListOrd.h"

template<typename T>
void getSequenceFromInput(std::function<bool(const T&)> process)
{
    std::cout << "Please input the data\nCtrl+d or any data non-matching the type will be seen as a terminator.\n";
    T a;
    std::cin >> a;
    while(std::cin && process(a))
    {
        std::cin >> a;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
std::unique_ptr<SingleLinkedList<T>> generateSLLFromInput(void)
{
    auto ptr = std::make_unique<SingleLinkedList<T>>();
    auto process = [&ptr](const T& e){
        ptr->insertTail(e);
        return true;
    };
    getSequenceFromInput<T>(process);
    return ptr;
}



void exp1(void)
{
    SingleLinkedList<int> sll;
    auto process = [&sll](const int& e){
        sll.insertHead(e);
        std::cout << "Insert " << e << " At the head\n";
        std::cout << "Current Single Linked List is : " << sll << std::endl;
        return true;
    };

    getSequenceFromInput<int>(process);
    std::cout << "Final Single Linked List is : " << sll << std::endl;
}

void exp2(void)
{
    SingleLinkedList<int> sll;
    auto process = [&sll](const int& e){
        sll.insertTail(e);
        std::cout << "Insert " << e << " At the tail\n";
        std::cout << "Current Single Linked List is : " << sll << std::endl;
        return true;
    };

    getSequenceFromInput<int>(process);
    std::cout << "Final Single Linked List is : " << sll << std::endl;
}

void exp3(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    ptr->enableLog(true);
    std::cout << "List : " << *ptr;
}

void exp4(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    std::cout << "List : " << *ptr;
    std::cout << "Size of list is : " << ptr->size();
}

void exp5(void)
{
    std::cout << "Create list.\n";

    auto ptr = generateSLLFromInput<int>(); 
    auto &sll = *ptr;
    SingleLinkedList<int> sll2;

    std::cout << "sll : " << *ptr << std::endl;
    size_t n = ptr->size();

    
    std::vector<size_t> indix{5, n, 0, n+1, n+2};
    std::vector<size_t> indix2{0, 2};

    for(auto x : indix)
    {
        try
        {
            std::cout << "sll[" << x << "] = " << sll[x] << std::endl;
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    for(auto x : indix2)
    {
        try
        {
            std::cout << "sll2[" << x << "] = " << sll2[x] << std::endl;
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

}


void interface(void)
{
    exp5();
}




int main(void)
{
    interface();
    return 0;
}