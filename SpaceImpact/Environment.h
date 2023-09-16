/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Environment
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ResetClouds();
	void ResetBuildings();

private:

	X::TextureId mBackgroundTexture;

	X::TextureId mClouds01TextureId;
	X::TextureId mClouds02TextureId;
	X::TextureId mClouds03TextureId;
	X::TextureId mClouds04TextureId;
	
	X::TextureId mBuildings01TextureId;
	X::TextureId mBuildings02TextureId;
	X::TextureId mBuildings03TextureId;
	X::TextureId mBuildings04TextureId;
	
	X::Math::Vector2 mBackgroundPosition;
	
	X::Math::Vector2 mClouds01Position;
	X::Math::Vector2 mClouds02Position;
	X::Math::Vector2 mClouds03Position;
	X::Math::Vector2 mClouds04Position;

	X::Math::Vector2 mBuildings01Position;
	X::Math::Vector2 mBuildings02Position;
	X::Math::Vector2 mBuildings03Position;
	X::Math::Vector2 mBuildings04Position;

	float mCloudSpeed = 125.0f;
	float mBuildingsSpeed = 100.0f;

	float mScreenWidth = 0.0f;
	float mScreenHeight = 0.0f;
};

