#pragma once
#include <cstdint>
#include <array>
#include "ludo6502.h"
#include "ludo2c02.h"
#include "Cartridge.h"
#include <memory>
class Bus
{
public:
	Bus();
	~Bus();
public: //devices
	ludo6502 cpu;
	ludo2c02 ppu;
	std::shared_ptr<Cartridge> cart;
	std::array<uint8_t, 64 * 1024> cpuRam;
public: //read and write
	void cpuWrite(uint16_t addr, uint16_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
	uint8_t controller[2];
public: //System Interface
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();
private:
	uint32_t nSystemClockCounter = 0;
	uint8_t controller_state[2];

	uint8_t dma_page = 0x00;
	uint8_t dma_addr = 0x00;
	uint8_t dma_data = 0x00;
	bool dma_transfer = false;
	bool dma_dummy = true;

};

