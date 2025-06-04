#pragma once

#include "raylib.h"



struct Sprite
{
	Texture2D tex = { 0 };
	int columns = 1;   // Must span whole width of sheet
	int rows = 1;      // Must span whole height of sheet
	int keyframes = 1; // Total nummber of frames in animation
	int frameRate = 1; // assuming 60 frames in second, how many times played in a second?
	int frameStart = 0;
};


enum SpriteID
{
	UNKNOWN,
	GRAVE,
	PARRY_ICON,
	POTION_ICON,

	KNIGHT_IDLE,
	KNIGHT_ATTACK,
	KNIGHT_DEFEND,
	KNIGHT_PARRY,
	KNIGHT_HURT,
	KNIGHT_DEATH,

	GOBLIN_IDLE,
	GOBLIN_ATTACK,
	GOBLIN_DEFEND,
	GOBLIN_PARRY,
	GOBLIN_HURT,
	GOBLIN_DEATH,

	CYCLOPS_IDLE,
	CYCLOPS_ATTACK,
	CYCLOPS_DEFEND,
	CYCLOPS_PARRY,
	CYCLOPS_HURT,
	CYCLOPS_DEATH,

	OGRE_IDLE,
	OGRE_ATTACK,
	OGRE_DEFEND,
	OGRE_PARRY,
	OGRE_HURT,
	OGRE_DEATH,

	SKELETON_KNIGHT_IDLE,
	SKELETON_KNIGHT_ATTACK,
	SKELETON_KNIGHT_DEFEND,
	SKELETON_KNIGHT_PARRY,
	SKELETON_KNIGHT_HURT,
	SKELETON_KNIGHT_DEATH
};


namespace Sprites
{
	Sprite GetSprite(SpriteID key);
}
