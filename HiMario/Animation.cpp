#include "Animation.h"

Animation::Animation()
{

}
Animation::~Animation()
{

}

void Animation::Init(float fps)
{
	_frameRate = fps;
	_currentFrameTime = 0.0f;
	_frameIndex = 0;
	_isPlaying = false;
}
void Animation::SetFrame(int frameIndex, X::TextureId textureId)
{
	while (_frames.size() <= frameIndex)
	{
		_frames.push_back(0);
	}

	_frames[frameIndex] = textureId;
}
void Animation::Update(float deltaTime)
{
	if (_isPlaying && _frames.size() > 1)
	{
		_currentFrameTime += deltaTime;
		while (_currentFrameTime >= _frameRate)
		{
			_currentFrameTime -= _frameRate;
			_frameIndex = (_frameIndex + 1) % (int)_frames.size();
		}
	}
}
const X::TextureId& Animation::GetCurrentFrameTexture()
{
	return _frames[_frameIndex];
}
void Animation::Play(int startingIndex)
{
	_isPlaying = true;
	_currentFrameTime = 0.0f;
	_frameIndex = startingIndex;
}
void Animation::Stop()
{
	_isPlaying = false;
}