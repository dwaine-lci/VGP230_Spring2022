#pragma once
#include "XEngine.h"
#include <vector>

class Animation
{
public:
	Animation();
	virtual ~Animation();

	void Init(float fps);
	void SetFrame(int frameIndex, X::TextureId textureId);
	void Update(float deltaTime);
	const X::TextureId& GetCurrentFrameTexture();

	void Play(int startingIndex = 0);
	void Stop();

private:
	std::vector<X::TextureId> _frames;
	int _frameIndex;
	float _frameRate;
	float _currentFrameTime;
	bool _isPlaying;
};