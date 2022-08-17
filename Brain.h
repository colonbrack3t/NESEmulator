#pragma once
#include <cstdint>
class Brain
{

public: 
	Brain();
	~Brain();

	virtual void Run(float fElapsedTime) = 0;
	virtual void Save() = 0;
	virtual void Load() = 0;

};

