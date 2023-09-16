/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Bullet.h"
#include "EnemyManager.h"

#pragma region NAMESPACE
namespace
{
	
}
#pragma endregion

#pragma region LOAD
void Bullet::Load()
{
	mBulletTextureId = X::LoadTexture("spaceship_bullet.png");

	screenWidth = X::GetScreenWidth();
}
#pragma endregion

#pragma region UNLOAD
void Bullet::Unload()
{

}
#pragma endregion

#pragma region RENDER
void Bullet::Render()
{
	if (IsActive() == false)
	{
		return;
	}

	X::DrawSprite(mBulletTextureId, mBulletPosition);
}
#pragma endregion

#pragma region UPDATE
void Bullet::Update(float deltaTime)
{
	if (IsActive())
	{
		mBulletPosition += mBulletVelocity * deltaTime;
		EnemyManager::Get().CheckCollisionBullet(25, *this);
		if (mBulletPosition.x > screenWidth)
		{
			Destroy();
		}
	}
}
#pragma endregion

#pragma region FIRE
void Bullet::Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mBulletPosition = position;
	mBulletVelocity = velocity;

	mIsActive = true;
}
#pragma endregion