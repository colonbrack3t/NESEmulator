#include "learnRAMIndividual.h"
#include <cmath>
#include <algorithm>
#include <bitset>
#include <thread>
learnRAMIndividual::learnRAMIndividual()
{
	for (size_t j = 0; j < 2048; j++)
		for (size_t k = 0; k < 8; k++)
			matrix[j][k] = ((rand() % 200) - 100) / 100.0;
}
learnRAMIndividual::learnRAMIndividual(float p1[2048][8]) {
	for (size_t j = 0; j < 2048; j++)
		for (size_t k = 0; k < 8; k++)
			matrix[j][k] = p1[j][k];
}
learnRAMIndividual::learnRAMIndividual(float p1[2048][8], float p2[2048][8])
{
	for (size_t j = 0; j < 2048; j++)
		for (size_t k = 0; k < 8; k++)
		{

			bool p1_gene = (rand() % 100) > 50;
			
			matrix[j][k] = p1_gene ? p1[j][k] : p2[j][k];
			bool mutation_chance = (rand() % 1000000) / 1000000;
			if (mutation_chance < mutationChance)
				matrix[j][k] += (rand() % 100)>50 ? 0.1: -0.1;
			

		}
	

}
void learnRAMIndividual::Run(float fElapsedTime)
{
	
	while (!dead()) {
			this->fTimeToStartMario -= 1/60.0;

			if (this->fTimeToStartMario > 0)
			{

				if (this->fTimeToStartMario < 4 && this->fTimeToStartMario > 1)
					this->NES.controller[0] = 0x10;
				else
					this->NES.controller[0] = 0x00;

			}
			else {

				this->NES.controller[0] = this->computeOutputs();
				if (this->NES.controller[0] & 0x80) {
					
					jumpHeldTime += 1 / 60.0;
					if (jumpHeldTime > jumpMaxHold)
					{

						this->NES.controller[0] &= 0x7F;
						jumpCooldown -= 1 / 60.0;
						if(jumpCooldown < 0)
						{
							jumpCooldown = 0.3f;
							jumpHeldTime = 0;
						}
					}
				}
				else {
					jumpHeldTime = 0;
					jumpCooldown = 0.3;
				}
			}
			//std::cout << std::bitset<8>(NES.controller[0]);
			do { this->NES.clock(); } while (!this->NES.ppu.frame_complete);
			this->NES.ppu.frame_complete = false;
		

	}
	bDead = true;
}
void learnRAMIndividual::Initiate()
{

	std::shared_ptr<Cartridge> cart = std::make_shared<Cartridge>("mario.nes");
	std::cout << cart->ImageValid();
	this->NES.insertCartridge(cart);

	this->NES.reset();
	

}

void learnRAMIndividual::runInThread(float fElapsedTime)
{
	
}

uint8_t learnRAMIndividual::computeOutputs()
{
	float outputs[8] = { 0 };
	for (int col = 0; col < 8; col++)
		for (int row = 0; row < 2048; row++)
			outputs[col] += NES.cpuRam[row] * matrix[row][col];
	float max = *std::max_element(outputs, outputs + 8);
	if (max < 0)
		return 0;
	uint8_t n = 0x00;
	contollerBtns[0] = outputs[0] / max;
	contollerBtns[1] = outputs[1] / max;
	contollerBtns[2] = outputs[2] / max;
	contollerBtns[3] = outputs[3] / max;
	contollerBtns[4] = outputs[6] / max;
	contollerBtns[5] = outputs[7] / max;
	float biggest = 0;
	float secondbiggest = 0;
	int ind1 = -1;
	int ind2 = -1;
	for (int i = 0; i < 6; i++) {
		if (contollerBtns[i] > 0) {
			if (contollerBtns[i] > biggest) {
				secondbiggest = biggest;
				ind2 = ind1;
				biggest = contollerBtns[i];
				ind1 = i;
			}
			else if (contollerBtns[i] > secondbiggest) {
				secondbiggest = contollerBtns[i];
				ind2 = i;
			}
		}
	}
	if (biggest > 0) {
		n |= 0x01 << (ind1 > 3 ? ind1 + 2 : ind1);
	}
	if (secondbiggest > 0) {
		n |= 0x01 << (ind2 > 3 ? ind2 + 2 : ind2);
	}

	

	return n;
}

int learnRAMIndividual::getScore()
{
	int score = this->NES.cpuRam[xPos_addr]*2;
	for (size_t i = 0; i < score_len; i++)
	{
		score += this->NES.cpuRam[score_addr] * std::pow(10, score_len - i);
	}
	return score;
}

float* learnRAMIndividual::GetControllerBtns()
{
	return contollerBtns;
}


bool learnRAMIndividual::dead()
{


	return this->NES.cpuRam[status_addr] == 6 || this->NES.cpuRam[status_addr] == 11|| earlydeath;
}





