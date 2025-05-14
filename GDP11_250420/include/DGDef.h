
#pragma once

#include <iostream>
#include <functional>
class Character;

constexpr int TARGET_FPS = 60;
constexpr float WINDOW_WIDTH = 1280.f;
constexpr float WINDOW_HEIGHT = 720.f;
constexpr int MAX_DIFFICULTY = 5;
constexpr bool GOD_MODE = 0;
constexpr int MAX_ENEMIES = 1;


enum EViewContext
{
	EXIT,
	START_MENU,
	GAME_RUNNING,
	GAME_OVER
};

enum EAction
{
	IDLE,
	ATTACK,
	PARRY,
	DEFEND,
	NONE
};

enum EMobType
{
	GOBLIN,
	CYCLOPS,
	OGRE,
	SKELETON_KNIGHT,
	KNIGHT
};

typedef struct BattleResult
{
	Character* instigator;
	Character* target;
	EAction action;
	EAction result;
	int damage;
} BattleResult;


