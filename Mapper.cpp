#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
	nCHRBanks = chrBanks;
	nPRGBanks = prgBanks;
}

Mapper::~Mapper()
{
}
