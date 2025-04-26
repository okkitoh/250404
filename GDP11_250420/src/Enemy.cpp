
#include "Enemy.h"



Enemy::Enemy() : Character()
{
	
}
// Passes all arguments to Character Constructor
Enemy::Enemy(int Health, int AtkPower, int Armor, std::string Name) : Character(Health, AtkPower, Armor, Name)//, Generator(std::random_device{}()), Distribution(0, 2)
{
	Enemy();
}
Action Enemy::ChooseAction()
{
	int ActionInput = Distribution(Generator);
	return GetActionFromInput(ActionInput);
}
void Enemy::IncreaseDifficulty(int RoundNumber)
{
	switch (RoundNumber)
	{
	case 5:
		MaxHealth += RoundNumber;
		Health = MaxHealth;
		AtkPower += RoundNumber;
		Armor += RoundNumber / 2;
		Name = "Knight Champion";
		break;
	case 4:
		MaxHealth += RoundNumber;
		Health = MaxHealth;
		AtkPower += RoundNumber;
		Name = "Berserker";
		break;
	case 3:
		MaxHealth += RoundNumber;
		Health = MaxHealth;
		AtkPower += RoundNumber;
		Name = "Gladiator";
		break;
	case 2:
		MaxHealth = 2;
		Health = MaxHealth;
		AtkPower = 2;
		Name = "Goblin Warrior";
		break;
	case 1:
	default:
		MaxHealth = 1;
		Health = MaxHealth;
		AtkPower = 1;
		Name = "Slime";
	}
	this->SetMaxHealth(Health);
}