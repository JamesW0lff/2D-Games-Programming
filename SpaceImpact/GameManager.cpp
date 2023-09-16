/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include "GameManager.h"

#include <iostream>
#include <string>

using std::string;

#pragma region LOAD
void GameManager::Load()
{
	mBackgroundTexture = X::LoadTexture("blue_bg.png");
	mSpaceshipTextureId = X::LoadTexture("spaceship.png");
	mSpaceshipLifeTextureId = X::LoadTexture("spaceship_life_icon.png");
	mBulletTextureId = X::LoadTexture("spaceship_bullet.png");
	mEnemyTextureId = X::LoadTexture("spaceship_alien_01.png");

	mBackgroundSoundId = X::LoadSound("CastlevaniaIII_ DraculasCurse.wav");

	mGamePresentation = true;
	mGameOver = false;
	mGameScore = 0;
}
#pragma endregion

#pragma region UNLOAD
void GameManager::Unload()
{

}
#pragma endregion

#pragma region IS GAME PRESENTATION
void GameManager::IsGamePresentation(bool gamePresentation)
{
	mGamePresentation = gamePresentation;
}
#pragma endregion

#pragma region IS GAME OVER
void GameManager::IsGameOver(bool gameOver)
{
	mGameOver = gameOver;
}
#pragma endregion

#pragma region UPDATE
void GameManager::Update(float deltaTime)
{
	
}
#pragma endregion

#pragma region UPDATE SCORE
void GameManager::UpdateScore(int score)
{ 
	mGameScore += score; 
}
#pragma endregion

#pragma region RENDER
void GameManager::Render()
{
	if (mGamePresentation == true)
	{
		DisplayGameMechanics();
	}
	else if (mGameOver == true)
	{
		DisplayFinalScore();
	}
	else
	{
		DisplayGameScore();
	}
}
#pragma endregion

#pragma region DISPLAY GAME MECHANICS
void GameManager::DisplayGameMechanics()
{
	// Draw background image
	X::DrawSprite(mBackgroundTexture, X::Math::Vector2(X::GetScreenWidth() * 0.5, X::GetScreenHeight() * 0.5));

	// Draw screen text title
	X::DrawScreenText("Space Impact 2.0 ", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.03, 20.0f, X::Colors::White);

	// Draw game mechanics
	X::DrawScreenText("Use \"W\", \"A\", \"S\", \"D\" on your keyboard to move the player.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.1, 15.0f, X::Colors::White);
	X::DrawScreenText("Press \"Left Button\" on your mouse to shoot an enemy. Each enemy is worth 100 points.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.2, 15.0f, X::Colors::White);

	// Draw sprites to show how game works
	X::DrawSprite(mSpaceshipTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.2, X::GetScreenHeight() * 0.3));
	X::DrawSprite(mBulletTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.3, X::GetScreenHeight() * 0.3));
	X::DrawSprite(mEnemyTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.5, X::GetScreenHeight() * 0.3));

	// Draw game rules
	X::DrawScreenText("You will start with 3 lifes.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.4, 15.0f, X::Colors::White);
	for (int i = 0; i < 3; ++i)
	{
		X::DrawSprite(mSpaceshipLifeTextureId, X::Math::Vector2(X::GetScreenWidth() * (i+1)/10, X::GetScreenHeight() * 0.5));
	}
	
	X::DrawScreenText("Each time you earn 1,000 points, you will get one extra life. You can get a max of 10 lifes.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.6, 15.0f, X::Colors::White);

	X::DrawScreenText("If you crash with an alien spaceship, you will lose one life. Losing all lifes will cause a \"Game Over\".", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.7, 15.0f, X::Colors::White);

	// Exit Ruleset Condition Message
	X::DrawScreenText("Press ENTER to continue", X::GetScreenWidth() * 0.2, X::GetScreenHeight() * 0.8, 15.0f, X::Colors::White);
}
#pragma endregion

#pragma region DISPLAY GAME SCORE
void GameManager::DisplayGameScore()
{
	X::PlaySoundLoop(mBackgroundSoundId);

	// convert int to string
	string score = std::to_string(GetGameScore()); // std::to_string(mGameScore);

	X::DrawScreenText("Score: ", 900.0f, 40.0f, 30.0f, X::Colors::White);
	// c_str() -> return a pointer to an array that contains a sequence of characters
	X::DrawScreenText(score.c_str(), 1000.0f, 40.0f, 30.0f, X::Colors::White);
}
#pragma endregion

#pragma region DISPLAY FINAL SCORE
void GameManager::DisplayFinalScore()
{
	X::StopSoundLoop(mBackgroundSoundId);

	string score = std::to_string(GetGameScore());

	// Draw background image
	X::DrawSprite(mBackgroundTexture, X::Math::Vector2(X::GetScreenWidth() * 0.5, X::GetScreenHeight() * 0.5));

	// Draw screen text title
	X::DrawScreenText("GAME OVER!", X::GetScreenWidth() * 0.3, X::GetScreenHeight() * 0.2, 50.0f, X::Colors::White);

	X::DrawScreenText("Final Score: ", X::GetScreenWidth() * 0.3, X::GetScreenHeight() * 0.5, 30.0f, X::Colors::White);
	X::DrawScreenText(score.c_str(), X::GetScreenWidth() * 0.5, X::GetScreenHeight() * 0.5, 30.0f, X::Colors::White);

	// Exit Ruleset Condition Message
	X::DrawScreenText("Press ENTER to continue", X::GetScreenWidth() * 0.2, X::GetScreenHeight() * 0.8, 25.0f, X::Colors::White);

}
#pragma endregion