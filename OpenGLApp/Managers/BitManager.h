#pragma once
#include <cmath>
class BitManager
{
public: 
	unsigned int GetPositionOfMostRightBit(int n);
	unsigned int IncrementByOne(unsigned int n);
	unsigned int ToggleLaskKBits(unsigned int n, unsigned int k);
	bool GetBitFromInteger(uint32_t byteNumber, uint32_t value);
};

