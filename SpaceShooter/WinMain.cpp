#include <XEngine.h>

X::Math::Vector2 position;
X::TextureId textureId;

void GameInit()
{
	textureId = X::LoadTexture("mario.png");
	position.x = X::GetScreenWidth() * 0.5f;
	position.y = X::GetScreenHeight() * 0.5f;
}

bool GameLoop(float deltaTime)
{
	const float speed = 100.0f;
	//if (X::IsKeyDown(X::Keys::W))
	//	position.y -= speed * deltaTime;
	//if (X::IsKeyDown(X::Keys::S))
	//	position.y += speed * deltaTime;
	//if (X::IsKeyDown(X::Keys::A))
	//	position.x -= speed * deltaTime;
	//if (X::IsKeyDown(X::Keys::D))
	//	position.x += speed * deltaTime;
	const float rotation = X::Math::kDegToRad * 270.0f;
	const X::Math::Vector2 direction = X::Math::Vector2::Forward(rotation);
	position += (direction * speed * deltaTime);

	X::DrawSprite(textureId, position, 0.0f, X::Pivot::Center);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}