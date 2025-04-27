#pragma once

#include <string>
#include <random>
#include "DGDef.h"


class Character
{
public:
	Character();
	Character(int Health, int AtkPower, int Armor, std::string Name);
	int GetMaxHealth() const;
	void SetMaxHealth(int MaxHealth);
	int GetHealth() const;
	void SetHealth(int Health);
	int GetAtkPower() const;
	void SetAtkPower(int AtkPower);
	int GetArmor() const;
	void SetArmor(int Armor);
	std::string GetName() const { return Name; }
	inline bool IsAlive() const { return Health > 0; };
	virtual EAction ChooseAction() = 0;

protected:
	EAction GetActionFromInput(int Input);
	

protected:
	int MaxHealth;
	int Health;
	int AtkPower;
	int Armor;
	std::string Name;
	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};