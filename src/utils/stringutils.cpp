#include <algorithm>

#include "stringutils.hpp"

std::string yae::numToBin(size_t maxDigits, size_t num)
{
    std::string res = "";

    size_t digits = 0;
    while (num && (!maxDigits || digits < maxDigits))
    {
        res.append(std::to_string(num & 0b1));
        num = num >> 1;
        digits++;
    }

    for (; maxDigits && digits < maxDigits; digits++)
        res.append("0");

    std::reverse(res.begin(), res.end());

    return res;
}