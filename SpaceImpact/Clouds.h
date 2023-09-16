/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Clouds
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& position) { mCloudPosition = position; }
	void ResetCloudsPosition();

private:

	X::TextureId mCloudsTexture;

	X::Math::Vector2 mCloudPosition;

	float mCloudSpeed = 100.0f;
};

