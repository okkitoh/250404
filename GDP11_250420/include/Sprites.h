#pragma once

#include "raylib.h"

struct Sprite
{
	Texture2D tex = { 0 };
	int columns = 1;   // Must span whole width of sheet
	int rows = 1;      // Must span whole height of sheet
	int keyframes = 1; // Total nummber of frames in animation
};


enum SpriteID
{
	GRAVE,
	KNIGHT_IDLE
};


namespace Sprites
{
	Sprite GetSprite(SpriteID key);
}