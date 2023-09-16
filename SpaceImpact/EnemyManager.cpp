/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "EnemyManager.h"
#include "GameManager.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "Enemy.h"

#include <stdlib.h>
#include <time.h>
#include <algorithm>

// Right click > Go to Definition / or F12
extern Spaceship _spaceship;
extern GameManager _gameManager;

#pragma region NAMESPACE
namespace
{
	EnemyManager* sInstance = nullptr;

	int resetCounter = 60;
}
#pragma endregion

#pragma region STATIC INITIALIZE
void EnemyManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "EnemyManager already initialized! There should be only one");
	sInstance = new EnemyManager();

	srand(time(NULL));
}
#pragma endregion

#pragma region STATIC TERMINATE
void EnemyManager::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
#pragma endregion

#pragma region GET
EnemyManager& EnemyManager::Get()
{
	XASSERT(sInstance != nullptr, "EnemyManager not initialized yet! Call StaticInitialize() first!");
	return *sInstance;
}
#pragma endregion

#pragma region UNLOAD
void EnemyManager::Unload()
{
	for (auto enemy : mEnemies)
	{
		enemy->Unload();
		delete enemy;
	}

	mEnemies.clear();
}
#pragma endregion

#pragma region UPDATE
void EnemyManager::Update(float deltaTime)
{
	CheckCollisionSpaceship();

	// int sizeOfEnemyArray = (int)(sizeof(mEnemies) / sizeof(mEnemies[0]));

	if (mNextSpawnTime < X::GetTime())
	{
		Enemy* enemy = new Enemy();
		enemy->Load();

		const float spawnX = X::GetScreenWidth() + 100.0f;
		const float spawnY = X::RandomFloat(96, X::GetScreenHeight() - enemy->GetEnemyHeight());// rand() % X::GetScreenHeight() + 64;
		enemy->NextWave(mEnemyCounter);
		enemy->SetPosition({ spawnX, spawnY });

		mEnemies.push_back(enemy);

		// Reset spawn timer every 2.5 seconds
		mNextSpawnTime = X::GetTime() + 2.5f;		
	}

	for (auto enemy : mEnemies)
	{
		if (enemy->IsAlive())
		{
			enemy->Update(deltaTime);
		}
		else if (!enemy->IsAlive())
		{
			mScore += 50;
			_gameManager.UpdateScore(50);
			enemy->DestroyedEnemySound();

			if (mScore == 1000)
			{
				mScore = 0;
				_spaceship.IncreaseLife();
			}

			mEnemies.erase(std::remove(mEnemies.begin(), mEnemies.end(), enemy), mEnemies.end());
			
			if (mEnemyCounter <= resetCounter)
			{
				mEnemyCounter++;
			}
			else
			{
				mEnemyCounter = 0;
			}
		}
	}

}
#pragma endregion

#pragma region RENDER
void EnemyManager::Render()
{
	for (auto enemy : mEnemies)
	{
		enemy->Render();
	}
}
#pragma endregion

#pragma region CHECK COLLISION SPACESHIP
void EnemyManager::CheckCollisionSpaceship()
{
	if (mCollisionTimer < X::GetTime())
	{
		// Timer for the collision
		for (auto enemy : mEnemies)
		{
			if (enemy->IsAlive())
			{
				if (X::Math::Intersect(enemy->GetBoundingCircle(), _spaceship.GetBoundingCircle()))
				{
					_spaceship.ReceiveDamage();
					mCollisionTimer = X::GetTime() + 2.0f;
				}
			}
		}
	}
}
#pragma endregion

#pragma region CHECK COLLISION BULLET
void EnemyManager::CheckCollisionBullet(int damageReceived, Bullet& bullet)
{
	// Timer for the collision
	for (auto enemy : mEnemies)
	{
		if (enemy->IsAlive())
		{
			if (X::Math::Intersect(enemy->GetBoundingCircle(), bullet.GetBoundingCircle()))
			{
				bullet.Destroy();
				enemy->Hurt(damageReceived);
			}
		}
	}
}
#pragma endregion