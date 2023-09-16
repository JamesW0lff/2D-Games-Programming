/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#include <XEngine.h>
#include <iostream>
#include "Survivor.h"
#include "EnemyManager.h"

#pragma region GLOBALS
Survivor survivor;

X::TextureId mSurvivorHandgunTextureId = 0;
X::TextureId mSurvivorRifleTextureId = 0;
X::TextureId mSurvivorShotgunTextureId = 0;

X::TextureId mBackgroundTextureId = 0;

#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	EnemyManager::StaticInitialize();

	survivor.Load(1);
	survivor.SetPosition({ 500.0f, 500.0f });

	X::ShowSystemCursor(false);
}
#pragma endregion

#pragma region GAME RULES
bool GameMgr(float deltaTime)
{
	// Load Textures to show
	mSurvivorHandgunTextureId = X::LoadTexture("survivor_handgun.png");
	mSurvivorRifleTextureId = X::LoadTexture("survivor_rifle.png");
	mSurvivorShotgunTextureId = X::LoadTexture("survivor_shotgun.png");
	mBackgroundTextureId = X::LoadTexture("forest.jpg");

	// Draw Background Image
	X::DrawSprite(mBackgroundTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f));

	// Draw screen text title
	X::DrawScreenText("Hello Zombie Rules: ", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.05, 20.0f, X::Colors::White);

	// Draw game movement mechanics
	X::DrawScreenText("Use \"W\", \"A\", \"S\", \"D\" on the keyboard to move the player", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.2, 15.0f, X::Colors::White);
	X::DrawScreenText("Press \"1\", \"2\", or \"3\" on the keyboard to change weapons", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.3, 15.0f, X::Colors::White);

	// Draw sprites to show which weapons there are
	X::DrawSprite(mSurvivorHandgunTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.2, X::GetScreenHeight() * 0.5));
	X::DrawSprite(mSurvivorRifleTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.4, X::GetScreenHeight() * 0.5));
	X::DrawSprite(mSurvivorShotgunTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.6, X::GetScreenHeight() * 0.5));

	// Draw shooting mechanics
	X::DrawScreenText("Aim by moving the mouse where you want to shoot.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.6, 15.0f, X::Colors::White);
	X::DrawScreenText("Shoot enemies by pressing \"Left Clic\" in your mouse.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.7, 15.0f, X::Colors::White);
	X::DrawScreenText("Reload your weapon by pressing \"Right Clic\" in your mouse or \"R\" button in your keyboard.", X::GetScreenWidth() * 0.05, X::GetScreenHeight() * 0.8, 15.0f, X::Colors::White);

	// Exit Ruleset Condition Message
	X::DrawScreenText("Press ENTER to continue", X::GetScreenWidth() * 0.2, X::GetScreenHeight() * 0.9, 15.0f, X::Colors::White);

	return (X::IsKeyPressed(X::Keys::ENTER));
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	mBackgroundTextureId = X::LoadTexture("bg_image.jpg");
	X::DrawSprite(mBackgroundTextureId, X::Math::Vector2(X::GetScreenWidth() * 0.5f, X::GetScreenHeight() * 0.5f));

	EnemyManager::Get().Update(deltaTime);
	survivor.Update(deltaTime);

	EnemyManager::Get().Render();
	survivor.Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	EnemyManager::Get().Unload();
	EnemyManager::StaticTerminate();

	survivor.Unload();
}
#pragma endregion

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)//(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	X::Start();
	GameInit();

	X::Run(GameMgr);

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;

}
#pragma endregion