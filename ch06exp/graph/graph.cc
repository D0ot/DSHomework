#include "graph.h"
#include <utility>
#include "tools.h"

#define CREATE_TREE(x)                                     \
    Graph x##graph_temp;                                   \
    CreateGraphFromFile("grps/" #x ".grp", x##graph_temp); \
    auto x = std::make_pair(&x##graph_temp, std::string(#x));

// God(it is OS indeed) will destory them.

void openTest()
{
    CREATE_TREE(dg6);
    CREATE_TREE(dg8);
    CREATE_TREE(dn8);
    CREATE_TREE(dn10);
    CREATE_TREE(dn61);
    CREATE_TREE(f14);
    CREATE_TREE(kPath101);
    CREATE_TREE(Top7dg1);
    CREATE_TREE(udg4);
    CREATE_TREE(udg8);
    CREATE_TREE(udg10);
    CREATE_TREE(udg114);
    CREATE_TREE(udg115);
    CREATE_TREE(udn6);
    CREATE_TREE(udTree11);
    CREATE_TREE(un8);
}

void exp1()
{
    std::cout << "1. DFS and BFS \n";
    CREATE_TREE(udg8);
    CREATE_TREE(udg115);
    CREATE_TREE(dg6)
    CREATE_TREE(f14)

    std::vector<decltype(udg8)> grps = {udg8, udg115, dg6, f14};

    std::cout << "DFS:\n";
    for (auto &x : grps)
    {
        std::cout << x.second << " : ";
        GraphDFS(*(x.first), 1, print);
        std::cout << std::endl;
    }

    std::cout << "BFS:\n";
    for (auto &x : grps)
    {
        std::cout << x.second << " : ";
        GraphBFS(*(x.first), 1, print);
        std::cout << std::endl;
    }
}

void exp2()
{
    std::cout << "2. Count the Arcs:\n";
    CREATE_TREE(udg8);
    CREATE_TREE(udg115);
    CREATE_TREE(dg6)
    CREATE_TREE(f14)

    std::vector<decltype(udg8)> grps = {udg8, udg115, dg6, f14};

    for (auto &x : grps)
    {
        std::cout << x.second << " : ";
        std::cout << GraphArcCount(*(x.first));
        std::cout << std::endl;
    }
}

void exp34_inner(const std::string & prompt, const std::function<void(Graph&,Graph&)> &func)
{
    std::cout << prompt << std::endl;

    CREATE_TREE(udg8);
    CREATE_TREE(dg8);
    CREATE_TREE(un8);
    CREATE_TREE(dn10);

    std::vector<decltype(udg8)> grps = {udg8, dg8, un8, dn10};
    for(auto&x:grps)
    {
    //    auto x = udg8;
        Graph span;
        std::cout << "Spaning Tree(Or forest) of " << x.second << " is : \n";
        func(*x.first, span);
        printGraph(span);
    }

}

std::function<void()> exp3 = std::bind(exp34_inner, std::string("3. Tree Spanning by DFS"), GraphDFSTreeSpanning);
std::function<void()> exp4 = std::bind(exp34_inner, std::string("4. Tree Spanning by BFS"), GraphBFSTreeSpanning);


void exp5()
{

}


int main(void)
{
    std::vector<std::function<void(void)>> funs =
        {exp1, exp2, exp3, exp4};

    mainLoop(funs);

    return 0;
}