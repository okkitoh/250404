
#include "ItemMenu.h"
#include "Character.h"
#include "GameState.h"



ItemMenu::ItemMenu()
{
	maxcols = 2;


	AddOption("Back", []() {
		GameState::GetRef().PopView();
	});
	std::map<ItemID, int> inventory = GameState::GetRef().MainPlayer.GetInventory();
	std::map<ItemID, int>::iterator iter = inventory.begin();
	while (iter != inventory.end())
	{
		const Item it = Items::GetItem(iter->first);
		AddOption(it.displayName, []() {
			GameState::GetRef().PopView();
		});
		++iter;
	}
}

void ItemMenu::Update()
{
	int cursorX = (cursor + 1) % maxcols;
	int cursorY = (cursor + 1) / maxcols;
	int maxrows = ceilf((this->optionsOrder.size() - 1) / static_cast<float>(maxcols)) + 1;
	if (cursor == 0)
	{
		cursorX = 0;
		cursorY = 0;
	}

	if (IsKeyPressed(KEY_UP))
	{
		if (cursor == 0)
		{
			cursorY = maxrows - 1;
			cursor = ((cursorY - 1) * maxcols + cursorX) + 1;
		}
		else if (cursorX > 0 && cursorY == 1)
		{
			int remainder = maxcols - ((this->optionsOrder.size() - 1) % maxcols);
			if (cursorX >= remainder)
			{
				cursorY = maxrows - 2;
			}
			else
			{
				cursorY = maxrows - 1;
			}
			cursor = ((cursorY - 1) * maxcols + cursorX) + 1;
		}
		else if (cursorX == 0 && cursorY == 1)
		{
			cursor = 0;
		}
		else
		{
			cursor -= 2;
		}
		
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		if (cursor + 1 < this->optionsOrder.size())
		{
			cursor += 1;
		}
		else
		{
			cursor = 0;
		}
		
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		if (cursor == 0)
		{
			cursor = 1;
		}
		else if (cursor >= this->optionsOrder.size() - maxcols)
		{
			if (cursorX > 0)
			{
				cursorY = 1;
				cursor = ((cursorY - 1) * maxcols + cursorX) + 1;
			}
			else
			{
				cursor = 0;
			}
		}
		else
		{
			cursor += 2;
		}
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		if (cursor != 0)
		{
			cursor -= 1;
		}
		else
		{
			cursor = this->optionsOrder.size() - 1;
		}
	}
	if (IsKeyPressed(KEY_X)) // Cancel
	{
		if (!cursor)
		{
			options["Back"]();
		}
		cursorX = 0;
		cursorY = 0;
	}
	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) // Confirm
	{
		std::string key = optionsOrder[cursor];
		std::unordered_map<std::string, std::function<void()>>::iterator it = options.find(key);
		if (it != options.end())
		{
			it->second();
		}
	}
}
void ItemMenu::GuiDraw()
{
	DrawRectangle(0, WINDOW_HEIGHT - 287, WINDOW_WIDTH, 287, BLACK);
	float paddingLeft = 240;
	float cursorWidth = 30;

	/*
	 * available space / # of entries per row
	 */
	float cellWidth = (WINDOW_WIDTH - (paddingLeft + cursorWidth) * 2) / maxcols;

	float viewX = paddingLeft + cursorWidth;
	float viewY = WINDOW_HEIGHT - 200;
	DrawText("Back", viewX, viewY, 32, WHITE);
	viewY += 16;
	for (int i = 1; i < this->optionsOrder.size(); ++i)
	{
		if (i % 2 == 1)
		{
			viewY += 32;
			viewX = paddingLeft + cursorWidth;
		}
		DrawText(this->optionsOrder[i].c_str(), viewX, viewY, 32, WHITE);
		viewX += cellWidth;
	}

	/*
	 * Draw Menu Cursor 
	 */
	viewX = 270;
	viewY = WINDOW_HEIGHT - 200;
	int cursorX = (cursor + 1) % maxcols;
	int cursorY = (cursor + 1) / maxcols;
	if (cursor == 0)
	{
		DrawTriangle({ viewX - 30, viewY + 8 }, { viewX - 30, viewY + 20 + 8 }, { viewX - 30 + 20, viewY + 16 }, RED);
	}
	else
	{
		viewY += 16;
		viewY = viewY + (cursorY * 32);
		viewX = viewX + (cursorX * cellWidth);
		DrawTriangle({ viewX - 30, viewY + 8 }, { viewX - 30, viewY + 20 + 8 }, { viewX - 30 + 20, viewY + 16 }, RED);
	}
}
