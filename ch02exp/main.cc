#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ch02exp.h"

template<typename T>
size_t array_size(T& a)
{
    return sizeof(a)/sizeof(a[0]);
}

template<typename T>
void genSeqSetByTestcase(SeqList<T> & s, T* testcases, size_t n)
{
    for(size_t i = 0; i < n; ++i)
    {
        s.insertAtBack(testcases[i]);
    }
}

void genRandomSeqSet(SeqList<int> &s, size_t n)
{
    size_t i = n;
    while(i--)
    {
        s.uniqueOrderedInsert(std::rand()%(2*n));
    }
}


// test the method "operator[](size_t index0"
void exp1()
{
    SeqList<int> s;
    for(size_t i = 0; i < 15; ++i)
    {
        s.insertAtBack(i);
    }


    size_t testcases[] = {
        5, s.size(), 0, s.size() + 1, s.size() + 2
    };

    for(size_t i = 0; i < sizeof(testcases)/sizeof(size_t); ++i)
    {
        try
        {
            std::cout << "s[" << testcases[i] << "] = " << s[testcases[i]] << std::endl;
        }catch(std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    SeqList<int> s2;
    size_t testcases2[] = {
        0, 2
    };

    for(size_t i = 0; i < sizeof(testcases2)/sizeof(size_t); ++i)
    {
        try
        {
            std::cout << "s2[" << testcases2[i] << "] = " << s2[testcases2[i]] << std::endl;
        }catch(std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
    }

}

void exp2()
{
    SeqList<int> s;
    for(size_t i = 0; i < 15; ++i)
    {
        s.insertAtBack(i);
    }


    size_t testcases1[] = {
        5, s.size(), s.size() + 1, 0, 1, s.size() + 2
    };

    int x = 100;


    for(size_t i = 0; i < sizeof(testcases1) / sizeof(size_t); ++i)
    {
        std::cout << "s = " << s << std::endl;
        bool ret = s.insertAtIndex(x, testcases1[i]);

        std::cout << "insert " << x << " before index : " << testcases1[i];
        if(ret)
        {
            std::cout << ", success";
        } else
        {
            std::cout << ", fail, index out of range";
        }
        std::cout << std::endl;


    }
    std::cout << "s = " << s << std::endl;

}


void exp3(void)
{
    SeqList<int> s;
    for(size_t i = 0; i < 15; ++i)
    {
        s.insertAtBack(i);
    }


    size_t testcases1[] = {
        5, s.size(), 1, s.size() + 1, 0 
    };

    for(size_t i = 0; i < sizeof(testcases1) / sizeof(size_t); ++i)
    {
        std::cout << "s = " << s << std::endl;
        std::cout << "delete element at " << testcases1[i];

        bool ret = s.removeAtIndex(testcases1[i]-1);

        if(ret)
        {
            std::cout << " , success\n";
        }
        else
        {
            std::cout << " , fail\n";
        }

    }
    std::cout << "s = " << s << std::endl;

    SeqList<int> s2;
    bool ret = s2.removeAtIndex(5);

}


void exp4(void)
{
    int testcases_1[] = 
    {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100
    };

    int testcases_2[] = 
    {
        25, 85, 110,8
    };


    SeqList<int> s;
    genSeqSetByTestcase(s, testcases_1, array_size(testcases_1));

    for(size_t i = 0; i < array_size(testcases_2); ++i)
    {
        std::cout << "s = " << s << std::endl;
        s.orderedInsert(testcases_2[i]);
        std::cout << "insert " << testcases_2[i] << std::endl;

    }
    std::cout << "s = " << s << std::endl;


}


bool isEven(const int &v)
{
    return v % 2 == 0;
}

void exp5(void)
{
    SeqList<int> org, odd, even;
    
    int testcase1[] = {
        1,2,3,4,5,6,7,8,9,10,20,30,40,50,60
    };

    int testcase2[] = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100
    };

    genSeqSetByTestcase(org, testcase1, sizeof(testcase1) / sizeof(int));

    splitByPredicate(org, even, odd, isEven);

    std::cout << "origin : " << org << std::endl;
    std::cout << "even : " << even << std::endl;
    std::cout << "odd : " << odd << std::endl;


    org.resize(0);
    odd.resize(0);
    even.resize(0);

    genSeqSetByTestcase(org, testcase2, sizeof(testcase2) / sizeof(int));

    splitByPredicate(org, even, odd, isEven);

    std::cout << "origin : " << org << std::endl;
    std::cout << "even : " << even << std::endl;
    std::cout << "odd : " << odd << std::endl;

}

void exp6_subtest(int* testcases1, size_t n1, int* testcases2, size_t n2)
{
    SeqList<int> L1, L2, L3;

    genSeqSetByTestcase(L1, testcases1, n1);
    genSeqSetByTestcase(L2, testcases2, n2);

    L3 = L1 & L2;

    std::cout << "L1 = " << L1 << std::endl;
    std::cout << "L2 = " << L2 << std::endl;
    std::cout << "L3 = L1 & L2 = " << L3 << std::endl;


}


void exp6(void)
{
    int testcase1_1[] = {
        1,3,6,10,15,16,17,18,19,20
    };

    int testcase1_2[] = {
        1,2,3,4,5,6,7,8,9,10,18,20,30
    };

    int testcase2_1[] = {
        1,3,6,10,15,16,17,18,19,20
    };

    int testcase2_2[] = {
        2,4,5,7,8,9,12,22
    };

    int testcase3_1[] = {

    };

    int testcase3_2[] = {
        1,2,3,4,5,6,7,8,9,10
    };

    exp6_subtest(testcase1_1, array_size(testcase1_1), testcase1_2, array_size(testcase1_2));
    exp6_subtest(testcase2_1, array_size(testcase2_1), testcase2_2, array_size(testcase2_2));
    exp6_subtest(testcase3_1, array_size(testcase3_1), testcase3_2, array_size(testcase3_2));

}

void exp7_sub(int* p, size_t n)
{
    SeqList<int> s;

    for(size_t i = 0; i < n; ++i)
    {
        s.insertAtBack(p[i]);
    }

    makeItUnique(s);
}


void exp7(void)
{
    int testcase1[] =
    {
        1,2,3,4,5,6,7,8,9
    };

    int testcase2[] =
    {
        1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,9
    };

    int testcase3[] = 
    {
        1,2,3,4,5,5,6,7,8,8,9,9,9,9,9
    };

    exp7_sub(testcase1, sizeof(testcase1)/ sizeof(int));

    std::cout << std::endl;
    
    exp7_sub(testcase2, sizeof(testcase2)/ sizeof(int));

    std::cout << std::endl;

    exp7_sub(testcase3, sizeof(testcase3)/ sizeof(int));

    std::cout << std::endl;

}


void ext_exp1(void)
{

    SeqList<int> s1;
    SeqList<int> s2;

    size_t i = 15;
    while(i--)
    {
        s1.orderedInsert(std::rand() % 30);
        std::cout << "s1 = " << s1 << std::endl;
        s2.orderedInsert(std::rand() % 30);
    }

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;

    combineIntoSet(s1, s2);

    std::cout << "after combination s1 = " << s1 << std::endl;

}


void ext_exp2(void)
{
    SeqList<int> s1, s2, s3, s4, s5;
    
    genRandomSeqSet(s1, 15);
    genRandomSeqSet(s2, 15);

    s3 = s1 & s2;
    s4 = s1 | s2;
    s5 = s1 - s2;

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;
    std::cout << "s3 = s1 & s2 = " << s3 << std::endl;
    std::cout << "s4 = s1 | s2 = " << s4 << std::endl;
    std::cout << "s5 = s1 - s2 = " << s5 << std::endl;

}


void ext_exp3(void)
{
    SeqList<int> s1, s2;

    genRandomSeqSet(s1, 15);

    s2 = s1;

    s1.removeAtIndex(0);

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;
    std::cout << "s1 is subset of s2 ? " << isSubSetOf(s2 ,s1) << std::endl;

    s1.uniqueOrderedInsert(20);

    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;
    std::cout << "s1 is subset of s2 ? " << isSubSetOf(s2 ,s1) << std::endl;
}

void findMidElem(SeqList<int>& a, SeqList<int>& b, int l1, int r1, int l2, int r2)
{
    if(l1 >= r1 || l2 >= r2)
    {
        if(a[l1]>b[l2])
        {
            std::cout << "mid value : " << b[l2];
        }
        else
        {
            std::cout << "mid value : " << a[l1];
        }
        std::cout << std::endl;
        return;
    }

    // prevent from overflow
    // int mid1 = (l1 + r1)/2, it risks overflowing
    int mid1 = l1 + (r1 - l1)/2;
    int mid2 = l2 + (r2 - l2)/2;

    std::cout << "mid1, mid2 = " << mid1 << " , " << mid2 << std::endl;

    // if mid value of a is same with mid value of b
    // a[mid1] or b[mid2] is not final result
    if(a[mid1] == b[mid2])
    {
        std::cout << "mid value : " << a[mid1];
        return;
    }
    else if(a[mid1] < b[mid2])
    {
        if((r1 + l1) % 2)
        {
            findMidElem(a, b, mid1 + 1, r1, l2, mid2);
        }
        else
        {
            findMidElem(a, b, mid1, r1, l2, mid2);
        }
    } else
    {
        if((r2 + l2) % 2)
        {
            findMidElem(a, b, l1, mid1, mid2+1, r2);
        }
        else
        {
            findMidElem(a,b, l1, mid1, mid2, r2);
        }
    }




}


void ext_exp4(void)
{
    SeqList<int> s1, s2;

    int testcases1[] = {
        11,13,15,17,19
    };

    int testcases2[] = {
        2,4,6,8,20
    };


    const size_t length = sizeof(testcases1)/sizeof(testcases1[0]);

    genSeqSetByTestcase(s1, testcases1, length);
    genSeqSetByTestcase(s2, testcases2, length);

    findMidElem(s1, s2, 0, length, 0, length);


}



int main(void)
{
    // initialize the random seed
    std::srand(std::time(NULL));

    void(*funs[])() = 
    {
        exp1, exp2, exp3, exp4, exp5, exp6, exp7, ext_exp1, ext_exp2, ext_exp3, ext_exp4
    };

    int n = 0;
    while(1)
    {
        std::cout << "1 求顺序表中第 i 个元素\n";
        std::cout << "2 在第i个节点前插入值为x的节点\n";
        std::cout << "3 删除顺序表中第 i 个元素节点\n";
        std::cout << "4 在一个递增有序顺序表L中插入一个值为x的元素，并保持其有序性\n";
        std::cout << "5 将顺序表中的奇数项与偶数项分开\n";
        std::cout << "6 求两个递增有序顺序表中的公共元素\n";
        std::cout << "7 删除递增有序顺序表中的重复元素，并统计移动次数，要求时间性能最好\n";
        std::cout << "8 扩展实验，对递增有序顺序表进行合并，合并为一个集合并放入L1中保存,要求时间性能最好\n";
        std::cout << "9 扩展实验，递增有序顺序表实现集合的交集，并集，差集\n";
        std::cout << "10 扩展实验，判定递增有序顺序表表示的集合A, B, A是否是B的子集\n";
        std::cout << "11 扩展实验，两个序列的中位数问题\n";



        std::cout << "请输入实验编号 1 - 11 查看实验结果。\n";
        std::cout << "键入非数字内容即可退出\n";

        std::cin >> n;


        if(!std::cin.good())
        {
            break;
        }

        if(n <=0 || n > 11)
        {
            std::cout << "输入数字无效，请重新输入\n";
        }
        else
        {
            system("/usr/bin/clear");
            std::cout << "--------------------\n";
            (funs[n-1])();
            std::cout << "--------------------\n";
            std::string temp;
            std::cout << "输入回车继续。\n";
            std::getline(std::cin, temp);
            std::getline(std::cin, temp);
            system("/usr/bin/clear");
        }


    }
    std::cout << "键入非数字内容，程序退出。\n";


    return 0;
}