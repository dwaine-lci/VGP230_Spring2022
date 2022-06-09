#pragma once
#include "Animation.h"
#include <map>

class AnimationController
{
public:
	AnimationController();
	virtual ~AnimationController();

	void AddAnimation(int animationId, Animation& animation);
	void Update(float deltaTime);
	const X::TextureId& GetCurrentAnimationTexture();
	void PlayAnimation(int animationId, int startingIndex = 0);
	void Stop();
private:
	bool _isPlaying;
	int _activeAnimationId;
	std::map<int, Animation> _animations;
};