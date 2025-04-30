#pragma once

#include "View.h"
#include "Sprites.h"
#include "raylib.h"

// 2DAnimation System Design
// --------------------------
// Has position vec2
// Has dimension width, height
// Adjustable Frames per second
//   - Needs to keep track of "duration "
// Reuse view so animation has ability to "self-delete" at end of duration popping itself off the animation stack
//
// What if animation doesn't span the full sheet? interesting problem 
// 
// sheet.column    Must be number of divisions in the whole sheet width
// sheet.rows      Must be number of divisions in the whole sheet height
// sheet.keyframes Number of keyframes
class Animation : public View
{
public:
	Animation(SpriteID key, Vector2 position, int framesPerSecond, bool isLooping);
	void Update();
	void Draw();
	void GuiDraw();
private:
	Sprite sheet;
	Vector2 position; // screen space
	int framesPerSecond;
	bool isLooping;

	Vector2 dimensions;
	int keyframes;
	int frameCounter;
	int framePosition;
};
