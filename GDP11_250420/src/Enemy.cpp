
#include "Enemy.h"



Enemy::Enemy() : Character()
{
	
}
// Passes all arguments to Character Constructor
Enemy::Enemy(int Health, int AtkPower, int Armor, std::string Name) : Character(Health, AtkPower, Armor, Name)//, Generator(std::random_device{}()), Distribution(0, 2)
{
	Enemy();
}
EMobType Enemy::GetMobType()
{
	return MobType;
}
EAction Enemy::ChooseAction()
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
			MobType = KNIGHT;
			break;
		case 4:
			MaxHealth += RoundNumber;
			Health = MaxHealth;
			AtkPower += RoundNumber;
			Name = "Skeleton Knight";
			MobType = SKELETON_KNIGHT;
			break;
		case 3:
			MaxHealth += RoundNumber;
			Health = MaxHealth;
			AtkPower += RoundNumber;
			Name = "Ogre";
			MobType = OGRE;
			break;
		case 2:
			MaxHealth = 2;
			Health = MaxHealth;
			AtkPower = 2;
			Name = "Cyclops";
			MobType = CYCLOPS;
			break;
		case 1:
		default:
			MaxHealth = 1;
			Health = MaxHealth;
			AtkPower = 1;
			Name = "Goblin";
			MobType = GOBLIN;
			break;
	}
	this->SetMaxHealth(Health);
}
SpriteID Enemy::GetDeathSprite(EMobType MobType)
{
	switch (MobType)
	{
		case GOBLIN: return GOBLIN_DEATH;
		case CYCLOPS: return CYCLOPS_DEATH;
		case OGRE: return OGRE_DEATH;
		case SKELETON_KNIGHT: return SKELETON_KNIGHT_DEATH;
		case KNIGHT: return KNIGHT_DEATH;
	}
}
SpriteID Enemy::GetHurtSprite(EMobType MobType)
{
	switch (MobType)
	{
		case GOBLIN: return GOBLIN_HURT;
		case CYCLOPS: return CYCLOPS_HURT;
		case OGRE: return OGRE_HURT;
		case SKELETON_KNIGHT: return SKELETON_KNIGHT_HURT;
		case KNIGHT: return KNIGHT_HURT;
	}
}
SpriteID Enemy::GetActionSprite(EMobType MobType, EAction action)
{
	switch (action)
	{
		case ATTACK:
			switch (MobType)
			{
				case GOBLIN: return GOBLIN_ATTACK;
				case CYCLOPS: return CYCLOPS_ATTACK;
				case OGRE: return OGRE_ATTACK;
				case SKELETON_KNIGHT: return SKELETON_KNIGHT_ATTACK;
				case KNIGHT: return KNIGHT_ATTACK;
			}
			break;
		case DEFEND:
			switch (MobType)
			{
				case GOBLIN: return GOBLIN_DEFEND;
				case CYCLOPS: return CYCLOPS_DEFEND;
				case OGRE: return OGRE_DEFEND;
				case SKELETON_KNIGHT: return SKELETON_KNIGHT_DEFEND;
				case KNIGHT: return KNIGHT_DEFEND;
			}
			break;
		case PARRY:
			switch (MobType)
			{
				case GOBLIN: return GOBLIN_PARRY;
				case CYCLOPS: return CYCLOPS_PARRY;
				case OGRE: return OGRE_DEFEND;
				case SKELETON_KNIGHT: return SKELETON_KNIGHT_DEFEND;
				case KNIGHT: return KNIGHT_DEFEND;
			}
			break;
		case IDLE:
		case NONE:
		default:
			switch (MobType)
			{
				//case CYCLOPS: return
				case GOBLIN: return GOBLIN_IDLE;
				case CYCLOPS: return CYCLOPS_IDLE;
				case OGRE: return OGRE_IDLE;
				case SKELETON_KNIGHT: return SKELETON_KNIGHT_IDLE;
				case KNIGHT: return KNIGHT_IDLE;
			}
			break;
	}
	return UNKNOWN;
}
