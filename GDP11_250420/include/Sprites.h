#pragma once

#include "raylib.h"

struct Sprite
{
	Texture2D tex = { 0 };
	int columns = 1;   // Must span whole width of sheet
	int rows = 1;      // Must span whole height of sheet
	int keyframes = 1; // Total nummber of frames in animation
	int frameRate = 1; // assuming 60 frames in second, how many times played in a second?
};


enum SpriteID
{
	GRAVE,
	KNIGHT_IDLE,
	KNIGHT_ATTACK,
	KNIGHT_DEFEND,
	KNIGHT_PARRY,
	KNIGHT_HURT,
	KNIGHT_DEATH
};


namespace Sprites
{
	Sprite GetSprite(SpriteID key);
}