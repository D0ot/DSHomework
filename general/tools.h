#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>

#define SHOW_EXP(x)                                 \
    do{                                             \
        std::cout << #x << " = " << x << std::endl; \
    } while(0)

#define SHOW_STATEMENT(x)                           \
    do{                                             \
        std::cout << "BEFORE " << #x << std::endl;  \
        x;                                          \
        std::cout << std::endl << "AFTER  " << #x << std::endl;  \
    } while(0)


void getIntSequence(std::vector<int>& data)
{
    int tmp;
    while(std::cin)
    {
        std::cin >> tmp;
        data.push_back(tmp);
    }
}


#endif //TOOLS_H