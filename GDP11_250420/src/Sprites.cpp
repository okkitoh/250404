
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
			printf("Cache hit\n");
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
			return { DeferredLoad(KNIGHT_IDLE, "GDP11_250420/resources/AN_Knight_Idle.png"), 4, 3, 3 };
	}
}