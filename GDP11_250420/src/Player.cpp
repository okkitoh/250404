
#include "Player.h"
#include <iostream>
#include <string>



Player::Player() : Character()
{
	this->Reset();
}
// Passes all arguments to Character Constructor
Player::Player(int Health, int AtkPower, int Armor, std::string Name) : Character(Health, AtkPower, Armor, Name)
{
	this->Reset();
}
std::map<ItemID, int>& Player::GetInventory()
{
	return Inventory;
}
EAction Player::ChooseAction()
{
	int Input;
	while (true)
	{
		std::cout << "Choose an action - (1: Attack, 2: Parry, 3: Defend)" << std::endl;
		std::cin >> Input;
		if (std::cin.fail() || Input < 1 || Input > 3)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid input : You must enter 1, 2, or 3 - (1: Attack, 2: Parry, 3: Defend)" << std::endl;
		}
		else
		{
			break;
		}
	}
	Input -= 1;

	return GetActionFromInput(Input);
}
void Player::Reset()
{
	// Base Stats
	this->MaxHealth = 5;
	this->Health = this->MaxHealth;
	this->AtkPower = 2;
	this->Armor = 2;
	this->Name = "Guy";

	this->ParryMax = 3.0;
	this->ParryCounter = this->ParryMax;
	this->ParryRegen = 0.5;

	this->Inventory.clear();
	this->Inventory[CONSUMABLE_POTION] = 3;
	this->Inventory[CONSUMABLE_BLIND] = 2;
}