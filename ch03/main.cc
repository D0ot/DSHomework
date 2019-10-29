#include "q1.h"
#include "q2.h"
#include "q5.h"
#include "q12.h"
#include "tools.h"

int main(void)
{
    Stack<int, 20> st;
    
    SHOW_EXP(st.empty());
    SHOW_EXP(st.full());
    SHOW_EXP(st.push(1));
    SHOW_STATEMENT(st.print());
    SHOW_EXP(st.push(2));

    int a;
    SHOW_EXP(st.getTop(a));
    SHOW_EXP(a);

    SHOW_STATEMENT(st.print());
    SHOW_EXP(st.pop());
    SHOW_STATEMENT(st.print());
    SHOW_EXP(st.pop());
    SHOW_STATEMENT(st.print());
    SHOW_EXP(st.pop());

    SHOW_EXP(st.getTop(a));
    SHOW_EXP(a);

    SHOW_EXP(isPair("((( [ { }] ()()(()((((()))))) [[[[{{((( x xx x x x x)))}}]]]] )))"));


    SHOW_STATEMENT(P2(5));
    SHOW_STATEMENT(P(4));
    int M;
    SHOW_STATEMENT(P3(4,&M));
    SHOW_EXP(M);
    SHOW_EXP(ack(2,2));
    

    return 0;
}