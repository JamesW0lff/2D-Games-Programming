/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include <XEngine.h>

class GameManager
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void IsGamePresentation(bool gamePresentation);
	void IsGameOver(bool gameOver);
	
	void UpdateScore(int score);
	int GetGameScore() { return mGameScore; }

	void DisplayGameMechanics();
	void DisplayGameScore();
	void DisplayFinalScore();

private:

	X::TextureId mBackgroundTexture;
	X::TextureId mSpaceshipTextureId;
	X::TextureId mSpaceshipLifeTextureId;
	X::TextureId mBulletTextureId;
	X::TextureId mEnemyTextureId;

	X::SoundId mBackgroundSoundId;

	int mGameScore;
	bool mGamePresentation;
	bool mGameOver;
};

