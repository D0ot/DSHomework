#include "sort.h"
#include "tools.h"
#include <algorithm>
#include <fstream>

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

void exp3()
{
    auto ds = generateRandomSeq(1000, 30000);
    std::vector<int> sedgewickSeq{
        1, 5, 19, 41, 109, 209, 505, 929,
        2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609,
        587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 67084289,
        150958081, 268386305, 603906049, 1073643521};
    std::vector<int> hibbardSeq{
        1, 3, 7, 15, 31, 63, 127, 255,
        511, 1023, 2047, 4095, 8191, 16383, 32767, 65535,
        131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215,
        33554431, 67108863, 134217727, 268435455, 536870911, 1073741823};

    auto linear = []() {
        static size_t counter = 0;
        return (++counter) * 1000;
    };

    auto shellSortHibbard = std::bind(shellSort, std::placeholders::_1, hibbardSeq);
    auto shellSortSedgewick= std::bind(shellSort, std::placeholders::_1, sedgewickSeq);

    auto dss = generateTable(linear, 1000000, 100);
    auto ret = countSort(shellSortHibbard, dss);
    auto ret2 = countSort(shellSortSedgewick , dss);

    std::ofstream ofhib("hibbard.csv", std::ios::trunc);
    showVectorOfTriple(ret, ofhib);

    std::ofstream ofsed("sedgewick.csv", std::ios::trunc);
    showVectorOfTriple(ret2, ofsed);

}

void exp4()
{

}

int main(void)
{
    exp3();
    return 0;
}