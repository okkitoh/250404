
#include "AnimationHandle.h"


void AnimationHandle::Interrupt()
{
	if (reference != nullptr)
	{
		reference->SetActive(false);

	}
}

void AnimationHandle::SwapSprite(SpriteID spritekey)
{
	if (reference != nullptr)
	{
		reference->SetSprite(spritekey);
		reference->SetFramePosition(0);
	}

}
void AnimationHandle::SwapSprite(SpriteID spritekey, bool bLooping)
{
	if (reference != nullptr)
	{
		reference->SetSprite(spritekey);
		reference->SetFramePosition(0);
		reference->SetLooping(bLooping);
	}
}
void AnimationHandle::Unregister()
{
	if (reference != nullptr)
	{
		reference->Invalidate();
	}
}