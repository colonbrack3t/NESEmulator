#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "Bus.h"
#include "Brain.h"
#include "learnRAM.h"
#include <bitset>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"






class Simulator : public olc::PixelGameEngine
{
public: 
	Simulator() { sAppName = "Simulator";  }
	int watching = 0;
	int pop = 12;
	bool followLeader = false;
	learnRAM brain = learnRAM(pop);
	bool OnUserCreate()
	{
		srand(time(nullptr));
	
		brain.Initiate();
		//brain.Load();
		brain.Run(0);
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) {
		Clear(olc::DARK_BLUE);
		for (int i = 0; i < pop; i++) {
			if (i != watching) {
				brain.disableScreen(i);
			}
			else {
				brain.enableScreen(i);
			}
		}
		DrawSprite(0, 0, brain.getScreen(watching),2);
		DrawString(0, 0, std::to_string(watching));
		float* controllerBtns = brain.GetControllerBtns(watching);
		DrawString((0 * 8 * 10), 480, "Right");
		DrawString((1 * 8 * 10), 480, "Left");
		DrawString((2 * 8 * 10), 480, "Down");
		DrawString((3 * 8 * 10), 480, "Up");
		DrawString((4 * 8 * 10), 480, "Z");
		DrawString((5 * 8 * 10), 480, "X");
		
		for (int i = 0; i < 6; i++) {
			
			auto w = *(controllerBtns + i);
			DrawString((i * 8*10), 490 , std::to_string(w),w>0? olc::GREEN : olc::RED );
			
		}
		
		DrawString(0, 500, std::bitset<8>(brain.getIndividuals()[watching]->NES.controller[0]).to_string());
		if (GetKey(olc::Key::RIGHT).bReleased)
			watching = (watching + 1) % pop;
		if (GetKey(olc::Key::ESCAPE).bReleased)
			brain.KillAll();
		if (GetKey(olc::Key::SPACE).bReleased)
			followLeader = !followLeader;
		if (followLeader) {
			int highest = 0;
			int ind = 0;
			for (int i = 0; i < pop; i++) {
				if(!brain.getIndividuals()[i]->bDead)
				if (brain.getIndividuals()[i]->getScore() > highest)
				{
					ind = i; highest = brain.getIndividuals()[i]->getScore();
				}
			}
			watching = ind;
		}
		bool alldead = brain.AllDead();

		if (alldead) {

			//brain.JoinTHS();//should be immediate
			brain.Learn();
			brain.Run(0);
		}
		return true;
	}
	
};


int main()
{
	Simulator sim;
	sim.Construct(512, 510, 2, 2);// (780, 480, 2, 2);
	sim.Start();

	return 0;
}

