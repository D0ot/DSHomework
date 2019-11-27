#include "binarytree.h"
#include "tools.h"
#include <limits>
#include <functional>

#define CREATE_TREE(x) \
    auto x = createBinaryTreeFromFile(#x ".btr");

CREATE_TREE(bt4);
CREATE_TREE(bt8);
CREATE_TREE(bt9);
CREATE_TREE(bt10);
CREATE_TREE(bt12);
CREATE_TREE(bt14);
CREATE_TREE(bt15);
CREATE_TREE(bt21);
CREATE_TREE(bt26);
CREATE_TREE(bt151);
CREATE_TREE(bt261);
CREATE_TREE(bt262);
CREATE_TREE(full4);
CREATE_TREE(full5);

void destory()
{
    destoryBinaryTree(bt4);
    destoryBinaryTree(bt8);
    destoryBinaryTree(bt9);
    destoryBinaryTree(bt10);
    destoryBinaryTree(bt12);
    destoryBinaryTree(bt14);
    destoryBinaryTree(bt15);
    destoryBinaryTree(bt21);
    destoryBinaryTree(bt261);
    destoryBinaryTree(bt262);
    destoryBinaryTree(full4);
    destoryBinaryTree(full5);
}
#define THREE_KIND_ORDER(x)                                 \
    do                                                      \
    {                                                       \
        std::cout << "PreOrderTraverse of " #x << ":\n\t";  \
        preOrder(x);                                        \
        endl(std::cout);                                    \
        std::cout << "MidOrderTraverse of " #x << ":\n\t";  \
        midOrder(x);                                        \
        endl(std::cout);                                    \
        std::cout << "PostOrderTraverse of " #x << ":\n\t"; \
        preOrder(x);                                        \
        endl(std::cout);                                    \
    } while (0)

void exp1()
{
    THREE_KIND_ORDER(bt151);
    THREE_KIND_ORDER(bt21);
}

void exp2()
{
    // TODO
    SHOW_STATEMENT(midOrderHeight(bt15));
    endl(std::cout);
    SHOW_STATEMENT(midOrderHeight(bt21));
    endl(std::cout);
}

#define CODE_GEN_FOR_3456(x) \
    do                       \
    {                        \
        SHOW_EXP(x(bt261));  \
        SHOW_EXP(x(bt21));   \
    } while (0)

void exp3()
{
    CODE_GEN_FOR_3456(treeHeight);
};

void exp4()
{
    CODE_GEN_FOR_3456(treeNodeCount);
}

void exp5()
{
    CODE_GEN_FOR_3456(treeLeafCount);
}

void exp6()
{
    CODE_GEN_FOR_3456(treeNode2DegCount);
}

// why input, disgusting...
void exp7()
{
    char input;
    std::cout << "Please input a Char\n:";
    std::cin >> input;

    treeFind(bt21, input);
}

void exp8()
{
    char input;
    std::cout << "Please input a Char\n:";
    std::cin >> input;

    SHOW_EXP(treeElemHeight(bt26, input));
}

#define SHOW_TREE_IN_ARRAY(x)                           \
    do                                                  \
    {                                                   \
        std::cout << "tree : " #x " in array form :\n"; \
        for (size_t i = 0; i < x##arr.size(); ++i)      \
        {                                               \
            std::cout << x##arr[i] << ' ';              \
        }                                               \
        std::cout << std::endl;                         \
    } while (0)

void exp9()
{
    auto bt8arr = treeLinked2Array(bt8);
    auto bt14arr = treeLinked2Array(bt14);

    SHOW_TREE_IN_ARRAY(bt8);
    SHOW_TREE_IN_ARRAY(bt14);

    std::cout << "\nThree orders of tranverse : \n";

    THREE_KIND_ORDER(bt8);
    THREE_KIND_ORDER(bt14);
}

void exp10_aux(BtNode *root)
{
    THREE_KIND_ORDER(root);
    std::cout << "Apply the exchange\n";
    treeExchangeLR(root);
    THREE_KIND_ORDER(root);
    std::cout << "Exchage back\n";
    treeExchangeLR(root);
    THREE_KIND_ORDER(root);
}

void exp10()
{
    std::cout << "ABOUT BT151:\n";
    exp10_aux(bt151);

    std::cout << "\nABOUT BT21\n";
    exp10_aux(bt21);
}

void exp11()
{
    auto newtree1 = treeCopy(bt151);
    auto newtree2 = treeCopy(bt21);

    std::cout << "newtree1 is copied from bt151\n";
    THREE_KIND_ORDER(newtree1);
    std::cout << "\nnewtree2 is copied form bt21\n";
    THREE_KIND_ORDER(newtree2);
}

void exp12()
{
    SHOW_STATEMENT(treePath2Leaf(bt261));
    SHOW_STATEMENT(treePath2Leaf(bt21));
}

void exp13()
{
    SHOW_STATEMENT(treeHeightOrder(bt261));
    SHOW_STATEMENT(treeHeightOrder(bt261));
}

void exp14()
{
    SHOW_EXP(treeSharedAncestor(bt261, 'e', 'd'));
    SHOW_EXP(treeSharedAncestor(bt21, 'e', 'd'));
}

void exp15()
{
    auto MaxLengthOfBT261 = treeMaxPathLength(bt261)[0].size();
    auto MaxLengthOfBT21 = treeMaxPathLength(bt21)[0].size();
    SHOW_EXP(MaxLengthOfBT261);
    SHOW_EXP(MaxLengthOfBT21);
}

int main(void)
{  
    
    std::vector<std::function<void(void)>> funs = 
    {
        exp1, exp2, exp3, exp4, exp5, exp6, exp7,
        exp8, exp9, exp10, exp11, exp12, exp13, exp14, exp15
    };

    mainLoop(funs);
    return 0;
}