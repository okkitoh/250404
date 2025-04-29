
#pragma once

#include <iostream>
#include <functional>
class Character;



static constexpr float WINDOW_WIDTH = 1280.f;
static constexpr float WINDOW_HEIGHT = 720.f;
static constexpr int MAX_DIFFICULTY = 5;
static constexpr bool GOD_MODE = 0;
static constexpr int MAX_ENEMIES = 1;


enum EViewContext
{
	EXIT,
	START_MENU,
	GAME_RUNNING,
	GAME_OVER,
	PROCESSING
};


enum EAction
{
	IDLE,
	ATTACK,
	PARRY,
	DEFEND,
	NONE
};


typedef struct BattleResult
{
	Character* instigator;
	Character* target;
	EAction action;
	EAction result;
	int damage;
	std::function<void()> callback;
} BattleResult;


