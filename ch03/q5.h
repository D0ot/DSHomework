#ifndef CH03_Q5_H
#define CH03_Q5_H

#include <iostream>
#include <string>
#include <vector>
#include "tools.h"


bool isPair(const std::string &str)
{
    size_t i = 0;
    size_t counter = 1;
    std::vector<int> st;

    auto ltor = [](char a) {
        if(a == '(') return ')';
        if(a == '[') return ']';
        if(a == '{') return '}';
        return '\0';
    };

    st.push_back('#');
    while(i < str.size())
    {

        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            if(str[i] != st.back())
            {
                st.push_back(counter);
                st.push_back(str[i]);
                counter = 1;
            } else 
            {
                counter++;
            }
        } 
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
        {
            if(str[i] != ltor(st.back()))
            {
                std::cout << "return here1\n";
                return false;
            } else 
            {
                --counter;
                if(counter == 0)
                {
                    st.pop_back();
                    counter = st.back();
                    st.pop_back();
                }
            }
            
        }
        ++i;


    }


    return st.back() == '#';
}



#endif