
#include "Animation.h"
#include "DGDef.h"
#include "rlgl.h"

Animation::Animation(SpriteID key, Vector2 position, bool isLooping) : View()
{
	sheet = Sprites::GetSprite(key);
	this->spriteid = key;
	this->position = position;
	this->isLooping = isLooping;
	this->playspeed = 1.f;
	
	dimensions.x = static_cast<float>(sheet.tex.width) / static_cast<float>(sheet.columns);
	dimensions.y = static_cast<float>(sheet.tex.height) / static_cast<float>(sheet.rows);
	frameCounter = 0;
	framePosition = 0;
}
void Animation::SetSprite(SpriteID key)
{
	if (this->spriteid != key)
	{
		this->spriteid = key;
		sheet = Sprites::GetSprite(key);
	}
}
void Animation::SetLooping(bool bLooping)
{
	this->isLooping = bLooping;
}
void Animation::SetPlayspeed(float playspeed)
{
	this->playspeed = playspeed;
}
void Animation::SetFramePosition(int framePosition)
{
	framePosition = framePosition % sheet.keyframes;
}
void Animation::Update()
{

}
void Animation::Draw()
{
	if (IsActive())
	{
		if ((frameCounter * playspeed) >= TARGET_FPS / sheet.frameRate)
		{
			frameCounter = 0;
			if (framePosition < sheet.keyframes - 1 || isLooping)
			{
				framePosition = ++framePosition % sheet.keyframes;
			}

		}
		frameCounter++;
		/*
		typedef struct Rectangle {
			float x;                // Rectangle top-left corner position x
			float y;                // Rectangle top-left corner position y
			float width;            // Rectangle width
			float height;           // Rectangle height
		} Rectangle;
		*/
		int x = (framePosition % sheet.columns) * static_cast<int>(dimensions.x);
		int y = framePosition / sheet.columns * static_cast<int>(dimensions.y);
		Rectangle source = {
			x,
			y,
			dimensions.x,
			dimensions.y
		};
		Rectangle display = {
			position.x - dimensions.x,
			position.y - dimensions.y,
			dimensions.x,
			dimensions.y
		};
		Vector2 origin = {
			0,
			0
		};
		DrawTexturePro(sheet.tex, source, display, origin, 0.f, WHITE);
	}
}
void Animation::GuiDraw()
{

}
