/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma region INCLUDE
#include <XEngine.h>
#include <iostream>

#include "Environment.h"
#include "Spaceship.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "GameManager.h"
#pragma endregion

#pragma region GLOBALS
Environment _environment;
Spaceship _spaceship;
GameManager _gameManager;
#pragma endregion

#pragma region GAME INIT
void GameInit() // Initialize game
{
	// ======= Initialize Game =======
	_gameManager.Load();

	_environment.Load();

	_spaceship.Load();
	_spaceship.SetPosition({ 160.0f, 360.0f });

	BulletManager::StaticInitialize();
	BulletManager::Get().Load();

	EnemyManager::StaticInitialize();
}
#pragma endregion

#pragma region MENU
bool GameMgr(float deltaTime)
{
	_gameManager.Update(deltaTime);

	_gameManager.Render();

	return (X::IsKeyPressed(X::Keys::ENTER));
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime) // Run game
{
	// ======= UPDATE =======
	_gameManager.Update(deltaTime);
	_environment.Update(deltaTime);
	_spaceship.Update(deltaTime);
	BulletManager::Get().Update(deltaTime);
	EnemyManager::Get().Update(deltaTime);

	// ======= RENDER ======= 
	_gameManager.Render();
	_environment.Render();
	_spaceship.Render();
	_spaceship.RenderLife();
	BulletManager::Get().Render();
	EnemyManager::Get().Render();

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE) || _spaceship.OutOfLives();
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanUp() // Cleanup game
{
	BulletManager::Get().Unload();
	BulletManager::StaticTerminate();

	EnemyManager::Get().Unload();
	EnemyManager::StaticTerminate();
}
#pragma endregion

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameMgr);
	_gameManager.IsGamePresentation(false);

	X::Run(GameLoop);
	_gameManager.IsGameOver(true);

	X::Run(GameMgr);

	GameCleanUp();
	X::Stop();

	return 0;
}
#pragma endregion