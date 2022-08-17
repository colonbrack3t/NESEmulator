#include "Cartridge.h"
#include <fstream>

Cartridge::Cartridge(const std::string& sFileName)
{
	
	struct sHeader{	
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	std::ifstream ifs{};
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open()) {
		//Read file header
		ifs.read((char*)&header, sizeof(sHeader));
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		//Determine which mapper
		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4); //Standard ROM format

		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;
		uint8_t nFileType = 1;// only doing type 1 atm
		if (nFileType == 0) {

		}
		if (nFileType == 1) {
			
			nPRGBanks = header.prg_rom_chunks;//set prg bank numb
			vPRGMemory.resize(nPRGBanks * 16384); //reserve enought space for rom
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size()); //set data in prg to cartridge data

			nCHRBanks = header.chr_rom_chunks;//set prg bank numb
			if (nCHRBanks == 0)
				vCHRMemory.resize(8192);
			else{
				vCHRMemory.resize(nCHRBanks * 8192);
			} //reserve enought space for rom
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size()); //set data in prg to cartridge data

		}
		
		if (nFileType == 2) {

		}
		
		switch (nMapperID) {
			case 0:
				pMapper = std::make_shared<Mapper_000>(nPRGBanks, nCHRBanks);
			
				break;
			case 2:
				pMapper = std::make_shared<Mapper_002>(nPRGBanks, nCHRBanks);

				break;
		
		}

		bImageValid = pMapper != nullptr;//if mapper isnt set, then image isnt valid
		ifs.close();
	}

}


Cartridge::~Cartridge()
{
}

bool Cartridge::ImageValid()
{
	return bImageValid;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t  data)
{ 
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapWrite(addr, mapped_addr,data)) {
		vPRGMemory[mapped_addr] = data ;
		return true;
	}
	return false;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t& data)
{
	uint32_t mapped_addr = 0;
	if (pMapper->cpuMapRead(addr, mapped_addr))
	{
		data = vPRGMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{

	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapWrite(addr, mapped_addr)) {
		vCHRMemory[mapped_addr] = data;
		return true;
	}
	return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t& data)
{

	uint32_t mapped_addr = 0;
	if (pMapper->ppuMapRead(addr, mapped_addr)) {
		data = vCHRMemory[mapped_addr];
		return true;
	}
	return false; 
}
void Cartridge::reset() {
	pMapper->reset();
}
