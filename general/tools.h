#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <vector>
#include <limits>
#include <vector>
#include <functional>

#define SHOW_EXP(x)                                 \
    do                                              \
    {                                               \
        std::cout << #x << " = " << x << std::endl; \
    } while (0)

#define SHOW_STATEMENT(x)                          \
    do                                             \
    {                                              \
        std::cout << "BEFORE " << #x << std::endl; \
        x;                                         \
        std::cout << std::endl                     \
                  << "AFTER  " << #x << std::endl; \
    } while (0)

void getIntSequence(std::vector<int> &data)
{
    int tmp;
    while (std::cin)
    {
        std::cin >> tmp;
        data.push_back(tmp);
    }
}
void printMenu(const std::vector<std::string> &items)
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        std::cout << i << ". " << items[i] << std::endl;
    }
}

void clearBuf()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

size_t getNumInput()
{
    clearBuf();
    size_t choice = 0;
    std::cin >> choice;
    return choice;
}

void clearScreen()
{
    system("/usr/bin/clear");
}

void waitEnter()
{
    clearBuf();
    std::string temp;
    std::cout << "Press Enter to continue\n";
    std::getline(std::cin, temp);
}

void mainLoop(std::vector<std::function<void(void)>> &funs)
{
    int n = 0;
    while(1)
    {
        std::cout << "Please enter number to check exp\n";
        std::cout << "1 ~ " << funs.size() << std::endl;
        std::cout << "Input non-digits input will cause exit\n";

        std::cin >> n;

        if(!std::cin.good())
        {
            break;
        }

        if(n <=0 || n > funs.size())
        {
            std::cout << "Invalid number input\n";
        }
        else
        {
            clearScreen();
            std::cout << "--------------------\n";
            clearBuf();
            (funs[n-1])();
            std::cout << "--------------------\n";
            waitEnter();
            clearScreen();
        }


    }
    std::cout << "non-digtis input detected, exit\n";

}

#endif //TOOLS_H