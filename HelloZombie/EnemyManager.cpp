/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "EnemyManager.h"
#include "Survivor.h"

extern Survivor survivor;

#pragma region NAMESPACE
namespace
{
	EnemyManager* sInstance = nullptr;
}
#pragma endregion

#pragma region STATIC INITIALIZE
void EnemyManager::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "EnemyManager already initialized! There should be only one");
	sInstance = new EnemyManager();
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
	// Spawn enemuies
	if (mNextSpawnTime < X::GetTime())
	{
		Enemy* enemy = new Enemy();
		enemy->Load();

		const float spawnX = X::RandomFloat(100.0f, X::GetScreenWidth() - 100.0f);
		const float spawnY = -50.0f;
		enemy->SetPosition({ spawnX, spawnY });

		mEnemies.push_back(enemy);

		// Reset spawn timer (every 1- 3 seconds)
		mNextSpawnTime = X::GetTime() + X::RandomFloat(1.0f, 3.0f);
	}

	// Update enemies
	for (auto enemy : mEnemies)
	{
		enemy->Update(deltaTime);
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

#pragma region CHECK COLLISION
void EnemyManager::CheckCollision(const X::Math::LineSegment& lineSegment, int damageReceived)
{
	// Note: this will hurt the first enemy found, NOT the closest one/

	float closestDistanceSqr = std::numeric_limits<float>::max();
	Enemy* closestIntersectingEnemy = nullptr;

	for (auto enemy : mEnemies)
	{
		if (enemy->IsAlive())
		{
			if (X::Math::Intersect(lineSegment, enemy->GetBoundingCircle()))
			{
				const float distanceSqr = X::Math::DistanceSqr(enemy->GetPosition(), survivor.GetPosition());
				if (distanceSqr < closestDistanceSqr)
				{
					closestDistanceSqr = distanceSqr;
					closestIntersectingEnemy = enemy;
				}
			}
			
			
		}

		if (enemy->IsAlive())
		{
			if (X::Math::Intersect(enemy->GetBoundingCircle(), survivor.GetBoundingCircle()))
			{
				survivor.Health(10.0f);
			}
		}
	}

	if (closestIntersectingEnemy)
	{
		closestIntersectingEnemy->Hurt(damageReceived);
	}

}
#pragma endregion

#pragma region ORIGINAL CHECK COLLISION CODE
/*
#pragma region CHECK COLLISION
void EnemyManager::CheckCollision(const X::Math::LineSegment& lineSegment)
{
	// Note: this will hurt the first enemy found, NOT the closest one/

	for (auto enemy : mEnemies)
	{
		if (enemy->IsAlive())
		{
			if (X::Math::Intersect(lineSegment, enemy->GetBoundingCircle()))
			{
				enemy->Hurt(50.0f);
				break;
			}
		}
	}
}
#pragma endregion
*/
#pragma endregion