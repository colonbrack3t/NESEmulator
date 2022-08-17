#include "ludo2c02.h"

ludo2c02::ludo2c02()
{
	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);

}


ludo2c02::~ludo2c02()
{
}

olc::Sprite& ludo2c02::GetScreen()
{
	// Simply returns the current sprite holding the rendered screen
	return sprScreen;
}



olc::Sprite& ludo2c02::GetPatternTable(uint8_t i, uint8_t palette)
{
	for (uint16_t nTiley = 0; nTiley < 16; nTiley++)
	{
		for (uint16_t nTilex = 0; nTilex < 16; nTilex++) {
			uint16_t nOffset = nTiley * 256 + nTilex * 16;//single tile is 16 bytes- 16 tiles per row
			for (uint16_t row = 0; row < 8; row++)
			{
				uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row + 0x0000);
				uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 0x0008);

				for (uint16_t col = 0; col < 8; col++)
				{
					uint8_t pixel = ((tile_lsb & 0x01) <<1 ) | (tile_msb & 0x01);
					tile_lsb >>= 1;
					tile_msb >>= 1;

					sprPatternTable[i].SetPixel(
						nTilex * 8 + (7 - col),
						nTiley * 8 + row,
						GetColourFromPaletteRam(palette, pixel)
					);
				}
			}

		}
	}
	return sprPatternTable[i];
}


olc::Pixel& ludo2c02::GetColourFromPaletteRam(uint8_t palette, uint8_t pixel)
{
	// This is a convenience function that takes a specified palette and pixel
	// index and returns the appropriate screen colour.
	// "0x3F00"       - Offset into PPU addressable range where palettes are stored
	// "palette << 2" - Each palette is 4 bytes in size
	// "pixel"        - Each pixel index is either 0, 1, 2 or 3
	// "& 0x3F"       - Stops us reading beyond the bounds of the palScreen array
	return palScreen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];

	// Note: We dont access tblPalette directly here, instead we know that ppuRead()
	// will map the address onto the seperate small RAM attached to the PPU bus.
}

olc::Sprite& ludo2c02::GetNameTable(uint8_t i)
{
	// As of now unused, but a placeholder for nametable visualisation in teh future
	return sprNameTable[i];
}


uint8_t ludo2c02::cpuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;
	switch (addr) {
	case 0x0000: //Control
		break;
	case 0x0001: //Mask
		break;
	case 0x0002: //Status

		data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
		status.vertical_blank = 0;
		address_latch = 0;
		break;
	case 0x0003: //OAM Address
		break;
	case 0x0004: //OAM Data
		data = pOAM[oam_addr];
		break;
	case 0x0005: //Scroll
		break;
	case 0x0006: //PPU Address
		break;
	case 0x0007: //PPU Data
		data = ppu_data_buffer;
		ppu_data_buffer = ppuRead(vram_addr.reg);

		if (vram_addr.reg > 0x3F00) data = ppu_data_buffer;//get data immediately
		vram_addr.reg += (control.increment_mode ? 32 : 1);
		break;
	}
	return data;
}

void ludo2c02::cpuWrite(uint16_t addr, uint8_t data)
{
	switch (addr) {
	case 0x0000: //Control
		control.reg = data;
		tram_addr.name_table_x = control.nametable_x;
		tram_addr.name_table_y = control.nametable_y;
		break;
	case 0x0001: //Mask
		mask.reg = data;
		break;
	case 0x0002: //Status
		break;
	case 0x0003: //OAM Address
		oam_addr = data;
		break;
	case 0x0004: //OAM Data
		pOAM[oam_addr] = data;
		break;
	case 0x0005: //Scroll
		if (address_latch == 0) {
			fine_x = data & 0x07;
			tram_addr.coarse_x = data >> 3;
			address_latch = 1;
		}
		else {

			tram_addr.fine_y = data & 0x07;
			tram_addr.coarse_y = data >> 3;
			address_latch = 0;
		}
		break;
	case 0x0006: //PPU Address
		if (address_latch == 0)
		{
			tram_addr.reg = (uint16_t)((data & 0x3F) << 8) | (tram_addr.reg & 0x00FF);
			address_latch = 1;
		}
		else {
			tram_addr.reg = (tram_addr.reg & 0xFF00) | data;
			vram_addr = tram_addr;
			address_latch = 0;
		}

		break;
	case 0x0007: //PPU Data
		ppuWrite(vram_addr.reg, data);
		vram_addr.reg += (control.increment_mode ? 32 : 1);
		break;
	}
}

uint8_t ludo2c02::ppuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;
	addr &= 0x3FFF;
	if (cart->ppuRead(addr, data)) {

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{//patttern
		data = tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{//name table
		addr &= 0x0FFF;
		switch (cart->mirror) {
		case Cartridge::VERTICAL:
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];

			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[1][addr & 0x03FF];

			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[0][addr & 0x03FF];

			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
			break;
		case Cartridge::HORIZONTAL:
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];

			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[0][addr & 0x03FF];

			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[1][addr & 0x03FF];

			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
			break;
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{//palette
		addr &= 0x001F;//mask bottom 5 bits
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = tblPalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
	}

	return data;
}

void ludo2c02::ppuWrite(uint16_t addr, uint8_t data)
{
	addr &= 0x3FFF;//masking address to beyond its addressable range
	if (cart->ppuWrite(addr, data)) {

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{//pattern
		tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{//name table
		addr &= 0x0FFF;
		switch (cart->mirror) {
		case Cartridge::VERTICAL:
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;

			else if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[1][addr & 0x03FF] = data;

			else if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[0][addr & 0x03FF] = data;

			else if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
			break;
		case Cartridge::HORIZONTAL:
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;

			else if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[0][addr & 0x03FF] = data;

			else if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[1][addr & 0x03FF] = data;

			else if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
			break;
		}

	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{//palette
		addr &= 0x001F;//mask bottom 5 bits
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		tblPalette[addr] = data;
	}
}

void ludo2c02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
}

void ludo2c02::reset()
{
	fine_x = 0x00;
	address_latch = 0x00;
	ppu_data_buffer = 0x00;
	scanline = 0;
	cycle = 0;
	bg_next_tile_id = 0x00;
	bg_next_tile_attrib = 0x00;
	bg_next_tile_lsb = 0x00;
	bg_next_tile_msb = 0x00;
	bg_shifter_pattern_lo = 0x0000;
	bg_shifter_pattern_hi = 0x0000;
	bg_shifter_attrib_lo = 0x0000;
	bg_shifter_attrib_hi = 0x0000;
	status.reg = 0x00;
	mask.reg = 0x00;
	control.reg = 0x00;
	vram_addr.reg = 0x0000;
	tram_addr.reg = 0x0000;
}

void ludo2c02::clock()
{
	//helper functions
	auto IncremementScrollX = [&]() {
		if (mask.render_background || mask.render_sprites) //doesnt apply without rendering
		{//one name table is 32x30 tables, as we increment in X we may cross into
			//next nametable, or wrap around to name table on left
			if (vram_addr.coarse_x == 31) {
				//leaving name table - need to wrap around

				vram_addr.coarse_x = 0;
				vram_addr.name_table_x = ~vram_addr.name_table_x;
			}
			else {
				vram_addr.coarse_x++;
			}
		}

	};

	auto IncremementScrollY = [&]() {
		if (mask.render_background || mask.render_sprites) {
			if (vram_addr.fine_y < 7) {//if possible, always increment y/scanline

				vram_addr.fine_y++;
			}
			else {
				//we are going past the max scanlines in this tile, will need
				// to investigate which is the next tile (what nametable)
				vram_addr.fine_y = 0;
				//check if we need to swap vert name tables
				if (vram_addr.coarse_y == 29) {
					//leaving name table - need to wrap around

					vram_addr.coarse_y = 0;
					vram_addr.name_table_y = ~vram_addr.name_table_y;
				}
				else if (vram_addr.coarse_y == 31) {
					//we are in attribute memeory - just wrap around current nametable
					vram_addr.coarse_y = 0;

				}
				else {
					//otherwise just move coarse y
					vram_addr.coarse_y++;
				}
			}

		}};

	auto TransferAddressX = [&]() {
		if (mask.render_background || mask.render_sprites) {
			vram_addr.name_table_x = tram_addr.name_table_x;
			vram_addr.coarse_x = tram_addr.coarse_x;
		}
	};
	auto TransferAddressY = [&]() {
		if (mask.render_background || mask.render_sprites) {
			vram_addr.fine_y = tram_addr.fine_y;
			vram_addr.name_table_y = tram_addr.name_table_y;
			vram_addr.coarse_y = tram_addr.coarse_y;
		}
	};
	auto LoadBackgroundShifters = [&]() {
		bg_shifter_pattern_lo = (bg_shifter_pattern_lo & 0xFF00) | bg_next_tile_lsb;
		bg_shifter_pattern_hi = (bg_shifter_pattern_hi & 0xFF00) | bg_next_tile_msb;
		bg_shifter_attrib_lo = (bg_shifter_attrib_lo & 0xFF00) | ((bg_next_tile_attrib & 0b01) ? 0xFF : 0x00);
		bg_shifter_attrib_hi = (bg_shifter_attrib_hi & 0xFF00) | ((bg_next_tile_attrib & 0b10) ? 0xFF : 0x00);
	};
	auto UpdateShifters = [&]() {
		if (mask.render_background) {
			bg_shifter_attrib_lo <<= 1;
			bg_shifter_attrib_hi <<= 1;
			bg_shifter_pattern_hi <<= 1;
			bg_shifter_pattern_lo <<= 1;
		}
		if (cycle >= 1 && cycle < 258 && mask.render_sprites) {
			for (int i = 0; i < sprite_count; i++) {
				if (spriteScanline[i].x > 0) {
					spriteScanline[i].x--;
				}
				else {
					sprite_shifter_pattern_lo[i] <<= 1;
					sprite_shifter_pattern_hi[i] <<= 1;
				}
			}
		}
	};
	if (scanline >= -1 && scanline < 240)//visible scanlines
	{
		if (scanline == 0 && cycle == 0)
		{
			// "Odd Frame" cycle skip
			cycle = 1;
		}
		if (scanline == -1 && cycle == 1) {
			status.vertical_blank = 0;
			status.sprite_zero_hit = 0;
			status.sprite_overflow = 0;
			for (int i = 0; i < 8; i++) {
				sprite_shifter_pattern_lo[i] = 0;
				sprite_shifter_pattern_hi[i] = 0;
			}


		}
		//lots of magic numbers taken from nesdev wiki - Loopy logic
		if ((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338)) {
			UpdateShifters();
			switch ((cycle - 1) % 8) {

			case 0:
				LoadBackgroundShifters();
				bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
				break;

			case 2:
				bg_next_tile_attrib = ppuRead(0x23C0 | (vram_addr.name_table_y << 11)
					| (vram_addr.name_table_x << 10)
					| ((vram_addr.coarse_y >> 2) << 3)
					| (vram_addr.coarse_x >> 2)
				);
				if (vram_addr.coarse_y & 0x02) bg_next_tile_attrib >>= 4;

				if (vram_addr.coarse_x & 0x02) bg_next_tile_attrib >>= 2;
				bg_next_tile_attrib &= 0x03;
				break;


			case 4:
				bg_next_tile_lsb = ppuRead((control.pattern_background << 12)
					+ ((uint16_t)bg_next_tile_id << 4)
					+ (vram_addr.fine_y) + 0);
				break;
			case 6:
				bg_next_tile_msb = ppuRead((control.pattern_background << 12)
					+ ((uint16_t)bg_next_tile_id << 4)
					+ (vram_addr.fine_y) + 8);
				break;
			case 7:
				IncremementScrollX();
				break;

			}
		}
		if (cycle == 256)//end of scanline
		{
			IncremementScrollY();

		}
		if (cycle == 257)//end of scanline
		{
			LoadBackgroundShifters();
			TransferAddressX();

		}

		if (cycle == 338 || cycle == 340)
		{
			bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
		}

		if (scanline == -1 && cycle >= 280 && cycle < 305) {
			TransferAddressY();

		}

		if (cycle == 257 && scanline >=0)//end of scanline
		{
			std::memset(spriteScanline, 0xFF, 8 * sizeof(sObjectAttributeEntry));
			//FF so that it wont be visible
			sprite_count = 0;
			for (uint8_t i = 0; i < 8; i++)
			{
				sprite_shifter_pattern_lo[i] = 0;
				sprite_shifter_pattern_hi[i] = 0;
			}
			uint8_t nOAMEntry = 0; //sprite search in next scanline
			while (nOAMEntry < 64 && sprite_count < 9) {
				int16_t diff = (int16_t)scanline - (int16_t)OAM[nOAMEntry].y;
				if (diff >= 0 && diff < (control.sprite_size ? 16 : 8)) {
					//scanline includes sprite
					if (sprite_count < 8) {
						memcpy(&spriteScanline[sprite_count], &OAM[nOAMEntry], sizeof(sObjectAttributeEntry));
						sprite_count++;
						if (nOAMEntry == 0)
							bSpriteZeroHitPossible = true;
					}
					
				}
				nOAMEntry++;
			}
			status.sprite_overflow = sprite_count > 8;
		}
		if (cycle == 340) {
			for (uint8_t i = 0; i < sprite_count; i++) {


				uint8_t sprite_pattern_bits_lo, sprite_pattern_bits_hi;
				uint16_t sprite_pattern_addr_lo, sprite_pattern_addr_hi;

				if (!control.sprite_size) {
					//8x8 mode
					if (spriteScanline[i].attribute & 0x80) {//Vertical flipped
						sprite_pattern_addr_lo =
							(control.pattern_sprite << 12)
							| (spriteScanline[i].id << 4)
							| (7 - (scanline - spriteScanline[i].y));
					}
					else {
						sprite_pattern_addr_lo =
							(control.pattern_sprite << 12)
							| (spriteScanline[i].id << 4)
							| (scanline - spriteScanline[i].y);
					}
					
				}
				else {//8x16 mode
					if (spriteScanline[i].attribute & 0x80) {//Vertical flipped
						if (scanline - spriteScanline[i].y < 8)//determine whether in top 8x8 or bottom 8x8
						{//top half
							
							sprite_pattern_addr_lo =
								((spriteScanline[i].id & 0x01) << 12)
								| ((spriteScanline[i].id & 0xFE) << 4)
								| (7 - (scanline - spriteScanline[i].y) & 0x07);
						}
						else {//bottom half
							sprite_pattern_addr_lo =
								((spriteScanline[i].id & 0x01) << 12)
								| (((spriteScanline[i].id & 0xFE) + 1) << 4)
								| (7 - (scanline - spriteScanline[i].y) & 0x07);
						}
					}
					else {//not flipped
						if (scanline - spriteScanline[i].y < 8) //determine whether in top 8x8 or bottom 8x8
						{//top half
							sprite_pattern_addr_lo =
								((spriteScanline[i].id & 0x01) << 12)
								| ((spriteScanline[i].id & 0xFE) << 4)
								| ((scanline - spriteScanline[i].y)&0x07);
						}
						else {//bottom half
							sprite_pattern_addr_lo =
								((spriteScanline[i].id & 0x01) << 12)
								| (((spriteScanline[i].id & 0xFE) + 1) << 4)
								| ((scanline - spriteScanline[i].y) & 0x07);
						}
					}
					
				}
				sprite_pattern_addr_hi = sprite_pattern_addr_lo + 8;

				sprite_pattern_bits_lo = ppuRead(sprite_pattern_addr_lo);
				sprite_pattern_bits_hi = ppuRead(sprite_pattern_addr_hi);

				if (spriteScanline[i].attribute & 0x40) {
					//stack overflow byte flipper http://stackoverflow.com/a/2602885
					auto flipbyte = [](uint8_t b) {
						b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
						b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
						b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
						return b;
					};
					sprite_pattern_bits_hi = flipbyte(sprite_pattern_bits_hi);
					sprite_pattern_bits_lo = flipbyte(sprite_pattern_bits_lo);
				}
				sprite_shifter_pattern_hi[i] = sprite_pattern_bits_hi;
				sprite_shifter_pattern_lo[i] = sprite_pattern_bits_lo;
			}
		}
	}


	if (scanline == 240) {
		// do nothing
	}


	if (scanline == 241 && cycle == 1) {
		status.vertical_blank = 1;
		if (control.enable_nmi)
			nmi = true;
	}
	//Draw tile
	uint8_t bg_pixel = 0x00;
	uint8_t bg_palette = 0x00;
	if (mask.render_background) {
		uint16_t bit_mux = 0x8000 >> fine_x;

		uint8_t p0_pixel = (bg_shifter_pattern_lo & bit_mux) > 0;
		uint8_t p1_pixel = (bg_shifter_pattern_hi & bit_mux) > 0;

		bg_pixel = (p1_pixel << 1) | p0_pixel;

		uint8_t bg_pal0 = (bg_shifter_attrib_lo & bit_mux) > 0;
		uint8_t bg_pal1 = (bg_shifter_attrib_hi & bit_mux) > 0;

		bg_palette = (bg_pal1 << 1) | bg_pal0;

	}
	uint8_t fg_pixel = 0x00;
	uint8_t fg_palette = 0x00;
	uint8_t fg_priority = 0x00;
	
	if (mask.render_sprites) {
		bSpriteZeroBeingRendered = false;
		for (uint8_t i = 0; i < sprite_count;i++ ) {
			//sprites are in OAM order
			if (spriteScanline[i].x == 0)
			{
				uint8_t fg_pixel_lo = (sprite_shifter_pattern_lo[i] & 0x80) > 0;
				uint8_t fg_pixel_hi = (sprite_shifter_pattern_hi[i] & 0x80) > 0;
				fg_pixel = (fg_pixel_hi << 1) | fg_pixel_lo;

				fg_palette = (spriteScanline[i].attribute & 0x03) + 0x04;
				fg_priority = (spriteScanline[i].attribute & 0x20) == 0;//can go behind background
				if (fg_pixel != 0)//pixel is not transparent
				{
					if (i == 0)
						bSpriteZeroBeingRendered = true;
					break;//no need to compute other fg sprites as this has highest priority (OAM order)
				}

			}
		}

	}
	uint8_t pixel = 0x00;
	uint8_t palette = 0x00;
	if (bg_pixel == 0x00 && fg_pixel == 0x00) {
		//pixel is transparent, leave as 0x00
	}
	else if (bg_pixel > 0 && fg_pixel == 0)
	{
		//fg transparent, so draw bg;
		pixel = bg_pixel;
		palette = bg_palette;
	}
	else if (bg_pixel == 0 && fg_pixel > 0)
	{
		//bg transparent, so draw fg;
		pixel = fg_pixel;
		palette = fg_palette;
	}
	else if (bg_pixel > 0 && fg_pixel > 0)//both visible, look at prio
	{
		if (fg_priority) {
			pixel = fg_pixel;
			palette = fg_palette;
		}
		else {
			pixel = bg_pixel;
			palette = bg_palette;
		}
		if (bSpriteZeroBeingRendered && bSpriteZeroHitPossible)
			if (mask.render_background & mask.render_sprites)
				if (~(mask.render_background_left | mask.render_sprites_left))
				{
					if (cycle >= 9 && cycle < 258) //left 8 pixels not being rendered
						status.sprite_zero_hit = 1;
				}
				else {
					if (cycle >= 1 && cycle < 258) //left 8 pixels not being rendered
						status.sprite_zero_hit = 1;

				}
	}
	sprScreen.SetPixel(cycle - 1, scanline, GetColourFromPaletteRam(palette, pixel));
	cycle++;
	if (cycle >= 341) {
		scanline++;
		cycle = 0;
		if (scanline >= 261) {
			scanline = -1;
			frame_complete = true;
		}
	}
}

