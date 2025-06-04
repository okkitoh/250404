
#include "Item.h"
#include <map>
#include "Character.h"
 



Item Items::GetItem(ItemID key)
{
	switch (key)
	{
		case CONSUMABLE_POTION:
			return { CONSUMABLE_POTION, Sprites::GetSprite(POTION_ICON), "HP Potion", [](Character& target) { target.SetHealth(target.GetHealth() + 5); }};
		case CONSUMABLE_BLIND:
			return { CONSUMABLE_BLIND, Sprites::GetSprite(POTION_ICON), "Blinding Powder", [](Character& target){} };
		case CONSUMABLE_POTION1:
			return { CONSUMABLE_POTION1, Sprites::GetSprite(POTION_ICON), "Potion 1", [](Character& target) { } };
		case CONSUMABLE_POTION2:
			return { CONSUMABLE_POTION2, Sprites::GetSprite(POTION_ICON), "Potion 2", [](Character& target) {} };
		case CONSUMABLE_POTION3:
			return { CONSUMABLE_POTION3, Sprites::GetSprite(POTION_ICON), "Potion 3", [](Character& target) {} };
		case CONSUMABLE_POTION4:
			return { CONSUMABLE_POTION4, Sprites::GetSprite(POTION_ICON), "Potion 4", [](Character& target) {} };
		case CONSUMABLE_POTION5:
			return { CONSUMABLE_POTION5, Sprites::GetSprite(POTION_ICON), "Potion 5", [](Character& target) {} };
		case CONSUMABLE_POTION6:
			return { CONSUMABLE_POTION6, Sprites::GetSprite(POTION_ICON), "Potion 6", [](Character& target) {} };
	}
}
