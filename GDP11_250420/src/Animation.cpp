
#include "Animation.h"
#include "DGDef.h"
#include "rlgl.h"

Animation::Animation(SpriteID key, Vector2 position, int framesPerSecond, bool isLooping) : View()
{
	sheet = Sprites::GetSprite(KNIGHT_IDLE);
	this->position = position;
	this->framesPerSecond = framesPerSecond;
	this->isLooping = isLooping;
	dimensions.x = static_cast<float>(sheet.tex.width) / static_cast<float>(sheet.columns);
	dimensions.y = static_cast<float>(sheet.tex.height) / static_cast<float>(sheet.rows);
	frameCounter = 0;
	framePosition = 0;
}
void Animation::Update()
{

}
void Animation::Draw()
{
	if (IsActive())
	{
		// `TARGET_FPS / framesPerSecond` resulting value is equivalent to "draw after X amount of frames"
		if (frameCounter >= TARGET_FPS / framesPerSecond)
		{
			frameCounter = 0;
			framePosition++;
			if (isLooping && framePosition < (sheet.columns * sheet.rows))
			{
				framePosition = ++framePosition % (sheet.columns * sheet.rows);
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
		int x = (framePosition % sheet.columns) * dimensions.x;
		int y = static_cast<int>(framePosition / sheet.rows) * dimensions.y;

		Rectangle source = {
			x,
			y,
			dimensions.x,
			dimensions.y
		};
		Rectangle display = {
			position.x,
			position.y,
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
