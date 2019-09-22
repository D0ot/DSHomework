#include <iostream>
#include <random>
#include <array>
#include "ch02/q3.h"


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

    std::cout << "a : " << a << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "a&b : " << c << std::endl;
    std::cout << "a|b : " << d << std::endl;
    std::cout << "a-b : " << e << std::endl;

}

int main(int, char**) {
    //SeqSetBasicTest();
    SetTest();
}
