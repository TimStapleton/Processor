#include <stdio.h>
#include "Stack.h"

int main()
{
    Stack_t st(3);
    st.Push(1);
    st.Push(1);
    st.Push(1);
    st.Push(1);
    st.Push(1);
    st.Pop();
    st.Dump();

    return 0;
}
