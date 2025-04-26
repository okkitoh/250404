#pragma once

#include "raylib.h"



enum SpriteID
{
	GRAVE
};


namespace Sprites
{
	Texture2D GetSprite(SpriteID key);
}