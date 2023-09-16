/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Survivor.h"
#include "Handgun.h"
#include "Rifle.h"
#include "Shotgun.h"
#include <string>
#include <iostream>

#pragma region NAMESPACE
namespace
{
	X::Math::Vector2 GetCrosshairPosition()
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());

		return X::Math::Vector2(mouseX, mouseY);
	}
}
#pragma endregion


// use enums
// vector to store all 3 weapons to avoid memory leak
#pragma region LOAD
void Survivor::Load(int chosenWeapon)
{
	if(chosenWeapon == 1)
	{
		mCurrentWeapon = new Handgun();
		mCurrentWeapon->Load();
	}
	else if (chosenWeapon == 2)
	{
		mCurrentWeapon = new Rifle();
		mCurrentWeapon->Load();
	}
	else if (chosenWeapon == 3)
	{
		mCurrentWeapon = new Shotgun();
		mCurrentWeapon->Load();
	}
	
}
#pragma endregion

#pragma region UNLOAD
void Survivor::Unload()
{
	mCurrentWeapon->Unload();

	delete mCurrentWeapon;
	mCurrentWeapon = nullptr;
}
#pragma endregion

#pragma region UPDATE
void Survivor::Update(float deltaTime)
{
	// Movement
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		mPosition.x += mSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		mPosition.x -= mSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		mPosition.y -= mSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		mPosition.y += mSpeed * deltaTime;
	}

	// Firing
	mHeading = X::Math::Normalize(GetCrosshairPosition() - mPosition);

	if (X::IsMousePressed(X::Mouse::LBUTTON) && mCurrentWeapon->CanFire())
	{
		mCurrentWeapon->Fire(mPosition, mHeading);
	}

	// Reloading
	if (X::IsKeyPressed(X::Keys::R) || X::IsMousePressed(X::Mouse::RBUTTON))
	{
		mCurrentWeapon->Reload();
	}

	// Change Weapon
	if (X::IsKeyPressed(X::Keys::ONE))
	{
		Load(1);
	}
	else if (X::IsKeyPressed(X::Keys::TWO))
	{
		Load(2);
	}
	else if (X::IsKeyPressed(X::Keys::THREE))
	{
		Load(3);
	}

}
#pragma endregion

#pragma region RENDER
void Survivor::Render()
{
	// Draw survivor sprite
	const float angle = atan2(mHeading.y, mHeading.x);
	X::DrawSprite(mCurrentWeapon->GetSurvivorTextureId(), mPosition, angle);

	// Render weapon (bullet UI for example)
	mCurrentWeapon->Render();

	// Render crosshairs from mouse position
	const X::Math::Vector2 target = GetCrosshairPosition();
	X::DrawSprite(mCurrentWeapon->GetCrosshairTextureId(), target);

}
#pragma endregion

// Dealed damage
// Draw the screen text in Render
#pragma region HEALTH
void Survivor::Health(float pDamage)
{
	std::string totalHealth = std::to_string(mHP - pDamage);
	mHP = std::stof(totalHealth);

	// Move this to Render
	X::DrawScreenText(totalHealth.c_str(), X::GetScreenWidth() * 0.6, X::GetScreenHeight() * 0.05, 20.0f, X::Colors::White);

}
#pragma endregion

#pragma region SCORE
void Survivor::Score()
{

}
#pragma endregion