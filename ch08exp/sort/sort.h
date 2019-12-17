#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <functional>

std::vector<int> generateRandomSeq(size_t n, int max)
{
    std::vector<int> ret;
    while (n--)
    {
        ret.push_back(std::rand() % max);
    }
    return ret;
}

std::vector<std::vector<int>> generateTable(std::function<size_t()> &&f, int max, size_t lines)
{
    std::vector<std::vector<int>> ret;
    while (lines--)
    {
        ret.push_back(generateRandomSeq(f(), max));
    }
    return ret;
}

std::vector<std::vector<int>> generateTable(size_t n, int max, size_t lines)
{
    auto constFunc = [n]() { return n; };
    return generateTable(constFunc, max, lines);
}

size_t &compareCounter()
{
    static size_t i;
    return i;
}

size_t &moveCounter()
{
    static size_t i;
    return i;
}

std::tuple<size_t, size_t, size_t> countSortAlgorithm(std::function<void(std::vector<int> &)> f, std::vector<int> &ds)
{
    compareCounter() = 0;
    moveCounter() = 0;
    f(ds);
    return std::make_tuple(ds.size(), compareCounter(), moveCounter());
}

std::vector<std::tuple<size_t, size_t, size_t>> countSort(std::function<void(std::vector<int> &)> f, std::vector<std::vector<int>> dss)
{
    std::vector<std::tuple<size_t, size_t, size_t>> ret;

    for (auto &&x : dss)
    {
        ret.push_back(countSortAlgorithm(f, x));
    }
    return ret;
}


void showVectorOfTriple(std::vector<std::tuple<size_t, size_t, size_t>> &ds, std::ostream& os = std::cout)
{
    os << "n;compare;move\n";
    for (auto &&x : ds)
    {
        os<< std::get<0>(x) << ";" << std::get<1>(x) << ";" << std::get<2>(x) << std::endl;
    }
}

int partition(std::vector<int> &ds, int l, int r)
{
    int key = ds[l];

    int p = l, q = r;

    while (p < q)
    {
        while (ds[q] > key && p < q)
        {
            compareCounter()++;
            --q;
        }

        if (p < q)
        {
            compareCounter()++;
            moveCounter()++;
            ds[p++] = ds[q];
        }

        while (ds[p] < key && p < q)
        {
            compareCounter()++;
            ++p;
        }

        if (p < q)
        {
            compareCounter()++;
            moveCounter()++;
            ds[q--] = ds[p];
        }
    }

    ds[p] = key;
    return q;
}

void quickSortInner(std::vector<int> &ds, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int p = partition(ds, l, r);
    quickSortInner(ds, l, p - 1);
    quickSortInner(ds, p + 1, r);
}

void quickSort(std::vector<int> &ds)
{
    if (ds.empty())
    {
        return;
    }
    quickSortInner(ds, 0, ds.size() - 1);
}

// left true, right false
int partByPredicate(std::function<bool(int)> &&f, std::vector<int> &ds, int start, int end)
{
    int l = start, r = end;

    while (l < r)
    {
        while (l < r && f(ds[l]))
        {
            compareCounter()++;
            ++l;
        }

        while (l < r && !f(ds[r]))
        {
            compareCounter()++;
            --r;
        }

        if (l < r)
        {
            moveCounter()++;
            std::swap(ds[l], ds[r]);
        }
    }
    return l;
}

int partByPredicate(std::function<bool(int)> &&f, std::vector<int> &ds)
{
    return partByPredicate(std::forward<std::function<bool(int)> &&>(f), ds, 0, ds.size() - 1);
}

void partByResOf3(std::vector<int> &ds)
{
    auto f1 = [](int n) {
        return n % 3 == 0;
    };

    auto f2 = [](int n) {
        return n % 3 == 1;
    };

    int pos = partByPredicate(f1, ds);
    partByPredicate(f2, ds, pos, ds.size() - 1);
}

void insertSortWithStride(std::vector<int> &ds, int stride, int offset = 0)
{
    // left is sorted, right is not sorted
    // sep itself is sorted


    int sep = offset;
    int iter;
    while (sep + stride < ds.size())
    {
        compareCounter()++;
        iter = sep;
        int key = ds[sep + stride];
        while (iter >= 0 && key < ds[iter])
        {
            compareCounter()++;
            compareCounter()++;
            ds[iter + stride] = ds[iter];
            moveCounter()++;
            iter -= stride;
        }
        ds[iter + stride] = key;

        sep += stride;
    }
}

void insertSort(std::vector<int> &ds)
{
    insertSortWithStride(ds, 1);
}

void shellSort(std::vector<int> &ds, const std::vector<int> &incSeq)
{
    int start = incSeq.size()-1;
    while(incSeq[start]> ds.size())
    {
        --start;
    }

    std::cout << "start:" << start << std::endl;

    for(int i = start; i >0; --i)
    {
        insertSortWithStride(ds, incSeq[i]);
    }

    insertSortWithStride(ds, 1);
}

#endif