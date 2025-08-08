#include <iostream>
#include "inlineFunc.H"

int main()
{
    inlineFunc s(3.0);
    std::cout << "inlineFunc: " << s.getInlineFunc() << std::endl;
}
