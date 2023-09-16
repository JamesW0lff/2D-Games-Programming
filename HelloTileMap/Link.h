#pragma once

#include <XEngine.h>

class Link
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

	X::Math::Vector2 CheckCollision(X::Math::Vector2 displacement, X::Math::Rect currentBox);

	X::Math::Rect GetBoundingBox() const;

private:
	void SetDisplacementThisFrame(X::Math::Vector2& displacement, float deltaTime);

	X::TextureId mTextureId = 0;
	X::Math::Vector2 mPosition;

	float mMoveSpeed = 0.0f;

};
