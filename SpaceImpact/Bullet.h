/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Bullet
{
public:

	void Load();
	void Unload();

	void Render();
	void Update(float deltaTime);

	X::Math::Circle GetBoundingCircle() const { return { mBulletPosition, 30.0f }; }
	
	void Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity);
	void Destroy() { mIsActive = false; }

	bool IsActive() const { return mIsActive; }

private:

	X::TextureId mBulletTextureId;

	X::Math::Vector2 mBulletPosition;
	X::Math::Vector2 mBulletVelocity;

	bool mIsActive = false;

	float screenWidth = 0;

};