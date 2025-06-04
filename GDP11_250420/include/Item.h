#pragma once

#include <functional>
#include <string>
#include "Sprites.h"

class Character;



enum ItemID
{
	CONSUMABLE_POTION,
	CONSUMABLE_BLIND,
	CONSUMABLE_POTION1,
	CONSUMABLE_POTION2,
	CONSUMABLE_POTION3,
	CONSUMABLE_POTION4,
	CONSUMABLE_POTION5,
	CONSUMABLE_POTION6
};

struct Item
{
	ItemID id;
	Sprite icon;
	std::string displayName;
	std::function<void(Character& target)> onUse = [](Character&) {};
	bool isStackable = true;
};

namespace Items
{
	Item GetItem(ItemID key);
}
