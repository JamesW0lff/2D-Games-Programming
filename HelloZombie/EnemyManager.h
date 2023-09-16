#pragma once
#include <XEngine.h>

#include "Enemy.h"

class EnemyManager
{
public:
	// Singleton Pattern
	// -> A software design principle that restricts class instantiation to one object
	// -> This is useful when exactly one object is needed to coordinate actions across a system
	// -> We only need one EnemyManager to manage all our enemies!

	// singleton methos
	static void StaticInitialize();
	static void StaticTerminate();
	static EnemyManager& Get();

public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void CheckCollision(const X::Math::LineSegment& lineSegment, int damageReceived);

private:
	std::vector<Enemy*> mEnemies;

	float mNextSpawnTime = 0.0f;
};

