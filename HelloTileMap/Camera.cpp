#include "Camera.h"

#pragma region NAMESPACE
namespace
{
	Camera* sInstance = nullptr;
}
#pragma endregion

#pragma region STATIC INITIALIZE
void Camera::StaticInitialize()
{
	XASSERT(sInstance == nullptr, "Camera already initialized! There should only be one!");
	sInstance = new Camera();
}
#pragma endregion

#pragma region STATIC TERMINATE
void Camera::StaticTerminate()
{
	delete sInstance;
	sInstance = nullptr;
}
#pragma endregion

#pragma region GET
Camera& Camera::Get()
{
	XASSERT(sInstance != nullptr, "Camera not initialized yet! Call StaticInitialize() first!");
	return *sInstance;
}
#pragma endregion

#pragma region CONVERT TO SCREEN POSITION
X::Math::Vector2 Camera::ConvertToScreenPosition(const X::Math::Vector2& worldPosition) const
{
	return worldPosition - mOffset;
}
#pragma endregion

#pragma region CONVERT TO WORLD POSITION
X::Math::Vector2 Camera::ConvertToWorldPosition(const X::Math::Vector2& screenPosition) const
{
	return screenPosition + mOffset;
}
#pragma endregion

#pragma region SET VIEW BOUND
void Camera::SetViewBound(const X::Math::Rect& viewBound)
{
	mViewBound = viewBound;

	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());

	// Piece of mind error checking
	if (mViewBound.right - mViewBound.left < screenWidth)
	{
		mViewBound.right = mViewBound.left + screenWidth;
	}

	if (mViewBound.bottom - mViewBound.top < screenHeight)
	{
		mViewBound.bottom = mViewBound.top + screenHeight;
	}
}
#pragma endregion

#pragma region SET VIEW POSITION
void Camera::SetViewPosition(const X::Math::Vector2& viewPosition)
{
	const float screenWidth = static_cast<float>(X::GetScreenWidth());
	const float screenHeight = static_cast<float>(X::GetScreenHeight());

	const X::Math::Vector2 halfScreenSize{ screenWidth * 0.5f, screenHeight * 0.5f };

	// Compute the position offset
	mOffset = viewPosition - halfScreenSize;

	// Ensure offset is within viewbound
	if (mOffset.x < mViewBound.left)
	{
		mOffset.x = mViewBound.left;
	}
	if (mOffset.y < mViewBound.top)
	{
		mOffset.y = mViewBound.top;
	}
	if (mOffset.x > mViewBound.right - screenWidth)
	{
		mOffset.x = mViewBound.right - screenWidth;
	}
	if (mOffset.y > mViewBound.bottom - screenHeight)
	{
		mOffset.y = mViewBound.bottom - screenHeight;
	}
}
#pragma endregion