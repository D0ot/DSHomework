#include <iostream>
#include "../binarytree/binarytree.h"
#include "tree.h"
#include "tools.h"

#define CREATE_FOREST(x) \
    auto x = CreateTreeFromFile(#x "_.tre");

CREATE_FOREST(tree10);
CREATE_FOREST(tree11);
CREATE_FOREST(F14);
CREATE_FOREST(F16);
CREATE_FOREST(F18);
CREATE_FOREST(F20);


void exp1()
{
    std::cout << "1. Three ways to traverse Forest\n";

    std::cout << "About tree11.tre" << std::endl;
    forestPreOrder(tree11);
    std::cout << std::endl;
    forestPostOrder(tree11);
    std::cout << std::endl;
    forestLevelOrder(tree11);
    std::cout << std::endl;

    std::cout << "About F20.tre" << std::endl;
    forestPreOrder(F20);
    std::cout << std::endl;
    forestPostOrder(F20);
    std::cout << std::endl;
    forestLevelOrder(F20);
    std::cout << std::endl;
}

void exp2()
{
    std::cout << "2. Get Height of forest\n";
    SHOW_EXP(forestHeight(tree11));
    SHOW_EXP(forestHeight(F20));
}

void exp3()
{
    std::cout << "3. Count the node\n";
    SHOW_EXP(forestNodeCount(tree11));
    SHOW_EXP(forestNodeCount(F20));
}

void exp4()
{
    std::cout << "4. Count Leaves in forest\n";
    SHOW_EXP(forestLeafCount(tree11));
    SHOW_EXP(forestLeafCount(F20));
}

void exp5()
{
    std::cout << "5. Get degree of forest\n";
    SHOW_EXP(forestDegree(tree11));
    SHOW_EXP(forestDegree(F20));
}

void exp6()
{
    std::cout << "6. PreOrder With Level\n";
    std::cout << "About tree11.tre" << std::endl;
    forestLNPreOrder(tree11);
    std::cout << std::endl;
    std::cout << "About F20.tre" << std::endl;
    forestLNPreOrder(F20);
    std::cout << std::endl;
}

void exp7()
{
    std::cout << "7. Ouput Forest in Lists\n";
    std::cout << "About tree11.tre" << std::endl;
    std::cout << forestGerenalOutput(tree11) << std::endl;
    std::cout << "About F20.tre" << std::endl;
    std::cout << forestGerenalOutput(F20) << std::endl;
}


int main(void)
{
 
    std::vector<std::function<void(void)>> funs = 
    {
        exp1, exp2, exp3, exp4, exp5, exp6, exp7
    };

    mainLoop(funs);
    return 0;
}

