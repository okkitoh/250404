#pragma once

#include <random>
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(int Health, int AtkPower, int Armor, std::string Name);
	void IncreaseDifficulty(int RoundNumber);

	Action ChooseAction() override;

private:
	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};
