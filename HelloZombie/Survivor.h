/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

// Reference to a weapon
class Weapon;

// Player character
class Survivor
{

public:

	// Standard Object Functions
	void Load(int chosenWeapon);
	void Unload();

	void Update(float deltaTime);
	void Render();
	
	void Health(float pDamage);
	void Score();
	// void CheckCollision(const Math::);

	// Getters and Setters
	// the return type is a const ref, so we don't create a copy 
	// const on the right we are saying that anything happens should not change within the class
	// When you don't want anything the code to change; Any time I am reading or printing, there should be a const on the right
	const X::Math::Vector2& GetPosition() const { return mPosition; }
	X::Math::Circle GetBoundingCircle() const { return { mPosition, 30.0f }; }
	void SetPosition(const::X::Math::Vector2& position) { mPosition = position; }


private:

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mHeading;

	Weapon* mCurrentWeapon = nullptr;

	const float mSpeed = 300.0f;

	float mHP = 100.0f;

};

