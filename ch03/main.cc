#include "q1.h"


int main(void)
{
    std::vector<int> input{5,4,3,2,1};
    std::vector<int> output;


    stackOutputSeq(input);

    std::cout << stackOutputCheck(std::vector<int> {1,2,3,4,5}, std::vector<int> {3,4,5,1,2}) << std::endl;


    return 0;
}