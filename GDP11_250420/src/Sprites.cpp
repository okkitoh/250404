
#include "Sprites.h"
#include <unordered_map>

namespace Sprites
{
	std::unordered_map<SpriteID, Texture2D> spriteCache;
}

Texture2D Sprites::GetSprite(SpriteID key)
{
	switch (key)
	{
		case GRAVE:
			std::unordered_map<SpriteID, Texture2D>::iterator it = spriteCache.find(key);
			if (it != spriteCache.end())
			{
				return it->second;
			}
			Texture2D handle = LoadTexture("GDP11_250420/resources/grave.png");
			spriteCache[key] = handle;
			return handle;
	}
}