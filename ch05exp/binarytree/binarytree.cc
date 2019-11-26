#include "binarytree.h"
#include "tools.h"

int main(void)
{
    auto tree = createBinaryTreeFromFile("bt262.btr");
    preOrder(tree);
    endl(std::cout);
    midOrder(tree);
    endl(std::cout);
    postOrder(tree);
    endl(std::cout);

    return 0;
}