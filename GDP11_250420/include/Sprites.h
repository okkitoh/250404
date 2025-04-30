#pragma once

#include "raylib.h"

struct Sprite
{
	Texture2D tex = { 0 };
	int columns = 1;
	int rows = 1;
	//int u = 0; // not used until texture atlasing
	//int v = 0; // not used until texture atlasing
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