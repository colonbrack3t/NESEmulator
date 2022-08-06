#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include "Mapper_000.h"
class Cartridge
{
public:
	Cartridge(const std::string& sFileName);
	~Cartridge();

public: //communication to main bus and ppu bus
	bool cpuWrite(uint16_t addr, uint8_t data);
	bool cpuRead(uint16_t addr, uint8_t& data);

	bool ppuWrite(uint16_t addr, uint8_t data);
	bool ppuRead(uint16_t addr, uint8_t& data);

private://PRG and CHR memory
	std::vector<uint8_t> vPRGMemory;
	std::vector<uint8_t> vCHRMemory;
	uint8_t nMapperID = 0;
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;

	std::shared_ptr<Mapper> pMapper;
public:
	bool ImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;
private:
	bool bImageValid = false;
};

