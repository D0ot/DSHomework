#include "sort.h"
#include "tools.h"
#include <algorithm>

void exp1()
{
    auto linear = []() {
        static size_t counter = 0;
        return (++counter) * 1000;
    };

    auto dss = generateTable(linear, 1000000, 300);
    auto ret = countSort(quickSort, dss);

    std::cout << "n;compare;move\n";
    showVectorOfTriple(ret);
}

void exp2()
{
    auto pre = [](int n) {
        return n % 2;
    };

    std::vector<int> ds1;
    for (int i = 1; i <= 26; ++i)
    {
        ds1.push_back(i);
    }

    std::vector<int> ds2 = {
        11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6, 10, 16, 1, 22, 23, 2, 17, 18, 19, 20, 24, 7, 8, 9, 25, 26};

    std::vector<int> ds3 = {
        5, 6, 7, 1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 16, 17, 18, 14, 25, 26, 15, 19, 20, 21, 22, 23, 24};

    auto show = [](auto &ds) {
        auto ret = countSortAlgorithm(partByResOf3, ds);
        partByResOf3(ds);
        std::cout << "Part Result:"; 
        for (auto &&x : ds)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
        std::cout << "Compare: " << std::get<1>(ret)
                  << ", Move: " << std::get<2>(ret) << std::endl;
    };

    show(ds1);
    show(ds2);
    show(ds3);
}

int main(void)
{
    exp2();
    return 0;
}