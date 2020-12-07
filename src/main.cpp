#include <iostream>

#include "core/register.hpp"
#include "utils/stringutils.hpp"

int main(int, char **)
{
    yae::Register reg1("test register 1", 8, false);
    yae::Register reg2("test register 2", 8, false);

    for (size_t i = 0; i < 1000000000; i++)
    {
        reg2 = reg1;
        reg1 = reg2 + i;
    }

    return 0;
}