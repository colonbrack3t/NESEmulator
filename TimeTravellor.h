#pragma once
#include <queue>
#include "Bus.h"
class TimeTravellor
{
public:
	TimeTravellor(Bus * nes, int move_nums);
	uint8_t ControllerVals();

private:
	Bus * NES;
	std::queue<uint8_t> NextMoves;
	static const int comb_size = 11;
	uint8_t  combinations[comb_size] = {
			0b10000000,//X
			0b01000000,//Z
			0b00001000,//Down
			0b00000100,//Up
			0b00000010,//Left
			0b00000001,//Right
			0b10000010,//Right + X
			0b10000001,//Left + X
			0b01000010,//Right + Z
			0b01000001,//Left + Z
			0b11000001,//X + Z
	};
	std::vector<std::array<uint8_t, 5>> moves;
	void generate_moves();
	int num_moves;
	float valueState(Bus * nes, std::array<uint8_t, 5> sequence);

	uint8_t score_addr = 0x07DD;
	uint8_t score_len = 6;
	uint8_t xPos_addr = 0x0071;
	uint8_t status_addr = 0x000E;
	uint8_t world_addr = 0x075F;
};

