#include "TimeTravellor.h"

TimeTravellor::TimeTravellor(Bus * nes, int move_nums)
{
	NES = nes;
	num_moves = move_nums;
}

uint8_t TimeTravellor::ControllerVals()
{
	if (NextMoves.empty()) {
		generate_moves();
		std::sort(moves.begin(), moves.end(), [this](auto i, auto j) {
			return valueState(NES, i) >= valueState(NES, j);
			});
		
	}
	auto out = NextMoves.front();
	NextMoves.pop();

	return out;
}

void TimeTravellor::generate_moves()
{
	moves.clear();
	for (int i = 0; i < num_moves; i++) {
		std::array<uint8_t,5> sequence = { combinations[i % comb_size], 0,0,0,0 };
		for (int x = 1; x < 5; x++) {
			sequence[x] = combinations[rand() % comb_size];
		}
		moves.push_back(sequence);
	}
}

float TimeTravellor::valueState(Bus * nes, std::array<uint8_t,5> sequence)
{
	Bus nesCopy = *nes;
	Cartridge c = *(nes ->cart);
	nesCopy.insertCartridge(std::make_shared<Cartridge>(c));
	for (int i = 0; i < 5; i++) {
		nesCopy.controller[0] = sequence[i];
		for(int j = 0; j < 89001; j++)//num of cycles in a frame
			nesCopy.clock(); 
		
		do { nesCopy.clock(); } while (!nesCopy.cpu.complete());
		
		
	}
	float score = nesCopy.cpuRam[xPos_addr] * 2;
	for (size_t i = 0; i < score_len; i++)
	{
		score += nesCopy.cpuRam[score_addr] * std::pow(10, score_len - i);
	}
	return score;
}
