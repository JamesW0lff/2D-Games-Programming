#include <XEngine.h>

#include "Camera.h"
#include "Link.h"
#include "TileMap.h"

Link link;

#pragma region GAME INIT
void GameInit() // Initialize game
{
	TileMap::StaticInitialize();
	TileMap::Get().Load("Level02.txt", "Tileset01.txt");

	Camera::StaticInitialize();
	Camera::Get().SetViewBound(TileMap::Get().GetBound());

	link.Load();
	link.SetPosition({ 300.0f, 300.0f });
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime) // Run game
{
	// Update
	TileMap::Get().Update(deltaTime);
	link.Update(deltaTime);

	Camera::Get().SetViewPosition(link.GetPosition());

	// Render
	TileMap::Get().Render();
	link.Render();

	// Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanUp() // Cleanup game
{
	link.Unload();

	Camera::StaticTerminate();

	TileMap::Get().Unload();
	TileMap::StaticTerminate();

}
#pragma endregion

#pragma region WIN MAIN
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanUp();
	X::Stop();

	return 0;

}
#pragma endregion