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


template<typename T>
void generateSLLOFromVector(const std::vector<T> &v, SingleLinkedListOrd<T>& sllo)
{
    for(const auto &x : v)
    {
        sllo.insertOrd(x);
    }
}



void exp1(void)
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

void exp2(void)
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
void exp3(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    ptr->enableLog(true);
    std::cout << "List : " << *ptr << std::endl;
}

void exp4(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    std::cout << "List : " << *ptr << std::endl;
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



void exp6(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    auto &sll = *ptr;

    std::cout << "List1 : " << *ptr << std::endl;
    size_t n = ptr->size();
    
    std::vector<size_t> indix{5, n, n+1, 0, 1, n+2};

    for(auto x : indix)
    {
        try
        {
            std::cout << "Insert 100 at " << x << ".\n";
            sll.insert(x, 100);
            std::cout << "List1 : " << sll << std::endl;
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    
    SingleLinkedList<int> sll2;
    const size_t index = 5;

    try
    {
        std::cout << "Insert 100 at " << index << std::endl;
        sll2.insert(index, 100);
        std::cout << "List2 : " << sll2 << std::endl;
    }
    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void exp7(void)
{
    std::vector<int> testdata = {
        1,3,6,10,15,16,17,18
    };

    SingleLinkedList<int> sll;

    for(auto x : testdata)
    {
        sll.insertTail(x);
    }

    std::vector<int> testcase = {
        1, 17, 20, 88
    };

    std::cout << "List1 : " << sll << std::endl;


    SLLNode<int> *tmp;
    for(auto x : testcase)
    {
        tmp = sll.find(x);
        if(tmp)
        {
            std::cout << x << " is found in List1, Pointer : " << tmp << std::endl;;
        } else
        {
            std::cout << x << " is not found in List1.\n";
        }
    }
}

void exp8(void)
{
    std::cout << "Create list.\n";
    auto ptr = generateSLLFromInput<int>(); 
    auto &sll = *ptr;

    std::cout << "List1 : " << sll << std::endl;
    size_t n = ptr->size();
    
    std::vector<size_t> indix{5, n, 1, n+1, 0};

    for(auto x : indix)
    {
        try
        {
            std::cout << "Delete element at " << x << ".\n";
            sll.remove(x);
            std::cout << "List1 : " << sll << std::endl;
        }
        catch(std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    
    SingleLinkedList<int> sll2;
    const size_t index = 5;

    std::cout << "List2 : " << sll2 << std::endl;
    try
    {
        std::cout << "Delete element at " << index << std::endl;
        sll2.remove(index);
        std::cout << "List2 : " << sll2 << std::endl;
    }
    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}   

void exp9(void)
{
    SingleLinkedListOrd<int> sllo;
    for(size_t i = 1; i <= 10; ++i)
    {
        sllo.insertTail(i*10);
    }
    std::cout << "List : " << sllo << std::endl;

    std::vector<int> testcase = {
        25, 85, 110, 8
    };

    for(auto x : testcase)
    {
        std::cout << "Insert " << x << " into List, with ordering.\n";
        sllo.insertOrd(x);
        std::cout << "List : " << sllo << std::endl;
    }

}

void exp10(void)
{
    std::vector<int> testcase = 
    {
        1,2,3,4,5,6,7,8,9,10,20,30,40,50,60
    };

    std::vector<int> testcase2 = 
    {
        10,20,30,40,50,60,70,80,90,100
    };

    auto exp10_aux = [](const std::vector<int>& tc)
    {
        SingleLinkedList<int> sll, t, f;

        for(auto x : tc)
        {
            sll.insertTail(x);
        }

        splitList<int>(sll, t, f, [](const int& a){ return a % 2;});
        std::cout << "List : " << sll << std::endl;
        std::cout << "Odd  : " << t << std::endl;
        std::cout << "Even : " << f << std::endl;
    };

    exp10_aux(testcase);
    exp10_aux(testcase2);


}


void exp11()
{
    auto exp11_aux = [](const std::vector<int>& t1, const std::vector<int>& t2)
    {
        SingleLinkedListOrd<int> l1, l2, l3;
        generateSLLOFromVector(t1, l1);
        generateSLLOFromVector(t2, l2);

        std::cout << "List1 : " << l1 << std::endl;
        std::cout << "List2 : " << l2 << std::endl;
        interSectionList(l1, l2, l3);
        std::cout << "List3 : " << l3 << std::endl;
    };


    std::vector<int> tc1_1 = 
    {
        1,3,6,10,15,16,17,18,19,20
    };
    std::vector<int> tc1_2 = 
    {
        1,2,3,4,5,6,7,8,9,10,18,20,30
    };
    exp11_aux(tc1_1, tc1_2);
    std::cout << std::endl;


    std::vector<int> tc2_1 =
    {
        1,3,6,10,15,16,17,18,19,20
    };

    std::vector<int> tc2_2 = 
    {
        2,4,5,7,8,9,12,22
    };
    exp11_aux(tc2_1, tc2_2);
    std::cout << std::endl;


    std::vector<int> tc3_1 = {};

    std::vector<int> tc3_2 = 
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
    exp11_aux(tc3_1, tc3_2);
    std::cout << std::endl;
}


void exp12()
{
    std::vector<int> tc1 =
    {
        1,2,3,4,5,6,7,8,9
    };


    std::vector<int> tc2 = 
    {
        1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,9
    };

    std::vector<int> tc3 = 
    {
        1,2,3,4,5,5,6,7,8,8,9,9,9,9,9
    };

    auto exp12_aux = [](const std::vector<int>& v) 
    {
        SingleLinkedListOrd<int> sllo;
        generateSLLOFromVector(v, sllo);
        std::cout << "Origin List : " << sllo << std::endl;
        sllo.uniqueSelf();
        std::cout << "Result List : " << sllo << std::endl;
    };

    exp12_aux(tc1);
    std::cout << std::endl;
    exp12_aux(tc2);
    std::cout << std::endl;
    exp12_aux(tc3);
    std::cout << std::endl;



}

void exp13(void)
{
    std::vector<int> tc1_1 = 
    {
        1,3,6,10,15,16,17,18,19,20
    };
    std::vector<int> tc1_2 = 
    {
        1,2,3,4,5,6,7,8,9,10,18,20,30
    };


    std::vector<int> tc2_1 =
    {
        1,3,6,10,15,16,17,18,19,20
    };

    std::vector<int> tc2_2 = 
    {
        2,4,5,7,8,9,12,22
    };


    std::vector<int> tc3_1 = {};

    std::vector<int> tc3_2 = 
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };


    auto exp13_aux = [](const std::vector<int> &v1, const std::vector<int> &v2)
    {
        SingleLinkedListOrd<int> s1, s2;
        generateSLLOFromVector(v1, s1);
        generateSLLOFromVector(v2, s2);
        std::cout << "List1 : " << s1 << std::endl;
        std::cout << "List2 : " << s2 << std::endl;
        std::cout << "After the operation.\n";
        unionList(s1, s2);
        std::cout << "List1 : " << s1 << std::endl << std::endl;
    };

    exp13_aux(tc1_1, tc1_2);
    exp13_aux(tc2_1, tc2_2);
    exp13_aux(tc3_1, tc3_2);

}


void interface(void)
{
    std::vector<std::string> prompts
    {
        "1. 尾插法创建单链表",
        "2. 头插法创建单链表",
        "3. 销毁单链表",
        "4. 求链表长度",
        "5. 求链表中第i个元素",
        "6. 在第i个结点前插入值为x的结点",
        "7. 链表中查找元素值为x的结点",
        "8. 删除单链表中第i个元素结点",
        "9. 插入递增有序单链表，保持有序性",
        "10.分开单链表中的奇数与偶数项",
        "11.求两个递增有序单链表L1和L2中的公共元素",
        "12.删除递增有序单链表中的重复元素",
        "13.合并两个单增有序单链表"
    };
    
    auto showPrompts = [&]()
    {
        for(const auto&x:prompts)
        {
            std::cout << x << std::endl;
        }
    };


    std::vector<std::function<void(void)>> fs
    {
        exp1, exp2, exp3, exp4, exp5, exp6, exp7, exp8, exp9, exp10, exp11, exp12, exp13
    };

    int choice;
    std::string tmp;
    showPrompts();
    std::cout << "请输入实验编号 1~13 查看实验结果, 键入非数字内容即可退出\n";
    std::cin >> choice;
    while(std::cin)
    {
        if(choice > 0 && choice <= 13)
        {
            system("/usr/bin/clear");
            std::cout << prompts[choice-1] << std::endl;
            fs[choice-1]();
            std::getline(std::cin, tmp);
            std::getline(std::cin, tmp);
            system("/usr/bin/clear");
        } 


        showPrompts();
        std::cout << "请输入实验编号 1~13 查看实验结果, 键入非数字内容即可退出\n";
        std::cin >> choice;
    }

}



int main(void)
{
    interface();
    return 0;
}