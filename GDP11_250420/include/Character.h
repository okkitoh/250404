#pragma once

#include <string>
#include <iostream>
#include <random>



enum Action
{
	WAIT,
	ATTACK,
	PARRY,
	DEFEND,
	NONE
};

inline std::ostream& operator<<(std::ostream& out, const Action& action)
{
	switch (action)
	{
	case ATTACK: out << "ATTACK"; break;
	case PARRY:  out << "PARRY"; break;
	case DEFEND: out << "DEFEND"; break;
	case NONE:   out << "NONE"; break;
	}
	return out;
}


class Character
{
public:
	Character();
	Character(int Health, int AtkPower, int Armor, std::string Name);
	int GetMaxHealth() const;
	void SetMaxHealth(int MaxHealth);
	int GetHealth() const;
	void SetHealth(int Amount);
	int GetAtkPower() const;
	void SetAtkPower(int AtkPower);
	int GetArmor() const;
	void SetArmor(int Armor);
	std::string GetName() const { return Name; }
	inline bool IsAlive() const { return Health > 0; };
	virtual Action ChooseAction() = 0;

protected:
	Action GetActionFromInput(int Input);
	

protected:
	int MaxHealth;
	int Health;
	int AtkPower;
	int Armor;
	std::string Name;
	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};