#include "learnRAM.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
learnRAM::learnRAM(int population)
{
	this->population = population;



}

void learnRAM::Run(float fElapsedTime)
{

	for (int i = 0; i < individuals.size(); i++)
	{
		ths.push_back(
		std::thread([this, fElapsedTime, i] {
			this->getIndividuals()[i]->Run(fElapsedTime);
			}));
		
		
	}



}

void learnRAM::Save()
{
	std::ofstream MyFile("save.txt");
	MyFile << population << " " << generation << "#";
	for (int i = 0; i < population; i++)
	{
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < 2048; k++)
				MyFile << individuals[i]->matrix[k][j] << ",";
		MyFile << "#";
	}
	MyFile.close();
}
std::vector<std::string> SplitString(
	std::string str,
	std::string delimeter)
{
	std::vector<std::string> splittedStrings = {};
	size_t pos = 0;

	while ((pos = str.find(delimeter)) != std::string::npos)
	{
		std::string token = str.substr(0, pos);
		if (token.length() > 0)
			splittedStrings.push_back(token);
		str.erase(0, pos + delimeter.length());
	}

	if (str.length() > 0)
		splittedStrings.push_back(str);
	return splittedStrings;
}
void learnRAM::Load()
{
	std::ifstream file("save.txt");
	if (file.is_open()) {
		std::string line;
		std::getline(file, line);
		auto individuals_string = SplitString(line, "#");
	
		for (int i = 0; i < population; i++)
		{
			if (i > individuals_string.size())
				break;
			auto matrix_string = SplitString(individuals_string[i + 1], ",");
			for (int j = 0; j < 2048 * 8; j++) {
				individuals[i]->matrix[j % 2048][j / 2048] = std::stof(matrix_string[j]);
			}
			 
		}
			
		

	}

}

void learnRAM::Initiate()
{
	for (size_t i = 0; i < population; i++)
	{


		auto a = std::make_shared<learnRAMIndividual>();
		a->Initiate();

		this->individuals.push_back(a);
	}
	
}

olc::Sprite* learnRAM::getScreen(int i)
{
	return &individuals[i]->NES.ppu.GetScreen();
}

std::vector<std::shared_ptr<learnRAMIndividual>> learnRAM::getIndividuals()
{
	return individuals;
}
void learnRAM::KillAll(){
	for (size_t i = 0; i < population; i++)
		individuals[i]->earlydeath = true;
}
void learnRAM::disableScreen(int i)
{
	individuals[i]->NES.ppu.disable_screen = true;
}
void learnRAM::enableScreen(int i)
{
	individuals[i]->NES.ppu.disable_screen = false;

}
bool learnRAM::AllDead()
{
	bool b = true;
	for (size_t i = 0; i < population; i++)
		b&= individuals[i]->bDead;
	

	return b;
}
void learnRAM::JoinTHS() {
	for (int i = 0; i < individuals.size(); i++)
		ths[i].join();
}

void learnRAM::Learn()
{
	std::sort(individuals.begin(), individuals.end(), [](std::shared_ptr<learnRAMIndividual> p1,
		std::shared_ptr <learnRAMIndividual> p2) {
		return p1->getScore() > p2->getScore();
		});
	Save();
	std::vector<std::shared_ptr<learnRAMIndividual>> new_individuals;
	std::cout << individuals[0]->getScore();
	for (int i = 0; i < population; i++) {
		if (i < 2) {
			auto a = std::make_shared<learnRAMIndividual>(individuals[i]->matrix);
			a->Initiate();
			new_individuals.push_back(a);
		}
		else {
			auto a = std::make_shared<learnRAMIndividual>(individuals[0]->matrix,
				individuals[1]->matrix);
			a->Initiate();
			new_individuals.push_back(a);
		}
		
	}
	individuals.clear();
	individuals = new_individuals;

	
	generation++;
}

float* learnRAM::GetControllerBtns(int i)
{
	return individuals[i]->GetControllerBtns();
}
