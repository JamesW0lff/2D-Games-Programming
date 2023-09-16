/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class Enemy
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	const X::Math::Vector2& GetPosition() const { return mEnemyPosition; }
	void SetPosition(const X::Math::Vector2& position) { mEnemyPosition = position; mResetEnemyPosition = position; }
	X::Math::Circle GetBoundingCircle() const { return { mEnemyPosition, 30.0f }; }

	void OutOfBounds(float deltaTime);
	void DestroyedEnemySound();

	void Hurt(float damage) { mEnemyHP -= damage; }
	bool IsAlive() const { return mEnemyHP > 0.0f; }

	float GetEnemyHeight() { return mEnemyHeight; }

	void NextWave(int enemyCounter);

private:

	X::TextureId mEnemyTextureId = 0;
	X::TextureId mEnemiesTextureId[3];
	X::SoundId mEnemyDefeatedSoundId = 0;

	X::Math::Vector2 mEnemyPosition;
	X::Math::Vector2 mResetEnemyPosition;
	int mEnemyIndex = 0;

	float mEnemySpeed = 0.0f;
	float mEnemyHP = 0.0f;
	float mEnemyHeight = 0.0f;
	// float mWaveTime = 0.0f;

};

