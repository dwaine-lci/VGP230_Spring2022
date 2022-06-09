#pragma once
#include "XEngine.h"
#include <vector>

class Animation
{
public:
	Animation();
	virtual ~Animation();

	void Init(float fps);
	void Init(float fps, float frameWidth, float frameHeight, int rows, int cols, int frameCount);
	void SetFrame(int frameIndex, X::TextureId textureId);
	void Update(float deltaTime);
	const X::TextureId& GetCurrentFrameTexture();
	const X::Math::Rect& GetFrameRect();

	void Play(int startingIndex = 0);
	void Stop();

private:
	std::vector<X::TextureId> _frames;
	X::Math::Rect _frameRect;
	float _frameWidth;
	float _frameHeight;
	int _frameCount;
	int _spriteSheetRowCount;
	int _spriteSheetColCount;
	int _frameIndex;
	float _frameRate;
	float _currentFrameTime;
	bool _isPlaying;
	bool _useSpriteSheet;
};