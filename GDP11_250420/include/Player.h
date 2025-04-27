#pragma once

#include "Character.h"



class Player : public Character
{
public:
	Player();
	Player(int Health, int AtkPower, int Armor, std::string Name);
	void Reset()
	{
		SetHealth(GetMaxHealth());
	}
	EAction ChooseAction() override;
};


/*
	Public members of Character remain public in Player.
	Protected members of Character remain protected in Player.
	Private members of Character remain inaccessible to Player (thought Player can access them indirectly via public or protected methods in Character)

*/
