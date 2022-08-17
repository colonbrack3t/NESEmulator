#pragma once
#include "Mapper.h"
class Mapper_002 :
    public Mapper
{
public:
    Mapper_002(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper_002() override;

    bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr, uint8_t data = 0) override;
    bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr, uint8_t data = 0) override;
    void reset();
    bool ppuMapRead(uint16_t addr, uint32_t& mapped_addr) override;
    bool ppuMapWrite(uint16_t addr, uint32_t& mapped_addr) override;

private:
    uint8_t nPRGBankSelectlo = 0x00;
    uint8_t nPRGBankSelecthi = 0x00;
};

