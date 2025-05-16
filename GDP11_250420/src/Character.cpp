
#include "Character.h"



Character::Character()
{
	this->MaxHealth = 0;
	this->Health = 0;
	this->AtkPower = 0;
	this->Armor = 0;
	this->Name = "";

	this->ParryCounter = 0.0;
	this->ParryMax = 0.0;
	this->ParryRegen = 0.0;
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
double Character::GetParryCounter()
{
	return ParryCounter;
}
double Character::GetParryMax()
{
	return ParryMax;
}
double Character::GetParryRegen()
{
	return ParryRegen;
}

void Character::Tick()
{
	this->ParryCounter += this->ParryRegen;
	this->ParryCounter = fmin(this->ParryCounter, this->ParryMax);
}
bool Character::CanUseAction(EAction action)
{
	switch (action)
	{
		case PARRY: return static_cast<int>(this->ParryCounter) >= 1;
		default: return true;
	}
}
void Character::UseParry()
{
	this->ParryCounter -= 1.0;
	this->ParryCounter = fmax(this->ParryCounter, 0);
}
EAction Character::GetActionFromInput(int Input)
{
	switch (Input)
	{
	case 0: return EAction::ATTACK;
	case 1: return EAction::PARRY;
	case 2: return EAction::DEFEND;
	default:return EAction::NONE;
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