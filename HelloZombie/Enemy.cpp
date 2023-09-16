#include "Enemy.h"
#include "Survivor.h"

// Signifies external linkage to the "survivor " variable
// in the global namespace (defined in WinMain.cpp)
extern Survivor survivor;

#pragma region LOAD
void Enemy::Load()
{
	mAliveTexture = X::LoadTexture("zombie_idle.png");
	mDeadTexture = X::LoadTexture("zombie_dead.png");

	mHP = 100.0f;

}
#pragma endregion

#pragma region UNLOAD
void Enemy::Unload()
{

}
#pragma endregion

#pragma region UPDATE
void Enemy::Update(float deltaTime)
{
	if (IsAlive())
	{
		const X::Math::Vector2 target = survivor.GetPosition();
		mHeading = X::Math::Normalize(target - mPosition);
		mPosition += mHeading * mSpeed * deltaTime;
	}
}
#pragma endregion

#pragma region RENDER
void Enemy::Render()
{
	const float angle = atan2(mHeading.y, mHeading.x);

	const X::TextureId currentTextureId = IsAlive() ? mAliveTexture : mDeadTexture;

	X::DrawSprite(currentTextureId, mPosition, angle);

	// one line 
	// X::DrawSprite(IsAlive() ? mAliveTexture : mDeadTexture, mPosition, angle);
}
#pragma endregion