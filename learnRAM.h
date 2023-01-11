#pragma once
#include "Brain.h"
#include "learnRAMIndividual.h"
#include <vector>
#include "olcPixelGameEngine.h"
class learnRAM :
	public Brain
{
public:
	learnRAM(int population);
	
	void Run(float fElapsedTime) override;
	void Save() override;
	void Load() override;
	void Initiate();
	olc::Sprite* getScreen(int i);
	std::vector<std::shared_ptr<learnRAMIndividual>> getIndividuals();
	bool AllDead();
	void JoinTHS();
	void Learn();
	float* GetControllerBtns(int i);
	void KillAll();
	void disableScreen(int i);
	void enableScreen(int i);
private:
	int population;
	std::vector<std::thread> ths;
	int generation = 0;
		
	
	std::vector<std::shared_ptr<learnRAMIndividual>> individuals;
};

