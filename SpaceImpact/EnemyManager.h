/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>
#include <vector>

class Enemy;
class Bullet;

using std::vector;

class EnemyManager
{
public:

	static void StaticInitialize();
	static void StaticTerminate();
	static EnemyManager& Get();

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void CheckCollisionSpaceship();
	void CheckCollisionBullet(int damageReceived, Bullet& bullet);

private:

	vector<Enemy*> mEnemies;

	int mScore = 0;
	int mEnemyCounter = 0;

	float mNextSpawnTime = 0.0f;
	float mCollisionTimer = 0.0;

};

