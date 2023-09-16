/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Environment.h"

#include <stdlib.h>
#include <time.h>

#pragma region LOAD
void Environment::Load()
{
	srand(time(NULL));

	mBackgroundTexture = X::LoadTexture("blue_bg.png");
	
	mClouds01TextureId = X::LoadTexture("clouds_04.png");
	mClouds02TextureId = X::LoadTexture("clouds_05.png");
	mClouds03TextureId = X::LoadTexture("clouds_04.png");
	mClouds04TextureId = X::LoadTexture("clouds_05.png");

	mBuildings01TextureId = X::LoadTexture("buildings_01.png");
	mBuildings02TextureId = X::LoadTexture("buildings_03.png");
	mBuildings03TextureId = X::LoadTexture("buildings_05.png");
	mBuildings04TextureId = X::LoadTexture("buildings_07.png");

	mScreenWidth = static_cast<float>(X::GetScreenWidth());
	mScreenHeight = static_cast<float>(X::GetScreenHeight());

	mBackgroundPosition = { mScreenWidth * 0.5f, mScreenHeight * 0.5f };

	mClouds01Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds01TextureId)), 200.0f };
	mClouds02Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds02TextureId)) * 2.0f, 250.0f };
	mClouds03Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds03TextureId)) * 2.5f, 300.0f };
	mClouds04Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds04TextureId)) * 1.5f, 350.0f };

	mBuildings01Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings01TextureId)), 
								static_cast<float>(X::GetSpriteHeight(mBuildings01TextureId)) * 1.75f };

	mBuildings02Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings02TextureId)),
								static_cast<float>(X::GetSpriteHeight(mBuildings02TextureId)) * 2.45f };

	mBuildings03Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings03TextureId)) ,
								static_cast<float>(X::GetSpriteHeight(mBuildings03TextureId)) * 2.45f};

	mBuildings04Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings04TextureId)) ,
									static_cast<float>(X::GetSpriteHeight(mBuildings04TextureId)) * 1.25f };
}
#pragma endregion

#pragma region UNLOAD
void Environment::Unload()
{

}
#pragma endregion

#pragma region UPDATE
void Environment::Update(float deltaTime)
{
	mClouds01Position.x -= mCloudSpeed * deltaTime;
	mClouds02Position.x -= mCloudSpeed * deltaTime;
	mClouds03Position.x -= mCloudSpeed * deltaTime;
	mClouds04Position.x -= mCloudSpeed * deltaTime;

	mBuildings01Position.x -= mBuildingsSpeed * deltaTime;
	mBuildings02Position.x -= mBuildingsSpeed * deltaTime;
	mBuildings03Position.x -= mBuildingsSpeed * deltaTime;
	mBuildings04Position.x -= mBuildingsSpeed * deltaTime;

	ResetClouds();
	ResetBuildings();
}
#pragma endregion

#pragma region RENDER
void Environment::Render()
{
	X::DrawSprite(mBackgroundTexture, mBackgroundPosition);

	X::DrawSprite(mBuildings01TextureId, mBuildings01Position);
	X::DrawSprite(mBuildings02TextureId, mBuildings02Position);
	X::DrawSprite(mBuildings03TextureId, mBuildings03Position);
	X::DrawSprite(mBuildings04TextureId, mBuildings04Position);
	
	X::DrawSprite(mClouds01TextureId, mClouds01Position);
	X::DrawSprite(mClouds02TextureId, mClouds02Position);
	X::DrawSprite(mClouds03TextureId, mClouds03Position);
	X::DrawSprite(mClouds04TextureId, mClouds04Position);
}
#pragma endregion

#pragma region RESET CLOUDS
void Environment::ResetClouds()
{
	float mXPosition = static_cast<float>(rand() % 3 + 1);
	float mYPosition = static_cast<float>(rand() % 151 + 200);

	if (mClouds01Position.x < (0.0f - X::GetSpriteWidth(mClouds01TextureId)))
	{
		mClouds01Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds01TextureId)) * mXPosition, 
								mYPosition };
	}

	if (mClouds02Position.x < (0.0f - X::GetSpriteWidth(mClouds02TextureId)))
	{
		mClouds02Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds02TextureId)) * mXPosition,
								mYPosition };
	}

	if (mClouds03Position.x < (0.0f - X::GetSpriteWidth(mClouds03TextureId)))
	{
		mClouds03Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds03TextureId)) * mXPosition,
								mYPosition };
	}

	if (mClouds04Position.x < (0.0f - X::GetSpriteWidth(mClouds04TextureId)))
	{
		mClouds04Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mClouds04TextureId)) * mXPosition,
								mYPosition };
	}
}
#pragma endregion

#pragma region RESET BUILDINGS
void Environment::ResetBuildings()
{
	if (mBuildings01Position.x < (0.0f - X::GetSpriteWidth(mBuildings01TextureId)))
	{
		mBuildings01Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings01TextureId)),
									static_cast<float>(X::GetSpriteHeight(mBuildings01TextureId)) * 1.75f };
	}

	if (mBuildings02Position.x < (0.0f - X::GetSpriteWidth(mBuildings02TextureId)))
	{
		mBuildings02Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings02TextureId)),
									static_cast<float>(X::GetSpriteHeight(mBuildings02TextureId)) * 2.45f };
	}

	if (mBuildings03Position.x < (0.0f - X::GetSpriteWidth(mBuildings03TextureId)))
	{
		mBuildings03Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings03TextureId)) ,
									static_cast<float>(X::GetSpriteHeight(mBuildings03TextureId)) * 2.45f };
	}

	if (mBuildings04Position.x < (0.0f - X::GetSpriteWidth(mBuildings04TextureId)))
	{
		mBuildings04Position = { mScreenWidth + static_cast<float>(X::GetSpriteWidth(mBuildings04TextureId)) ,
									static_cast<float>(X::GetSpriteHeight(mBuildings04TextureId)) * 1.25f };
	}
}
#pragma endregion