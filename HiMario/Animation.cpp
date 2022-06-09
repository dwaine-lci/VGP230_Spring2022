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
	_useSpriteSheet = false;
}
void Animation::Init(float fps, float frameWidth, float frameHeight, int rows, int cols, int frameCount)
{
	_frameRate = fps;
	_currentFrameTime = 0.0f;
	_frameIndex = 0;
	_frameCount = frameCount;
	_spriteSheetRowCount = rows;
	_spriteSheetColCount = cols;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
	_frameRect.min = X::Math::Vector2::Zero();
	_frameRect.max = X::Math::Vector2(_frameWidth, _frameHeight);
	_isPlaying = false;
	_useSpriteSheet = true;
}
void Animation::SetFrame(int frameIndex, X::TextureId textureId)
{
	while (_frames.size() <= frameIndex)
	{
		_frames.push_back(0);
	}

	_frames[frameIndex] = textureId;
	if (!_useSpriteSheet)
	{
		_frameRect.min = X::Math::Vector2::Zero();
		_frameRect.max = X::Math::Vector2(X::GetSpriteWidth(textureId), X::GetSpriteHeight(textureId));
	}
	_frameCount = X::Math::Max(_frameCount, (int)_frames.size());
}
void Animation::Update(float deltaTime)
{
	if (_isPlaying && _frameCount > 1)
	{
		_currentFrameTime += deltaTime;
		while (_currentFrameTime >= _frameRate)
		{
			_currentFrameTime -= _frameRate;
			_frameIndex = (_frameIndex + 1) % _frameCount;
			if (_useSpriteSheet)
			{
				int x = _frameIndex % _spriteSheetColCount;
				int y = _frameIndex / _spriteSheetColCount;
				X::Math::Vector2 rectOffset((float)x * _frameWidth, (float)y * _frameHeight);
				_frameRect.min = rectOffset;
				_frameRect.max = rectOffset + (X::Math::Vector2(_frameWidth, _frameHeight));
			}
		}
	}
}
const X::TextureId& Animation::GetCurrentFrameTexture()
{
	if (_useSpriteSheet)
	{
		return _frames[0];
	}
	return _frames[_frameIndex];
}
const X::Math::Rect& Animation::GetFrameRect()
{
	return _frameRect;
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