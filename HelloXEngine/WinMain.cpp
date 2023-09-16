/*
* Student Name: Jaime Escobar Sanchez
* Student ID: 1940022
* Subject: 2D Games programming - VGP230
*/

#include <XEngine.h>

#pragma region GLOBALS
// ======= TEXTURE =======
X::TextureId marioTextureId = 0;

X::TextureId mushroomTextureId = 0;

X::TextureId qMarkTextureId = 0;

// ======= POSITION =======
X::Math::Vector2 marioPosition;

X::Math::Vector2 mushroomPosition;

X::Math::Vector2 qMarkPosition;

// ======= MOVE SPEED =======
float marioMoveSpeed = 0.0f;

float mushroomMoveSpeed = 0.0f;

float qMarkMoveSpeed = 0.0f;

// ======= SPRITE HEIGHT / SPRITE WIDTH =======
// 'HS' stands for Half Sprite
float marioHSWidth = 0.0f;
float marioHSHeight = 0.0f;

float mushroomHSWidth = 0.0f;
float mushroomHSHeight = 0.0f;

float qMarkHSWidth = 0.0f;
float qMarkHSHeight = 0.0f;

// ======= SCREEN WIDTH / SCREEN HEIGHT =======
int screenWidth = 0;
int screenHeight = 0;

#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	// ======= Initialize game =======

	// Get Screen Width and Height
	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();

	// Load a texture - this uses the correct file path already from the asstes folder
	marioTextureId = X::LoadTexture("mario.png");

	mushroomTextureId = X::LoadTexture("mushroom.png");

	qMarkTextureId = X::LoadTexture("qmark.png");

	// Init starting values
	// Init positions
	marioPosition = { 300.0f, 400.0f };

	mushroomPosition = { 300.0f, 100.0f };

	qMarkPosition = { 600.0f, 100.0f };

	// Init Speed
	marioMoveSpeed = 500.0f;

	mushroomMoveSpeed = 250.0f;

	qMarkMoveSpeed = 200.0f;

	// Get Half Width & Height from the sprites
	marioHSWidth = static_cast<float>(X::GetSpriteWidth(marioTextureId)) * 0.5f;
	marioHSHeight = static_cast<float>(X::GetSpriteHeight(marioTextureId)) * 0.5f;

	mushroomHSWidth = static_cast<float>(X::GetSpriteWidth(mushroomTextureId)) * 0.5f;
	mushroomHSHeight= static_cast<float>(X::GetSpriteHeight(mushroomTextureId)) * 0.5f;

	qMarkHSWidth = static_cast<float>(X::GetSpriteWidth(qMarkTextureId)) * 0.5f;
	qMarkHSHeight = static_cast<float>(X::GetSpriteHeight(qMarkTextureId)) * 0.5f;

}
#pragma endregion

#pragma region MOVE MARIO
void MoveMario(float deltaTime) 
{
	//Move Mario
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		// deltaTime is the change of time on each frame
		marioPosition.x += marioMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		marioPosition.x -= marioMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		marioPosition.y -= marioMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		marioPosition.y += marioMoveSpeed * deltaTime;
	}
}
#pragma endregion

#pragma region STOP OUT OF BOUNDS
void StopIfOutOfBounds(float deltaTime) 
{
	// Right boundary
	if (marioPosition.x > screenWidth - marioHSWidth)
	{
		marioPosition.x = screenWidth - marioHSWidth;
	}
	// Left boundary
	if (marioPosition.x < marioHSWidth)
	{
		marioPosition.x = marioHSWidth;
	}
	// Top boundary
	if (marioPosition.y < marioHSHeight)
	{
		marioPosition.y = marioHSHeight;
	}
	// Bottom boundary
	if (marioPosition.y > screenHeight - marioHSHeight) 
	{
		marioPosition.y = screenHeight - marioHSHeight;
	}
}
#pragma endregion

#pragma region MUSHROOM MOVEMENT
void MushroomMovement() 
{
	if (mushroomPosition.x > screenWidth - mushroomHSWidth)
	{
		mushroomMoveSpeed *= -1;
	}
	else if (mushroomPosition.x < mushroomHSWidth)
	{
		mushroomMoveSpeed *= -1;
	}
}
#pragma endregion

#pragma region QMARK MOVEMENT
void QMarkMovement() 
{
	if (qMarkPosition.x > screenWidth - qMarkHSWidth)
	{
		qMarkMoveSpeed *= -1;
	}
	else if (qMarkPosition.x < qMarkHSWidth)
	{
		qMarkMoveSpeed *= -1;
	}
}
#pragma endregion

#pragma region MOVE TEXTURES
void MoveTextures(float deltaTime)
{
	mushroomPosition.x += mushroomMoveSpeed * deltaTime;

	qMarkPosition.x += qMarkMoveSpeed * deltaTime;
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	// ======= RUN GAME =======

	// Render sprites on screen
	X::DrawSprite(marioTextureId, marioPosition);

	X::DrawSprite(mushroomTextureId, mushroomPosition);

	X::DrawSprite(qMarkTextureId, qMarkPosition);

	// Mario functions
	MoveMario(deltaTime);

	StopIfOutOfBounds(deltaTime);

	// HomeWork:
	// -> Make the texture move by itself and bounce off the border
	// Once it hits the border, it should reverse direction
	// -> Extra challenge: make two different textures do this at the same time!
	// -> Hint use: "X::Math::Vector2 velocity" and "position += velocity * deltaTime"

	// Mushroom Movement
	MushroomMovement();

	// QMark movement
	QMarkMovement();

	// Move Textures
	MoveTextures(deltaTime);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	// Cleanup game


}
#pragma endregion

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}
#pragma endregion