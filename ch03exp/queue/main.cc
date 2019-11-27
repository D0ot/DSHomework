#include <iostream>
#include <functional>
#include <limits>
#include "seqqueue.h"
#include "listqueue.h"
#include "tools.h"

template <typename T>
void QueueTest(IQueue<T> &q)
{
    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(1));

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(2));

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_STATEMENT(q.enQueue(3));

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());

    SHOW_EXP(q.front());
    SHOW_STATEMENT(q.deQueue());

    SHOW_EXP(q.full());
    SHOW_EXP(q.empty());
    SHOW_EXP(q.size());
}



void printMenu()
{
    std::cout
        << "1. Initial Queue\n"
        << "2. Is Queue Empty ?\n"
        << "3. Is Queue Full ?\n"
        << "4. EnQueue operations\n"
        << "5. DeQueue operations\n"
        << "6. Get \"The Front\"\n"
        << "7. Size of Queue\n"
        << "8. Lopp enQueue\n"
        << "9. Algrithm Procedure\n"
        << "10. Switch Queue\n"
        << "0. Exit\n";
}

template <typename T>
struct TestClass
{
public:
    static void f1(IQueue<T> *&q);
    static void f2(IQueue<T> *&q);
    static void f3(IQueue<T> *&q);
    static void f4(IQueue<T> *&q);
    static void f5(IQueue<T> *&q);
    static void f6(IQueue<T> *&q);
    static void f7(IQueue<T> *&q);
    static void f8(IQueue<T> *&q);
    static void f9(IQueue<T> *&q);
};

template <typename T>
void TestClass<T>::f1(IQueue<T> *&q)
{
    std::vector<std::string> prompts = {"Back", "SeqQueue", "ListQueue"};
    printMenu(prompts);
    size_t c = getNumInput();
    if (c == 1)
    {
        q = new SeqQueue<T>();
        std::cout << "Initialize SeqQueue<T>\n";
    }
    else if (c == 2)
    {
        q = new ListQueue<T>();
        std::cout << "Initialize ListQueue<T>\n";
    }
    else
    {
        std::cout << "Nothing Done\n";
    }
}

template <typename T>
void TestClass<T>::f2(IQueue<T> *&q)
{
    SHOW_EXP(q->empty());
}

template <typename T>
void TestClass<T>::f3(IQueue<T> *&q)
{
    SHOW_EXP(q->full());
}

template <typename T>
void TestClass<T>::f4(IQueue<T> *&q)
{
    T temp;

    std::cout << "Input data (Ctrl+D to terminate): ";
    while (std::cin)
    {
        std::cin >> temp;
        if (!std::cin)
        {
            break;
        }

        try
        {
            q->enQueue(temp);
        }
        catch (QueueException &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "Intput done\n";
}

template <typename T>
void TestClass<T>::f5(IQueue<T> *&q)
{
    try
    {
        q->deQueue();
    }
    catch (QueueException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
void TestClass<T>::f6(IQueue<T> *&q)
{
    try
    {
        SHOW_EXP(q->front());
    }
    catch (QueueException &e)
    {
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
void TestClass<T>::f7(IQueue<T> *&q)
{
    SHOW_EXP(q->size());
}

template <typename T>
void TestClass<T>::f8(IQueue<T> *&q)
{
    const size_t N = 99;
    for (size_t i = 1; i <= N; ++i)
    {
        q->enQueue((T)i);
    }
}

template <typename T>
void TestClass<T>::f9(IQueue<T> *&q)
{
    auto isOdd = [](int i) { return i % 2; };
    auto show = [](auto e) { std::cout << e << ' '; };
    while (1)
    {
        auto num = getNumInput();
        if (num == 0)
        {
            std::cout << "Algrithm exit.\n";
            break;
        }
        else if (isOdd(num))
        {
            std::cout << "enQueue\n";
            q->enQueue(num);
        }
        else
        {
            std::cout << "deQueue\n";
            q->deQueue();
        }

        std::cout << "Current in Queue : ";
        q->traverse(show);
        std::cout << std::endl;
    }
}

int main(void)
{

    int choice = 0;
    bool sw = 0; // default is q1;

    IQueue<int> *q1;
    IQueue<char> *q2;

    std::function<void(IQueue<int> *&)> fint[] = {TestClass<int>::f1, TestClass<int>::f2,
                                                  TestClass<int>::f3, TestClass<int>::f4,
                                                  TestClass<int>::f5, TestClass<int>::f6,
                                                  TestClass<int>::f7, TestClass<int>::f8,
                                                  TestClass<int>::f9};

    std::function<void(IQueue<char> *&)> fchar[] = {TestClass<char>::f1, TestClass<char>::f2,
                                                    TestClass<char>::f3, TestClass<char>::f4,
                                                    TestClass<char>::f5, TestClass<char>::f6,
                                                    TestClass<char>::f7, TestClass<char>::f8,
                                                    TestClass<char>::f9};

    try
    {

        while (1)
        {
            clearScreen();
            printMenu();
            std::cin >> choice;

            if (!std::cin || choice == 0)
            {
                break;
            }

            if (choice > 10)
            {
                std::cout << "Out of Range\n";
                waitEnter();
                continue;
            }

            if (choice == 10)
            {
                sw = !sw;
                std::cout << "Switch type of Queue\n";
                waitEnter();
                continue;
            }

            clearScreen();
            if (sw == 0)
            {
                fint[choice - 1](q1);
            }
            else
            {
                fchar[choice - 1](q2);
            }
            waitEnter();
        }
    }

    catch (std::exception &e)
    {
        std::cout << "Fatal Error : " << e.what() << std::endl;
    }

    std::cout << "program exits.\n";
    return 0;
}