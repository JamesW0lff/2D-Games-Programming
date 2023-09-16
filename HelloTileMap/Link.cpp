#include "Camera.h"
#include "Link.h"
#include "TileMap.h"

#pragma region NAMESPACE
namespace
{
	constexpr float SPRITE_SIZE_BUFFER = 12.0f;

	// enum class Edge
}
#pragma endregion

#pragma region ENUM DISPLACEMENT
enum Displacement
{
	D_LEFT,
	D_TOP,
	D_RIGHT,
	D_BOTTOM
};
#pragma endregion

#pragma region LOAD
void Link::Load()
{
	mTextureId = X::LoadTexture("zelda.png");
	mMoveSpeed = 250.0f;
}
#pragma endregion

#pragma region UNLOAD
void Link::Unload()
{

}
#pragma endregion

#pragma region UPDATE
void Link::Update(float deltaTime)
{
	// What is displacement in this scenario?
	//		-> the amount the character has moved in this update frame
	//
	// Generic movement strategy when AABB collision is involved:
	// 1.) Predict what the displacement WILL be based on player input
	// 2.) Check for collision
	// 3.) If collision occurs,
	//		-> set displacement to 0
	// 4.) Finally, add displacement to our position

	// 1.) Predict displacement for this frame
	X::Math::Vector2 displacement;
	SetDisplacementThisFrame(displacement, deltaTime);

	// 2.) Check for collision
	X::Math::Rect currentBox = GetBoundingBox();

	// Homework - Week 07
	// -> Condense these 4 code blocks into 1 reusable function for each different direction
	// -> Hint: use an enum for an "Edge" and pass that into the function as an argument

	displacement = CheckCollision(displacement, currentBox);

	// 4.) Finally, add displacement to our position
	mPosition += displacement;

}
#pragma endregion

#pragma region RENDER
void Link::Render()
{
	const X::Math::Vector2 screenPosition = Camera::Get().ConvertToScreenPosition(mPosition);

	// Once we have a camera, swap this for the screenPosition
	X::DrawSprite(mTextureId, screenPosition);
}
#pragma endregion

#pragma region CHECK COLLISION
X::Math::Vector2 Link::CheckCollision(X::Math::Vector2 displacement, X::Math::Rect currentBox)
{
	// Displacement _displacement;

	#pragma region LEFT
	if (displacement.x < 0.0f) // moving to the left
	{
		const X::Math::LineSegment leftEdge
		{
			currentBox.min.x + displacement.x,
			currentBox.min.y,
			currentBox.min.x + displacement.x,
			currentBox.max.y
		};
		if (TileMap::Get().CheckCollision(leftEdge))
		{
			displacement.x = 0.0f;
		}
	}
	#pragma endregion

	#pragma region TOP
	if (displacement.y < 0.0f) // moving to the top
	{
		const X::Math::LineSegment topEdge
		{
			currentBox.min.x,
			currentBox.min.y + displacement.y,
			currentBox.max.x,
			currentBox.min.y + displacement.y
		};
		if (TileMap::Get().CheckCollision(topEdge))
		{
			displacement.y = 0.0f;
		}
	}
	#pragma endregion

	#pragma region RIGHT
	if (displacement.x > 0.0f) // moving to the right
	{
		const X::Math::LineSegment rightEdge
		{
			currentBox.max.x + displacement.x,
			currentBox.min.y,
			currentBox.max.x + displacement.x,
			currentBox.max.y
		};
		if (TileMap::Get().CheckCollision(rightEdge))
		{
			displacement.x = 0.0f;
		}
	}
	#pragma endregion

	#pragma region BOTTOM
	if (displacement.y > 0.0f) // moving to the bottom
	{
		const X::Math::LineSegment bottomEdge
		{
			currentBox.min.x,
			currentBox.max.y + displacement.y,
			currentBox.max.x,
			currentBox.max.y + displacement.y
		};
		if (TileMap::Get().CheckCollision(bottomEdge))
		{
			displacement.y = 0.0f;
		}
	}
	#pragma endregion

	return displacement;
}
#pragma endregion

#pragma region GET BOUNDING BOX
X::Math::Rect Link::GetBoundingBox() const
{
	return
	{
		mPosition.x - SPRITE_SIZE_BUFFER, // Left
		mPosition.y - SPRITE_SIZE_BUFFER, // Top
		mPosition.x + SPRITE_SIZE_BUFFER, // Right
		mPosition.y + SPRITE_SIZE_BUFFER // Bottom
	};
}
#pragma endregion

#pragma region MOVE WITH WASD
void Link::SetDisplacementThisFrame(X::Math::Vector2& displacement, float deltaTime)
{
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		displacement.x += mMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		displacement.x -= mMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		displacement.y -= mMoveSpeed * deltaTime;
	}
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		displacement.y += mMoveSpeed * deltaTime;
	}
}
#pragma endregion