#ifndef CH03_Q1_H
#define CH02_01_H


#include <vector>
#include <iostream>



bool stackOutputCheck(const std::vector<int> &input, const std::vector<int> &seq);

int count = 0;

void stackOutputSeq(std::vector<int> &s, std::vector<int> &input, std::vector<int> &output)
{
    auto show = [](std::vector<int> &t){
        for(const auto&x : t)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    };


    /*std::cout << std::endl;
    std::cout << "s : ";
    show(s);
    std::cout << "i : ";
    show(input);
    std::cout << "o : ";
    show(output);*/


    if(s.empty() && input.empty())
    {
        ++count;
        std::cout << count << " : ";
        for(const auto& x : output)
        {
            std::cout << x << ' ';
        }
        std::endl(std::cout);
        return;
    }

    if(!input.empty())
    {
        int tmp = input.back();

        input.pop_back();

        s.push_back(tmp);

        stackOutputSeq(s, input, output);

        s.pop_back();

        input.push_back(tmp);

    }
 
    if(!s.empty())
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
void stackOutputSeq(std::vector<int> &input)
{
    std::vector<int> s, output;
    count = 0;
    stackOutputSeq(s, input, output);
    std::cout << "count = " << count << std::endl;
}

bool stackOutputCheck(const std::vector<int> &input, const std::vector<int> &seq)
{
    std::vector<int> aux;
    size_t i = 0, j = 0;
    while(i < input.size() && j < seq.size())
    {
        aux.push_back(input[i++]);

        if(aux.back() == seq[j])
        {
            ++j;
            aux.pop_back();
        }
    }

    while(j < seq.size())
    {
        if(seq[j] != aux.back())
        {
            return false;
        }
        ++j;
        aux.pop_back();

    }
    return true;

}



#endif 