#pragma once

#include "View.h"
#include "Sprites.h"
#include "raylib.h"

// 2DAnimation System Design
// --------------------------
// 
// sheet.column    Must be number of divisions in the whole sheet width
// sheet.rows      Must be number of divisions in the whole sheet height
// sheet.keyframes Number of keyframes
class Animation : public View
{
public:
	Animation(SpriteID key, Vector2 position, bool isLooping);
	void SetSprite(SpriteID key);
	void SetLooping(bool bLooping);
	void SetFlip(bool isFlip);
	void SetPlayspeed(float playspeed);
	void SetFramePosition(int framePosition);
	void Update();
	void Draw();
	void GuiDraw();
private:
	SpriteID spriteid;
	Sprite sheet;
	Vector2 position; // screen space
	bool isLooping;
	bool isFlip;

	Vector2 dimensions;
	int frameCounter;
	int framePosition;
	float playspeed;
};
