/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class BulletManager
{
public:

	static void StaticInitialize();
	static void StaticTerminate();
	static BulletManager& Get();

	void Load();
	void Unload();

	void Render();
	void Update(float deltaTime);

	void SetBullet(const X::Math::Vector2& position, const X::Math::Vector2& velocity);

private:

	int mCurrentBulletsIndex = 0;
};

