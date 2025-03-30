#include "BitManager.h"
#include <vector>
unsigned int BitManager::GetPositionOfMostRightBit(int n)
{
    return log2(n & -n);
}

unsigned int BitManager::IncrementByOne(unsigned int n)
{
    int k = GetPositionOfMostRightBit(~n);

    n = ((1 << k) | n);

    if (k != 0)
        n = ToggleLaskKBits(n, k);

    return n;
}

unsigned int BitManager::ToggleLaskKBits(unsigned int n, unsigned int k)
{
    unsigned int num = (1 << k) - 1;

    return (n ^ num);
}

bool BitManager::GetBitFromInteger(uint32_t byteNumber, uint32_t value)
{
    int mask = 1 << byteNumber;
    int result = value & mask;
    return result != 0;
}
