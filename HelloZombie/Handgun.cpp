/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Handgun.h"
#include "EnemyManager.h"

#pragma region NAMESPACE
// Only access by this class if inside the namespace
namespace
{
	constexpr int MAX_AMMO_COUNT = 8;

	// Set start position for bullets in X and Y
	static float AMMO_COUNT_X = 50.0f;
	static float AMMO_COUNT_Y = 50.0f;

}
#pragma endregion

#pragma region LOAD
void Handgun::Load()
{
	// Load Textures
	mSurvivorTextureId = X::LoadTexture("survivor_handgun.png");
	mAmmoTextureId = X::LoadTexture("bullet1.png");
	mCrosshairTextureId = X::LoadTexture("crosshair_handgun.png");

	// Load Sounds
	mFireSoundId = X::LoadSound("photongun1.wav");

	mAmmoWidth = static_cast<float>(X::GetSpriteWidth(mAmmoTextureId));
	//mAmmoHeight = static_cast<float>(X::GetSpriteHeight(mAmmoTextureId));

	Reload();

	Render();

}
#pragma endregion

#pragma region UNDLOAD
void Handgun::Unload()
{


}
#pragma endregion

#pragma region RENDER
void Handgun::Render()
{

	for (int i = 0; i < mAmmoCount; ++i)
	{
		// Set the position for each "bullet"
		// Get ammoWidth so there can be the same space between each bullet, and multiplying it by the value of i + 1
		// in order to 
		mAmmoCountPosition = {AMMO_COUNT_X + (mAmmoWidth * i+1), AMMO_COUNT_Y };

		// We draw each available bullet
		X::DrawSprite(mAmmoTextureId, mAmmoCountPosition);
	}

}
#pragma endregion

#pragma region FIRE
void Handgun::Fire(const X::Math::Vector2& position, const X::Math::Vector2& direction)
{
	// DrawScreenLine(from, to, color)
	// We need to create a "from" vector and "to" vector
	const X::Math::Vector2 from = position + (direction * 50.0f);
	const X::Math::Vector2 to = position + (direction * 500.0f);

	X::DrawScreenLine(from, to, X::Colors::Red);

	// AS we fired a bullet, we need to decrement
	// Reduce ammo count by one
	--mAmmoCount;

	// Create a line segment from these two vectors to be used for collision with enemies
	const X::Math::LineSegment line(from, to);
	EnemyManager::Get().CheckCollision(line, 25);

	// Sound
	X::PlaySoundOneShot(mFireSoundId);

}
#pragma endregion

#pragma region CAN FIRE
bool Handgun::CanFire()
{
	return mAmmoCount > 0;
}
#pragma endregion

#pragma region RELOAD
void Handgun::Reload()
{
	mAmmoCount = MAX_AMMO_COUNT;
}
#pragma endregion