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
//
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
	int frameCounter;
	int framePosition;
};
