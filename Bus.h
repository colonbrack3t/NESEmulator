#pragma once
#include <cstdint>
#include <array>
#include "ludo6502.h"
#include "ludo2c02.h"
#include "ludo2A03.h"
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
	ludo2A03 apu;
	std::shared_ptr<Cartridge> cart;
	std::array<uint8_t, 64 * 1024> cpuRam;
public: //read and write
	void cpuWrite(uint16_t addr, uint16_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
	uint8_t controller[2];
	double dAudioSample = 0.0; // can always interrogate Bus to find out what audio sample val
	void SetSampleFrequency(uint32_t sample_rate);

public: //System Interface
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	bool clock();
private:
	double dAudioTimePerSystemSample = 0.0;
	double dAudioTimePerNESClock = 0.0;
	double dAudioTime = 0.0;
	uint32_t nSystemClockCounter = 0;
	uint8_t controller_state[2];

	uint8_t dma_page = 0x00;
	uint8_t dma_addr = 0x00;
	uint8_t dma_data = 0x00;
	bool dma_transfer = false;
	bool dma_dummy = true;

};

