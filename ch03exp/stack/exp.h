#ifndef EXP_H
#define EXP_H

#include "stackbase.h"
#include <string>
#include <iostream>

char table[] = "0123456789ABCDEF";

template <typename T>
void conversion()
{
    int n;
    std::cout << "input data to convert : ";
    std::cin >> n;
    int tmp = n;

    T st;
    IStack<int> &s = st;
    while (tmp)
    {
        s.push_back(tmp % 0x10);
        tmp = tmp / 0x10;
    }

    std::cout << n << " in hex is : ";

    while (!s.empty())
    {
        std::cout << table[s.back()];
        s.pop_back();
    }
    std::cout << std::endl;
}

template <typename T>
bool isPair(const std::string &str)
{
    size_t i = 0;
    size_t counter = 1;
    T ds;
    IStack<int> *st = &ds;

    auto ltor = [](char a) {
        if (a == '(')
            return ')';
        if (a == '[')
            return ']';
        if (a == '{')
            return '}';
        return '\0';
    };

    st->push_back('#');
    while (i < str.size())
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            if (str[i] != st->back())
            {
                st->push_back(counter);
                st->push_back(str[i]);
                counter = 1;
            }
            else
            {
                counter++;
            }
        }
        else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if (str[i] != ltor(st->back()))
            {
                //std::cout << "return here1\n";
                return false;
            }
            else
            {
                --counter;
                if (counter == 0)
                {
                    st->pop_back();
                    counter = st->back();
                    st->pop_back();
                }
            }
        }
        ++i;
    }

    return st->back() == '#';
}

template <typename T>
void pair()
{
    std::string s;
    std::getline(std::cin, s);
    std::cout << "input string is " << s << std::endl;
    std::cout << "isPair : " << isPair<T>(s) << std::endl;
}

bool stackOutputCheck(SeqStack<int> &input, const SeqStack<int> &seq);

int count = 0;

void stackOutputSeq(SeqStack<int> &s, SeqStack<int> &input, SeqStack<int> &output)
{

    if (s.empty() && input.empty())
    {
        ++count;
        std::cout << count << " : ";
        for (size_t i = 0; i < output.size(); ++i)
        {
            std::cout << output[i] << ' ';
        }
        std::endl(std::cout);
        return;
    }

    if (!input.empty())
    {
        int tmp = input.back();
        input.pop_back();
        s.push_back(tmp);
        stackOutputSeq(s, input, output);
        s.pop_back();
        input.push_back(tmp);
    }

    if (!s.empty())
    {
        int tmp = s.back();
        s.pop_back();
        output.push_back(tmp);
        stackOutputSeq(s, input, output);
        s.push_back(tmp);
        output.pop_back();
    }
}

// NOTE:
// input is inputed reversed
// the pop_back sequence of input is real input sequence
void stackOutputSeq(SeqStack<int> &input)
{
    SeqStack<int> s, output;
    count = 0;
    stackOutputSeq(s, input, output);
    std::cout << "count = " << count << std::endl;
}

bool stackOutputCheck(SeqStack<int> &input, SeqStack<int> &seq)
{
    SeqStack<int> aux;
    size_t i = 0, j = 0;
    while (i < input.size() && j < seq.size())
    {
        aux.push_back(input[i++]);
        if (aux.back() == seq[j])
        {
            ++j;
            aux.pop_back();
        }
    }
    while (j < seq.size())
    {
        if (seq[j] != aux.back())
        {
            return false;
        }
        ++j;
        aux.pop_back();
    }
    return true;
}

int calculate(const std::string &exp)
{
    auto priority = [](char c) {
        int k;
        switch (c)
        {
        case '*':
            k = 2;
            break;
        case '/':
            k = 2;
            break;
        case '+':
            k = 1;
            break;
        case '-':
            k = 1;
            break;
        case '(':
            k = 0;
            break;
        case ')':
            k = 0;
            break;
        default:
            k = -1;
            break;
        }
        return k;
    };

    auto i = exp.begin();

    SeqStack<char> op;
    SeqStack<int> vs;

    op.push_back('#');

    while (i != exp.end())
    {
        if (op.back() == *i && *i == '#')
        {
            break;
        }

        if (*i >= '0' && *i <= '9')
        {
            int v = 0;
            while(*i >= '0' && *i <= '9')
            {
                v *= 10;
                v += *i - '0';
                ++i;
            }
            vs.push_back(v);
        }
        else if (*i == '(' || priority(*i) > priority(op.back())) 
        {
            op.push_back(*i);
            ++i;
        }
        else if (*i == ')' && op.back() == '(')
        {
            op.pop_back();
            ++i;
        }
        else if (priority(*i) <= priority(op.back()))
        {
            int r = vs.back(); vs.pop_back();
            int l = vs.back(); vs.pop_back();
            char c = op.back(); op.pop_back();
            int ret;

            switch (c)
            {
            case '+':
                ret = l + r;
                break;
            
            case '-':
                ret = l - r;
                break;
            case '*':
                ret = l * r;
                break;
            case '/':
                ret = l / r;
                break;
            default:
                ret = -1;
                break;
            }

            vs.push_back(ret);
        }
    }

    return vs.back();
}

#endif