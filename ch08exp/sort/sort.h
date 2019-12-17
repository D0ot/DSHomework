#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <functional>
#include <iomanip>
auto showVec = [](auto &&ds) {
    for (auto &&x : ds)
    {
        std::cout << std::setw(5) << x; 
    }
    std::cout << std::endl;
};

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

void showVectorOfTriple(std::vector<std::tuple<size_t, size_t, size_t>> &ds, std::ostream &os = std::cout)
{
    os << "n;compare;move\n";
    for (auto &&x : ds)
    {
        os << std::get<0>(x) << ";" << std::get<1>(x) << ";" << std::get<2>(x) << std::endl;
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

bool &quickSortShow()
{
    static bool show;
    return show;
}

void quickSortInner(std::vector<int> &ds, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    if (quickSortShow())
    {
        std::cout << "Partition (" << l << ", " << r << ")\n";
        int i = 0;
        while (i < ds.size())
        {
            if (i >= l && i <= r)
            {
                std::cout << std::setw(5) << ds[i];
            }
            else
            {
                std::cout << std::setw(5) << ' ';
            }
            ++i;
        }
        std::cout << std::endl;
    }
    int p = partition(ds, l, r);

    if (quickSortShow())
    {
        std::cout << "Partition (" << l << ", " << r << ") Result:\n";
        int i = 0;
        while (i < ds.size())
        {
            if (i >= l && i <= r)
            {
                std::cout << std::setw(5) << ds[i];
            }
            else
            {
                std::cout << std::setw(5) << ' ';
            }
            ++i;
        }
        std::cout << std::endl;
    }

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
    int start = incSeq.size() - 1;
    while (incSeq[start] > ds.size())
    {
        --start;
    }

    for (int i = start; i > 0; --i)
    {
        insertSortWithStride(ds, incSeq[i]);
    }

    insertSortWithStride(ds, 1);
}

inline int leftChild(int p) { return p * 2 + 1; }
inline int rightChild(int p) { return p * 2 + 2; }
inline int theParent(int self) { return (self - 1) / 2; }

auto keepHeap = [](std::vector<int> &ds, int l, int r) {
    int i = 0;
    //std::cout << "to keep " << ds[i+l] << std::endl;
    while (i + l <= r)
    {
        int maxIndex = i;
        int max = ds[maxIndex+l];

        if(rightChild(i) + l <= r)
        {
            if(max < ds[rightChild(i)+l])
            {
                max = ds[rightChild(i)+l];
                maxIndex = rightChild(i);
            }
        }

        if(leftChild(i) + l <= r)
        {
            if(max < ds[leftChild(i)+l])
            {
                max = ds[leftChild(i)+l];
                maxIndex = leftChild(i); 
            }
        }

        if(max != ds[i+l])
        {
            std::swap(ds[i+l], ds[maxIndex+l]);
            i = maxIndex;
        }else
        {
            break;
        }

    }


};
// root is max
void createHeap(std::vector<int> &ds)
{

    int sep = ds.size() - 1;
    while (sep >= 0)
    {
        keepHeap(ds, sep, ds.size() - 1);
        --sep;
    };
}


void heapSort(std::vector<int> &ds)
{
    std::cout << "Heap Sort\n";


    createHeap(ds);
    std::cout << "Create Heap result :\n";
    showVec(ds);

    int sep = ds.size() - 1;
    while (sep >= 1)
    {
        std::swap(ds[0], ds[sep]);
        keepHeap(ds, 0, sep - 1);
        std::cout << "Step : \n";
        showVec(ds);
        --sep;
    }
    std::cout << "Result : \n";
    showVec(ds);
}


void mergeSort(std::vector<int> &ds, std::vector<int>&out, int l, int r)
{
    if(l >= r)
    {
        return;
    }

    int mid = (r-l)/2+l;

    mergeSort(ds, out, l, mid);
    mergeSort(ds, out, mid+1, r);

    //merge operation

    int s = l;

    int il = l;
    int ir = mid+1;

    while(il <= mid && ir <= r)
    {
        if(ds[il] < ds[ir])
        {
            out[s++] = ds[il++];
        }else
        {
            out[s++] = ds[ir++];
        }
    }

    while(il <= mid)
    {
        out[s++] = ds[il++];
    }

    while(ir <= r)
    {
        out[s++] = ds[ir++];
    }

    int iter = l;
    while(iter <= r)
    {
        ds[iter] = out[iter];
        ++iter;
    }


}

void mergeSort(std::vector<int> &ds, std::vector<int> &out)
{
    mergeSort(ds, out, 0, ds.size()-1);
}

void mergeSort(std::vector<int> &ds)
{
    std::vector<int> out;
    out.resize(ds.size());
    mergeSort(ds, out);
}

#endif