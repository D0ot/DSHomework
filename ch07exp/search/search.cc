#include "search.h"
#include "tools.h"

void exp1()
{
    std::vector<int> data = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 19, 20, 24, 25, 26, 30, 35, 40, 45, 50, 100};

    std::vector<int> xs = {
        2, 8, 20, 30, 50, 5, 15, 33, 100};

    std::vector<int> data2 = {
        2, 3, 5, 7, 8, 10, 12, 15, 18, 20, 22, 25, 30, 35, 40, 45, 50, 55, 60, 80, 100};

    std::vector<int> xs2 = {
        22, 8, 80, 3, 100, 1, 13, 120};

    auto inner = [](std::vector<int> &data, std::vector<int> &xs) {
        for (auto &&x : xs)
        {
            std::cout << "Find " << x << std::endl;
            int ret = binarySearch(data, x);
            std::cout << "Find Result index:" << ret << std::endl
                      << std::endl;
        }
    };

    inner(data, xs);
    inner(data2, xs2);
}

void exp2()
{
    std::vector<int> ds = {
        100, 150, 120, 50, 70, 60, 80, 170, 180, 160, 110, 30, 40, 35, 175};

    std::vector<int> ds2 = {
        100, 70, 60, 80, 150, 120, 50, 160, 30, 40, 170, 180, 175, 35};

    Node *t1 = createByVector(ds);
    Node *t2 = createByVector(ds2);

    SHOW_STATEMENT(preOrder(t1));
    SHOW_STATEMENT(preOrder(t2));
}

void exp3()
{
    std::vector<int> data = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 19, 20, 24, 25, 26, 30, 35, 40, 45, 50, 100};

    std::vector<int> data2 = {
        150, 70, 160, 190, 10, 55, 175};

    std::vector<Node *> rets;

    auto t1 = createByVector(data);

    for (auto &&x : data2)
    {
        rets.push_back(searchInTree(t1, x));
        std::cout << x << ' ';
    }

    std::cout << "\nsearch results:\n";

    for (auto &&x : rets)
    {
        if (x)
        {
            std::cout << x->data << ' ';
        }
        else
        {
            std::cout << "NOT_FOUND" << ' ';
        }
    }

    std::cout << std::endl;
}

void exp4()
{

    std::vector<int> data = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 19, 20, 24, 25, 26, 30, 35, 40, 45, 50, 100};

    std::vector<int> data2 = {30, 150, 100};

    auto t1 = createByVector(data);

    std::cout << "Before delete : \n";
    showTree(t1);
    for (auto &&x : data2)
    {
        deleteInTree(t1, x);
        std::cout << "Delete " << x << std::endl;
        showTree(t1);
    }
}

void exp5()
{
    std::vector<int> ds;

    for (int i = 1; i <= 26; ++i)
    {
        ds.push_back(i);
    }

    std::vector<int> ds2 = {
        1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210, 231, 253, 277, 302, 328};

    auto t1 = createBlanceByVector(ds, 0, ds.size() - 1);
    auto t2 = createBlanceByVector(ds2, 0, ds2.size() - 1);

    showTree(t1);
    std::cout << std::endl;
    showTree(t2);
}

int main(void)
{
    exp5();

    return 0;
}