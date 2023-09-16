/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "Enemy.h"

#pragma region NAMESPACE
namespace
{
	int wave01 = 10; // 10
	int wave02 = 30; // 25
	int wave03 = 60; // 45
}
#pragma endregion

#pragma region LOAD
void Enemy::Load()
{
	mEnemiesTextureId[0] = X::LoadTexture("spaceship_alien_01.png");
	mEnemiesTextureId[1] = X::LoadTexture("spaceship_alien_02.png");
	mEnemiesTextureId[2] = X::LoadTexture("spaceship_alien_03.png");
	mEnemyTextureId = mEnemiesTextureId[mEnemyIndex];
	mEnemyDefeatedSoundId = X::LoadSound("8bit_explosion.wav");
	mEnemyHP = 100.0f;
	mEnemySpeed = 100.0f;
	mEnemyHeight = X::GetSpriteHeight(mEnemyTextureId);
}
#pragma endregion

#pragma region UNLOAD
void Enemy::Unload()
{


}
#pragma endregion

#pragma region UPDATE
void Enemy::Update(float deltaTime)
{
	if (!IsAlive())
	{
		return;
	}
	
	mEnemyPosition.x -= mEnemySpeed * deltaTime;
	
	OutOfBounds(deltaTime);

}
#pragma endregion

#pragma region RENDER
void Enemy::Render()
{
	// Render spaceship on screen
	X::DrawSprite(mEnemyTextureId, mEnemyPosition);
}
#pragma endregion

#pragma region OUT OF BOUNDS
void Enemy::OutOfBounds(float deltaTime)
{
	// Reset position if enemy is out of bounds on 
	if(mEnemyPosition.x < (0.0f - X::GetSpriteWidth(mEnemyTextureId)))
	{
		mEnemyPosition.x = mResetEnemyPosition.x;
		mEnemyPosition.y = X::RandomFloat(96, X::GetScreenHeight() - GetEnemyHeight());
	}
}
#pragma endregion

#pragma region DESTROYED ENEMY SOUND
void Enemy::DestroyedEnemySound()
{
	X::PlaySoundOneShot(mEnemyDefeatedSoundId);
}
#pragma endregion

#pragma region NEXT WAVE
void Enemy::NextWave(int enemyCounter)
{
	// int sizeOfEnemyTextureArray = (int)(sizeof(mEnemiesTextureId) / sizeof(mEnemiesTextureId[0]));

#pragma region TEST 1: TIME
	/*
	if (mWaveTime < X::GetTime())
	{
		if (i < sizeOfEnemyTextureArray)
		{
			mEnemyTextureId = mEnemiesTextureId[i];
			mEnemyHP += 25.0f;
			mEnemySpeed = 5.0f;
			i++;
			if (i > sizeOfEnemyTextureArray)
			{
				i = 0;
			}
			// Reset spawn timer every 15 seconds
			mWaveTime = X::GetTime() + 15.0f;
		}
	}
	*/
#pragma endregion

#pragma region TEST 2: ENEMY COUNTER
	/*
	if (enemyCounter == 4)
	{
		if (mEnemyIndex < sizeOfEnemyTextureArray)
		{
			mEnemyIndex++;
			mEnemyTextureId = mEnemiesTextureId[mEnemyIndex];
			mEnemyHP += 25.0f;
			mEnemySpeed += 10.0f;
			if (mEnemyIndex == sizeOfEnemyTextureArray)
			{
				mEnemyIndex = 0;
			}
		}
		enemyCounter = 0;
	}
	*/
#pragma endregion

#pragma region TEST 3: LONG CODE
	if (enemyCounter <= wave01)
	{
		mEnemyTextureId = mEnemiesTextureId[0];
		mEnemyHP = 125.0f;
		mEnemySpeed = 275.0f;
	}
	else if(enemyCounter <= wave02)
	{
		mEnemyTextureId = mEnemiesTextureId[1];
		mEnemyHP = 150.0f;
		mEnemySpeed = 325.0f;
	}
	else if (enemyCounter <= wave03)
	{
		mEnemyTextureId = mEnemiesTextureId[2];
		mEnemyHP = 250.0f;
		mEnemySpeed = 375.0f;
	}
#pragma endregion
}
#pragma endregion