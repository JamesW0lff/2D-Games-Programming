#include "TileMap.h"
#include "Camera.h"

#pragma region NAMESPACE
namespace
{
	// Texture size at hand is 32x32, must change for different sized textures
	constexpr float TILE_SIZE = 32.0f;

	TileMap* sInstance = nullptr;
}
#pragma endregion

#pragma region STATIC INITIALIZE
void TileMap::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "TileMap already initialized! There should only be one!");
	sInstance = new TileMap();
}
#pragma endregion

#pragma region STATIC TERMINATE
void TileMap::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
#pragma endregion

#pragma region GET
TileMap& TileMap::Get()
{
	XASSERT(sInstance != nullptr, "TileMap not initialized yet! Call StaticInitialize() first!");
	return *sInstance;
}
#pragma endregion

#pragma region LOAD
void TileMap::Load(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName)
{
	LoadMap(mapName);
	LoadTextures(tilesetName);
}
#pragma endregion

#pragma region UNLOAD
void TileMap::Unload()
{
	mColumns = 0;
	mRows = 0;

	delete[] mMap;
	mMap = nullptr;

	mTiles.clear();

}
#pragma endregion

#pragma region UPDATE
void TileMap::Update(float deltaTime)
{
	
}
#pragma endregion

#pragma region RENDER
void TileMap::Render()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			//	Get the index for where we are when iterating through the tile map
			const int mapIndex = GetIndex(x, y);

			//	Here we get 0, or 1, or whatever number that is has on the array.
			const int tileIndex = mMap[mapIndex];

			//	Use that index to get the correct texture from the texture vector
			//	(grass, flower, tree)
			const X::TextureId textureId = mTiles[tileIndex];

			//	Position that texture on the screen and render int
			const X::Math::Vector2 worldPosition = { x * TILE_SIZE, y * TILE_SIZE };
			const X::Math::Vector2 screenPosition = Camera::Get().ConvertToScreenPosition(worldPosition);
			X::DrawSprite(textureId, screenPosition, X::Pivot::TopLeft);
		}
	}
}
#pragma endregion

#pragma region CHECK COLLISION
bool TileMap::CheckCollision(const X::Math::LineSegment& lineSegment) const
{
	const int startX =  static_cast<int>(lineSegment.from.x / TILE_SIZE);
	const int startY =  static_cast<int>(lineSegment.from.y / TILE_SIZE);
	const int endX =	static_cast<int>(lineSegment.to.x / TILE_SIZE);
	const int endY =	static_cast<int>(lineSegment.to.y / TILE_SIZE);

	// If out of bounds of the tile map
	if (startX < 0  || startX >= mColumns ||
		startY < 0  || startY >= mRows	  ||
		endX < 0	|| endX >= mColumns   ||
		endY < 0	|| endY >= mRows)
	{
		return true;
	}

	// If our line segment is colliding with any tile
	// that is marked as collidable
	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			const int index = GetIndex(x, y);
			if (mMap[index] > 1) // Not grass (0), not flower (1)
			{
				return true;
			}
		}
	}

	return false;
}
#pragma endregion

#pragma region GET BOUND
X::Math::Rect TileMap::GetBound() const
{
	//	Construct a rect and return it.
	return
	{
		0.0f,					// Left
		0.0f,					// Top
		mColumns * TILE_SIZE,	// Right
		mRows * TILE_SIZE		// Bottom
	};
}
#pragma endregion

#pragma region LOAD MAP
void TileMap::LoadMap(const std::filesystem::path& fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	XASSERT(file != nullptr, "File was not opened correctly! Ensure file name/location is correct!");

	if (file != nullptr)
	{
		fscanf_s(file, "Columns: %d\n", &mColumns);
		fscanf_s(file, "Rows: %d\n", &mRows);

		mMap = new int[mColumns * mRows];
		for (int y = 0; y < mRows; ++y)
		{
			for (int x = 0; x < mColumns; ++x)
			{
				const int index = GetIndex(x, y);

				//	Subtract the ASCII value for 0
				mMap[index] = fgetc(file) - '0';
			}

			//	Get the new line character to move to the next row read.
			fgetc(file);
		}

		fclose(file);

	}

}
#pragma endregion

#pragma region LOAD TEXTURES
void TileMap::LoadTextures(const std::filesystem::path& fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	XASSERT(file != nullptr, "File was not opened correctly! Ensure file name/location is correct!");

	if (file != nullptr)
	{

		int count = 0;

		fscanf_s(file, "Count: %d\n", &count);

		mTiles.clear();
		mTiles.resize(count);

		for (int i = 0; i < count; ++i)
		{
			char buffer[256];
			fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

			mTiles[i] = X::LoadTexture(buffer);
		}

		fclose(file);

	}

}
#pragma endregion

#pragma region GET INDEX
int TileMap::GetIndex(int column, int row) const
{
	// Example:
	// If looking for column 1 and row 3, with 2 total coolumns
	// {
	//		0, 1,
	//		0, 0,
	//		1, 1
	// }
	// 
	// index  = 1 + (3 * 2)
	// index = 7

	return column + (row * mColumns);

}
#pragma endregion