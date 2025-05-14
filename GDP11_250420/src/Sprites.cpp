
#include "Sprites.h"
#include <map>
#include <string>


namespace Sprites
{
	std::map<SpriteID, Texture2D> spriteCache = std::map<SpriteID, Texture2D>();

	Texture2D DeferredLoad(SpriteID key, std::string path)
	{
		std::map<SpriteID, Texture2D>::iterator it = spriteCache.find(key);
		if (it != spriteCache.end())
		{
			return it->second;
		}
		Texture2D handle = LoadTexture(path.c_str());
		spriteCache[key] = handle;
		return handle;
	}
}



Sprite Sprites::GetSprite(SpriteID key)
{
	switch (key)
	{
		case GRAVE:
			return { DeferredLoad(GRAVE, "GDP11_250420/resources/grave.png") };
		case KNIGHT_IDLE:
			return { DeferredLoad(KNIGHT_IDLE, "GDP11_250420/resources/AN_Knight_Idle.png"), 4, 3, 3, 5 };
		case KNIGHT_ATTACK:
			return { DeferredLoad(KNIGHT_ATTACK, "GDP11_250420/resources/AN_Knight_Attack.png"), 4, 3, 12, 18 };
		case KNIGHT_DEFEND:
			return { DeferredLoad(KNIGHT_DEFEND, "GDP11_250420/resources/AN_Knight_Defend.png"), 4, 3, 12, 18 };
		case KNIGHT_PARRY:
			return { DeferredLoad(KNIGHT_PARRY, "GDP11_250420/resources/AN_Knight_Parry.png"), 4, 3, 12, 12 };
		case KNIGHT_HURT:
			return { DeferredLoad(KNIGHT_HURT, "GDP11_250420/resources/AN_Knight_Hurt.png"), 4, 3, 12, 12 };
		case KNIGHT_DEATH:
			return { DeferredLoad(KNIGHT_DEATH, "GDP11_250420/resources/AN_Knight_Dying.png"), 4, 3, 12, 4 };
	}
}