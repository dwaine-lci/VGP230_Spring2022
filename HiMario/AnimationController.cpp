#include "AnimationController.h"

AnimationController::AnimationController()
	: _activeAnimationId(-1)
	, _isPlaying(false)
{

}
AnimationController::~AnimationController()
{

}

void AnimationController::AddAnimation(int animationId, Animation& animation)
{
	_animations[animationId] = animation;
}
void AnimationController::Update(float deltaTime)
{
	if (_isPlaying)
	{
		_animations[_activeAnimationId].Update(deltaTime);
	}
}
const X::TextureId& AnimationController::GetCurrentAnimationTexture()
{
	return _animations[_activeAnimationId].GetCurrentFrameTexture();
}
void AnimationController::PlayAnimation(int animationId, int startingIndex)
{
	_isPlaying = true;
	_activeAnimationId = animationId;
	_animations[_activeAnimationId].Play(startingIndex);
}
void AnimationController::Stop()
{
	for (auto anim : _animations)
	{
		anim.second.Stop();
	}
	_activeAnimationId = 0;
	_isPlaying = false;
}