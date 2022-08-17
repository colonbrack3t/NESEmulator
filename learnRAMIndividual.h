#pragma once
#include "Bus.h"
class learnRAMIndividual
{
public:
	learnRAMIndividual();
	learnRAMIndividual(float p1[2048][8]);
	learnRAMIndividual(float p1[2048][8], float p2[2048][8]);
	void Run(float fElapsedTime);
	Bus NES;
	void Initiate();
	void runInThread(float fElapsedTime);
	bool bDead = false;
	int getScore();
	float matrix[2048][8];
	float* GetControllerBtns();
	bool earlydeath = false;
private:
	float mutationChance = 0.01;
	uint8_t computeOutputs();

	uint8_t score_addr = 0x07DD;
	uint8_t score_len = 6;
	uint8_t xPos_addr = 0x0071;
	uint8_t status_addr = 0x000E;
	uint8_t world_addr = 0x075F;

	bool dead();
	
	float fResidualTime = 0.0f;
	float fTimeToStartMario = 5.0f;
	float contollerBtns[6] = {0};
	float jumpCooldown = 0.0f;
	float jumpHeldTime = 0;
	float jumpMaxHold = 0.55f;
};


