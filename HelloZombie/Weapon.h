/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Weapon
{

public:
	// Standard Object Functions
	// This makes the class Abstract
	// Virtual because we are intended to override the function
	// Abstract because we have to override them
	virtual void Load() = 0; // "= 0" This makes the class Abstract
	virtual void Unload() = 0;

	virtual void Render() = 0;

	// Weapon Specific Functions
	virtual void Fire(const X::Math::Vector2& position, const X::Math::Vector2& direction) = 0;
	virtual bool CanFire() = 0;
	virtual void Reload() = 0;

	// Getters and Setters
	X::TextureId GetSurvivorTextureId() const { return mSurvivorTextureId; }
	X::TextureId GetCrosshairTextureId() const { return mCrosshairTextureId; }

protected:
	X::TextureId mSurvivorTextureId = 0;
	X::TextureId mCrosshairTextureId = 0;
	X::TextureId mAmmoTextureId = 0;

	// This is for save the amount of bullets the player will have
	//X::TextureId mAmmoCountID[];

	X::Math::Vector2 mAmmoCountPosition = 0;

	X::SoundId mFireSoundId = 0;

	int mAmmoCount = 0;

	float mAmmoWidth = 0;
	float mAmmoHeight = 0;

};

