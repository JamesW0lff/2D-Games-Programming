/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Clouds.h"

#pragma region LOAD
void Clouds::Load()
{
	mCloudsTexture = X::LoadTexture("buildings_02.png");
}
#pragma endregion

#pragma region UNLOAD
void Clouds::Unload()
{

}
#pragma endregion

#pragma region UPDATE
void Clouds::Update(float deltaTime)
{
	mCloudPosition.x -= mCloudSpeed * deltaTime;
	if (mCloudPosition.x < -100.0f)
	{
		ResetCloudsPosition();
	}
}
#pragma endregion

#pragma region RENDER
void Clouds::Render()
{
	// Render spaceship on screen
	X::DrawSprite(mCloudsTexture, mCloudPosition);
}
#pragma endregion

#pragma region RESET CLOUDS POSITION
void Clouds::ResetCloudsPosition()
{
	SetPosition({ 1200, 360 });
}
#pragma endregion