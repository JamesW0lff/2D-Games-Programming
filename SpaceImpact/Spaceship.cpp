/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Spaceship.h"
#include "BulletManager.h"
#include "EnemyManager.h"

#pragma region NAMESPACE
namespace
{
	static float LIFE_POSITION_X = 50.0f;
	static float LIFE_POSITION_Y = 50.0f;
}
#pragma endregion

#pragma region LOAD
void Spaceship::Load()
{
	mSpaceshipTextureId = X::LoadTexture("spaceship.png");
	mSpaceshipLifeTextureId = X::LoadTexture("spaceship_life_icon.png");

	mNewLifeSoundId = X::LoadSound("8bit_new_life.wav");
	mLoseLifeSoundId = X::LoadSound("8bit_lose_life.wav");
	mShootSoundId = X::LoadSound("8bit_shoot.wav");

	mMoveSpeed = 250.0f;
	mSpaceshipLifes = 3;

	mSpaceshipWidthHS = X::GetSpriteWidth(mSpaceshipTextureId) * 0.5f;
	mSpaceshipHeightHS = X::GetSpriteHeight(mSpaceshipTextureId) * 0.5f;

	mSpaceshipLifeWidth = X::GetSpriteWidth(mSpaceshipLifeTextureId);
	mSpaceshipLifeHeight = X::GetSpriteHeight(mSpaceshipLifeTextureId);

	// Get half of the screen width as I do not want the player to go above it
	screenWidthHS = X::GetScreenWidth() * 0.5f;
	screenHeight = X::GetScreenHeight();
}
#pragma endregion

#pragma region RENDER
void Spaceship::Render()
{
	// Render spaceship on screen
	X::DrawSprite(mSpaceshipTextureId, mSpaceshipPosition);
}
#pragma endregion

#pragma region RENDER LIFE
void Spaceship::RenderLife()
{
	for (int i = 0; i < mSpaceshipLifes; ++i)
	{
		X::DrawSprite(mSpaceshipLifeTextureId, { (LIFE_POSITION_X + (mSpaceshipLifeWidth * i + 1)), LIFE_POSITION_Y });
	}
}
#pragma endregion

#pragma region UNLOAD
void Spaceship::Unload()
{

}
#pragma endregion

#pragma region UPDATE
void Spaceship::Update(float deltaTime)
{
	SpaceshipMovement(deltaTime);

	// ======= FIRE =======
	if (X::IsKeyPressed(X::Keys::SPACE)/*X::IsMousePressed(X::Mouse::LBUTTON)*/)
	{
		Fire();
	}

	// ======= STOP OUT OF BOUNDS
	StopOutOfBounds(deltaTime);
}
#pragma endregion

#pragma region SPACESHIP MOVEMENT
void Spaceship::SpaceshipMovement(float deltaTime)
{
	// ======= MOVEMENT: RIGHT =======
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		mSpaceshipPosition.x += mMoveSpeed * deltaTime;
	}
	// ======= MOVEMENT: LEFT =======
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		mSpaceshipPosition.x -= mMoveSpeed * deltaTime;
	}
	// ======= MOVEMENT: UP =======
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		mSpaceshipPosition.y -= mMoveSpeed * deltaTime;
	}
	// ======= MOVEMENT: DOWN =======
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		mSpaceshipPosition.y += mMoveSpeed * deltaTime;
	}
}
#pragma endregion

#pragma region STOP OUT OF BOUNDS
void Spaceship::StopOutOfBounds(float deltaTime)
{
	// ======= RIGHT BOUNDARY =======
	if (mSpaceshipPosition.x > screenWidthHS - mSpaceshipWidthHS)
	{
		mSpaceshipPosition.x = screenWidthHS - mSpaceshipWidthHS;
	}
	// ======= LEFT BOUNDARY =======
	if (mSpaceshipPosition.x < mSpaceshipWidthHS)
	{
		mSpaceshipPosition.x = mSpaceshipWidthHS;
	}
	// ======= TOP BOUNDARY =======
	if (mSpaceshipPosition.y < mSpaceshipHeightHS + mSpaceshipLifeHeight)
	{
		mSpaceshipPosition.y = mSpaceshipHeightHS + mSpaceshipLifeHeight;
	}
	// ======= BOTTOM BOUNDARY =======
	if (mSpaceshipPosition.y > screenHeight - mSpaceshipHeightHS)
	{
		mSpaceshipPosition.y = screenHeight - mSpaceshipHeightHS;
	}
}
#pragma endregion

#pragma region FIRE
void Spaceship::Fire()
{
	X::PlaySoundOneShot(mShootSoundId);
	// Move the bullet horizontally
	X::Math::Vector2 velocity(400.0f, 0.0f);
	// Start point is the spaceship's position
	X::Math::Vector2 position = GetPosition();

	BulletManager::Get().SetBullet(position, velocity);
}
#pragma endregion

#pragma region INCREASE LIFE
void Spaceship::IncreaseLife()
{
	if ((mSpaceshipLifes < 10))
	{
		X::PlaySoundOneShot(mNewLifeSoundId);
		++mSpaceshipLifes;
	}
}
#pragma endregion

#pragma region RECEIVE DAMAGE
void Spaceship::ReceiveDamage()
{
	if (mSpaceshipLifes >= 0)
	{
		X::PlaySoundOneShot(mLoseLifeSoundId);
		mSpaceshipLifes--;
	}
}
#pragma endregion

#pragma region OUT OF LIVES
bool Spaceship::OutOfLives()
{
	if(mSpaceshipLifes < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion