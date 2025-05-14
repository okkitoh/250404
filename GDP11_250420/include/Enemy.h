#pragma once

#include "Character.h"
#include "Sprites.h"


class Enemy : public Character
{
public:
	Enemy();
	Enemy(int Health, int AtkPower, int Armor, std::string Name);
	EMobType GetMobType();
	EAction ChooseAction() override;
	void IncreaseDifficulty(int RoundNumber);

	static SpriteID GetDeathSprite(EMobType MobType);
	static SpriteID GetHurtSprite(EMobType MobType);
	static SpriteID GetActionSprite(EMobType MobType, EAction action);
private:
	EMobType MobType;
//private:
//	std::mt19937 Generator;
//	std::uniform_int_distribution<> Distribution;
};
