#pragma once

#include <XEngine.h>

class TileMap
{
public:
	//	Singleton methods
	static void StaticInitialize();
	static void StaticTerminate();
	static TileMap& Get();

	void Load(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName);
	void Unload();

	void Update(float deltaTime);
	void Render();

	bool CheckCollision(const X::Math::LineSegment& lineSegment) const;

	X::Math::Rect GetBound() const;

private:
	void LoadMap(const std::filesystem::path& fileName);
	void LoadTextures(const std::filesystem::path& fileName);

	int GetIndex(int column, int row) const;

	int* mMap = nullptr;
	int mColumns = 0;
	int mRows = 0;

	std::vector<X::TextureId> mTiles;

};

