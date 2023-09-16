/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "BulletManager.h"
#include "Bullet.h"

#pragma region NAMESPACE
namespace
{
	int const maxBullets = 25;

	Bullet bullets[maxBullets];

	BulletManager* sInstance = nullptr;
}
#pragma endregion

#pragma region STATIC INITIALIZE
void BulletManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "TileMap already initialized! There should only be one!");
	sInstance = new BulletManager();
}
#pragma endregion

#pragma region STATIC TERMINATE
void BulletManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
#pragma endregion

#pragma region GET
BulletManager& BulletManager::Get()
{
	XASSERT(sInstance != nullptr, "TileMap not initialized yet! Call StaticInitialize() first!");
	return *sInstance;
}
#pragma endregion

#pragma region LOAD
void BulletManager::Load()
{
	mCurrentBulletsIndex = 0;

	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Load();
	}
}
#pragma endregion

#pragma region UNLOAD
void BulletManager::Unload()
{
	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Unload();
	}
}
#pragma endregion

#pragma region UPDATE
void BulletManager::Update(float deltaTime)
{
	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Update(deltaTime);
	}
}
#pragma endregion

#pragma region RENDER
void BulletManager::Render()
{
	for (int i = 0; i < maxBullets; ++i)
	{
		bullets[i].Render();
	}
}
#pragma endregion

#pragma region SET BULLET
void BulletManager::SetBullet(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	const int index = mCurrentBulletsIndex;

	if (bullets[index].IsActive() == false)
	{
		bullets[index].Fire(position, velocity);

		// Increment index
		mCurrentBulletsIndex += 1;

		if(mCurrentBulletsIndex == maxBullets)
		{ 
			mCurrentBulletsIndex = 0;
		}
	}
}
#pragma endregion
