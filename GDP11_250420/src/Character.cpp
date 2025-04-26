
#include "Character.h"



Character::Character()
{
	this->MaxHealth = 0;
	this->Health = 0;
	this->AtkPower = 0;
	this->Armor = 0;
	this->Name = "";
	Generator = std::mt19937(std::random_device{}());
	Distribution.param(std::uniform_int_distribution<>::param_type(0, 2));
	
}
Character::Character(int Health, int AtkPower, int Armor, std::string Name)
{
	this->Health = Health;
	this->MaxHealth = Health;
	this->AtkPower = AtkPower;
	this->Armor = Armor;
	this->Name = Name;
	Generator = std::mt19937(std::random_device{}());
	Distribution.param(std::uniform_int_distribution<>::param_type(0, 2));
}
int Character::GetMaxHealth() const
{
	return MaxHealth;
}
void Character::SetMaxHealth(int MaxHealth)
{
	this->MaxHealth = MaxHealth;
}
int Character::GetHealth() const
{
	return this->Health;
}
void Character::SetHealth(int Health)
{
	this->Health = std::min(std::max(0, Health), MaxHealth);
}
int Character::GetAtkPower() const
{
	return this->AtkPower;
}
void Character::SetAtkPower(int AtkPower)
{
	this->AtkPower = AtkPower;
}
int Character::GetArmor() const
{
	return this->Armor;
}
void Character::SetArmor(int Armor)
{
	this->Armor = Armor;
}

Action Character::GetActionFromInput(int Input)
{
	switch (Input)
	{
	case 0: return Action::ATTACK;
	case 1: return Action::PARRY;
	case 2: return Action::DEFEND;
	default:return Action::NONE;
		// case 0:
		//	return "Attack";
		// case 1:
		//	return "Parry";
		// case 2:
		// 	return "Defend";
		// default:
		//	break;
	}
}