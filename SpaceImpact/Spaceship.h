/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Spaceship
{

public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();
	void RenderLife();

	void SetPosition(const::X::Math::Vector2& position) { mSpaceshipPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mSpaceshipPosition; }

	X::Math::Circle GetBoundingCircle() const { return { mSpaceshipPosition, 30.0f }; }

	void IncreaseLife();
	void ReceiveDamage();
	void Fire();

	void SpaceshipMovement(float deltaTime);
	void StopOutOfBounds(float deltaTime);

	bool OutOfLives();

private:

	X::TextureId mSpaceshipTextureId = 0;
	X::TextureId mSpaceshipLifeTextureId = 0;

	X::SoundId mNewLifeSoundId = 0;
	X::SoundId mLoseLifeSoundId = 0;
	X::SoundId mShootSoundId = 0;

	X::Math::Vector2 mSpaceshipPosition;

	bool mAddLife = false;

	int mSpaceshipLifes = 0;
	float mMoveSpeed = 0.0f;

	float mSpaceshipLifeWidth = 0.0f;
	float mSpaceshipLifeHeight = 0.0f;

	// HS = Half Size
	float mSpaceshipWidthHS = 0.0f;
	float mSpaceshipHeightHS = 0.0f;

	float screenWidthHS = 0;
	float screenHeight = 0;

};

