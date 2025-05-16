
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
		case UNKNOWN:
			return { DeferredLoad(KNIGHT_DEATH, "GDP11_250420/resources/AN_Knight_Dying.png"), 4, 3, 12, 8 };
		case GRAVE:
			return { DeferredLoad(GRAVE, "GDP11_250420/resources/grave.png") };
		case PARRY_ICON:
			return { DeferredLoad(PARRY_ICON, "GDP11_250420/resources/Parry_Shield.png") };
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

		case GOBLIN_IDLE:
			return { DeferredLoad(GOBLIN_IDLE, "GDP11_250420/resources/AN_Goblin_Idle.png"), 4, 3, 12, 4 };
		case GOBLIN_ATTACK:
			return { DeferredLoad(GOBLIN_ATTACK, "GDP11_250420/resources/AN_Goblin_Attack.png"), 4, 3, 12, 4 };
		case GOBLIN_DEFEND:
			return { DeferredLoad(GOBLIN_DEFEND, "GDP11_250420/resources/AN_Goblin_Defend.png"), 4, 3, 12, 4 };
		case GOBLIN_PARRY:
			return { DeferredLoad(GOBLIN_PARRY, "GDP11_250420/resources/AN_Goblin_Parry.png"), 4, 3, 12, 4 };
		case GOBLIN_HURT:
			return { DeferredLoad(GOBLIN_HURT, "GDP11_250420/resources/AN_Goblin_Hurt.png"), 4, 3, 12, 4 };
		case GOBLIN_DEATH:
			return { DeferredLoad(GOBLIN_DEATH, "GDP11_250420/resources/AN_Goblin_Dying.png"), 4, 3, 12, 4 };

		case CYCLOPS_IDLE:
			return { DeferredLoad(CYCLOPS_IDLE, "GDP11_250420/resources/AN_Cyclop_Idle.png"), 4, 3, 3, 5 };
		case CYCLOPS_ATTACK:
			return { DeferredLoad(CYCLOPS_ATTACK, "GDP11_250420/resources/AN_Cyclop_Attack.png"), 4, 3, 3, 5 };
		case CYCLOPS_DEFEND:
			return { DeferredLoad(CYCLOPS_DEFEND, "GDP11_250420/resources/AN_Cyclop_Defend.png"), 4, 3, 3, 5 };
		case CYCLOPS_PARRY:
			return { DeferredLoad(CYCLOPS_PARRY, "GDP11_250420/resources/AN_Cyclop_Parry.png"), 4, 3, 3, 5 };
		case CYCLOPS_HURT:
			return { DeferredLoad(CYCLOPS_HURT, "GDP11_250420/resources/AN_Cyclop_Hurt.png"), 4, 3, 3, 5 };
		case CYCLOPS_DEATH:
			return { DeferredLoad(CYCLOPS_DEATH, "GDP11_250420/resources/AN_Cyclop_Dying.png"), 4, 3, 3, 5 };

		case OGRE_IDLE:
			return { DeferredLoad(OGRE_IDLE, "GDP11_250420/resources/AN_Ogre_Idle.png"), 4, 3, 12, 5 };
		case OGRE_ATTACK:
			return { DeferredLoad(OGRE_ATTACK, "GDP11_250420/resources/AN_Ogre_Attack.png"), 4, 3, 12, 5 };
		case OGRE_DEFEND:
			return { DeferredLoad(OGRE_DEFEND, "GDP11_250420/resources/AN_Ogre_Defend.png"), 4, 3, 12, 5 };
		case OGRE_PARRY:
			return { DeferredLoad(OGRE_PARRY, "GDP11_250420/resources/AN_Ogre_Parry.png"), 4, 3, 12, 5 };
		case OGRE_HURT:
			return { DeferredLoad(OGRE_HURT, "GDP11_250420/resources/AN_Ogre_Hurt.png"), 4, 3, 12, 5 };
		case OGRE_DEATH:
			return { DeferredLoad(OGRE_DEATH, "GDP11_250420/resources/AN_Ogre_Dying.png"), 4, 3, 12, 5 };

		case SKELETON_KNIGHT_IDLE:
			return { DeferredLoad(SKELETON_KNIGHT_IDLE, "GDP11_250420/resources/AN_Skeleton_Idle.png"), 4, 3, 12, 5 };
		case SKELETON_KNIGHT_ATTACK:
			return { DeferredLoad(SKELETON_KNIGHT_ATTACK, "GDP11_250420/resources/AN_Skeleton_Attack.png"), 4, 3, 12, 5 };
		case SKELETON_KNIGHT_DEFEND:
			return { DeferredLoad(SKELETON_KNIGHT_DEFEND, "GDP11_250420/resources/AN_Skeleton_Defend.png"), 4, 3, 12, 5 };
		case SKELETON_KNIGHT_PARRY:
			return { DeferredLoad(SKELETON_KNIGHT_PARRY, "GDP11_250420/resources/AN_Skeleton_Parry.png"), 4, 3, 12, 5 };
		case SKELETON_KNIGHT_HURT:
			return { DeferredLoad(SKELETON_KNIGHT_HURT, "GDP11_250420/resources/AN_Skeleton_Hurt.png"), 4, 3, 12, 5 };
		case SKELETON_KNIGHT_DEATH:
			return { DeferredLoad(SKELETON_KNIGHT_DEATH, "GDP11_250420/resources/AN_Skeleton_Dying.png"), 4, 3, 12, 5 };
	}
}