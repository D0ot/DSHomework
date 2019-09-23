#include <iostream>
#include <random>
#include <array>
#include "ch02/q3.h"
#include "ch02/q6.h"
#include "ch02/q8.h"
#include "ch02/q9.h"

void SeqSetBasicTest()
{
    std::default_random_engine dre;
    std::uniform_int_distribution<int> dis(0, 3000);
    std::array<int, 100> data;

    for(size_t i = 0; i <= 100; ++i)
    {
        size_t temp = dis(dre);
        std::cout << temp << std::endl;
    }


    SeqSet<int> myset(5);

    std::cout << "Insert content : ";
    for(const auto & x : data)
    {
        std::cout << x << ' ';
        myset.insert(x);
    }

    std::cout << "\nAfter Insert\n";
    for(size_t i = 0; i < myset.size(); ++i)
    {
        std::cout << myset[i] << ' ';
    }

    for(const auto & x : data)
    {
        myset.remove(x);
    }


    std::cout << "\nAfter Remove\n";
    for(size_t i = 0; i < myset.size(); ++i)
    {
        std::cout << myset[i] << ' ';
    }




    std::cout << "Insert content : ";
    for(const auto & x : data)
    {
        std::cout << x << ' ';
        myset.insert(x);
    }


    myset.clear();

    std::cout << "\nAfter Clear\n" << std::endl;
    for(size_t i = 0; i < myset.size(); ++i)
    {
        std::cout << myset[i] << ' ';
    }


    std::cout << "Insert content : ";
    for(const auto & x : data)
    {
        std::cout << x << ' ';
        myset.insert(x);
    }

    std::cout << "\nAfter Insert\n";
    for(size_t i = 0; i < myset.size(); ++i)
    {
        std::cout << myset[i] << ' ';
    }

    for(const auto & x : data)
    {
        myset.remove(x);
    }
    std::cout << std::endl;
}

void SetTest()
{
    constexpr size_t N = 10;

    std::default_random_engine dre;
    std::uniform_int_distribution<int> dis(0, 110);

    SeqSet<int> a(N);
    SeqSet<int> b(N);

    for(size_t i = 0; i <= N; ++i)
    {
        a.insert(dis(dre));
        b.insert(dis(dre));
    }

    SeqSet<int> c = a & b;
    SeqSet<int> d = a | b;
    SeqSet<int> e = a - b;

    std::cout << "Set Test Result:\n";
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "a&b : " << c << std::endl;
    std::cout << "a|b : " << d << std::endl;
    std::cout << "a-b : " << e << std::endl;

}

void SetTestInPlace()
{
    constexpr size_t N = 10;

    std::default_random_engine dre;
    std::uniform_int_distribution<int> dis(0, 110);

    SeqSet<int> a(N);
    SeqSet<int> b(N);

    for(size_t i = 0; i <= N; ++i)
    {
        a.insert(dis(dre));
        b.insert(dis(dre));
    }

    SeqSet<int> c = a;
    SeqSet<int> d = a;

    SeqSetAndInPlace(c, b);
    SeqSetMinusInPlace(d, b);

    std::cout << "Set Test In Place : \n";
    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "a&b : " << c << std::endl;
    std::cout << "a-b : " << d << std::endl;

}

void uniqueTest()
{

    std::array<int,18> data = {1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,8,9};
    auto size = makeItUnique(data);
    for(size_t i = 0; i < size; ++i)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
}


int main(int, char**) {
    SetTest();
    SetTestInPlace();
    return 0;
}
