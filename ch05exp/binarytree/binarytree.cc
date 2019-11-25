#include "binarytree.h"
#include "tools.h"

int main(void)
{
    auto node = createBinaryTreeFromFile("bt10.btr");

    auto node2 = treeCopy(node);

    std::cout << std::endl;
    preOrder(node);
    std::cout << std::endl;
    preOrder(node2);
    std::cout << std::endl;

    return 0;
}