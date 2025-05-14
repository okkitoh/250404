#pragma once

#include <iostream>
#include "Animation.h"

typedef struct AnimationHandle
{
	int id;
	Animation* reference;

	void Interrupt();
	void SwapSprite(SpriteID spritekey);
	void SwapSprite(SpriteID spritekey, bool bLooping);
	void Unregister();
} AnimationHandle;