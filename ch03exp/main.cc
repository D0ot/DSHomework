#include <iostream>
#include <memory>
#include <limits>
#include "stackbase.h"
#include "seqStack.h"
#include "linkedStack.h"
#include "exp.h"


void exp1()
{
    conversion<SeqStack<int>>();
}

void exp2()
{
    pair<SeqStack<int>>();
}

void exp3()
{
    conversion<LinkedStack<int>>();
}

void exp4()
{
    pair<LinkedStack<int>>();
}

void exp5()
{
    int n;
    std::cout << "input N : \n";
    std::cin >> n;
    SeqStack<int> input;

    for(size_t i = 1; i <= n; ++i)
    {
        input.push_back(i);
    }
 
    std::cout << "input the ouput sequence : \n";
    int tmp;

    SeqStack<int> tmpst;
    SeqStack<int> output;
    while(1)
    {
        std::cin >> tmp;
        if(!std::cin)
        {
            break;
        }
        tmpst.push_back(tmp);
    }

    while(!tmpst.empty())
    {
        output.push_back(tmpst.back());
        tmpst.pop_back();
    }

    std::cout << "is valid ? " << stackOutputCheck(input, output) << std::endl;
}

void exp6()
{
    int n;
    std::cout << "input N : ";
    std::cin >> n;
    SeqStack<int> st;
    while(n)
    {
        st.push_back(n--);
    }
    stackOutputSeq(st);
}

void exp7()
{
    std::string tmp;
    std::cout << "Input expression : \n";
    std::cin >> tmp;
    tmp += "#";
    int rst = calculate(tmp) ;
    std::cout << "rst " << rst << std::endl; 
}

int main(void)
{
    void(*funs[])() = 
    {
        exp1, exp2, exp3, exp4, exp5, exp6, exp7
    };

    int n = 0;
    while(1)
    {
        std::cout << "请输入实验编号 1 - 7 查看实验结果。\n";
        std::cout << "键入非数字内容即可退出\n";

        std::cin >> n;


        if(!std::cin.good())
        {
            break;
        }

        if(n <=0 || n > 8)
        {
            std::cout << "输入数字无效，请重新输入\n";
        }
        else
        {
            system("/usr/bin/clear");
            std::cout << "--------------------\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            (funs[n-1])();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "--------------------\n";
            std::string temp;
            std::cout << "输入回车继续。\n";
            std::getline(std::cin, temp);
            std::getline(std::cin, temp);
            system("/usr/bin/clear");
        }


    }
    std::cout << "键入非数字内容，程序退出。\n";


}