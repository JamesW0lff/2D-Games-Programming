/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Enemy
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	const X::Math::Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }

	X::Math::Circle GetBoundingCircle() const { return { mPosition, 30.0f }; }

	void Hurt(float damage) { mHP -= damage; }
	bool IsAlive() const { return mHP > 0.0f; }

protected:
	X::TextureId mAliveTexture;
	X::TextureId mDeadTexture;

	X::Math::Vector2 mPosition;
	X::Math::Vector2 mHeading;

	float mSpeed = 100.0f;// 300.0f;
	float mHP = 0.0f;

};