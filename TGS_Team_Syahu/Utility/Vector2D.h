#pragma once

typedef struct _Vector2D
{
	float x;
	float y;

}Vector2D;

//2Dベクトルの加算
inline Vector2D Vec2DAdd(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D ret = {};

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;

	return ret;
}

//2Dベクトルの減算
inline Vector2D Vec2DSub(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D ret = {};

	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;

	return ret;
}

//2Dベクトルの乗算
inline Vector2D Vec2DMult(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D ret = {};

	ret.x = vec1.x * vec2.x;
	ret.y = vec1.y * vec2.y;

	return ret;
}

//2Dベクトルの徐算
inline Vector2D Vec2DDiv(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D ret = {};

	ret.x = vec1.x / vec2.x;
	ret.y = vec1.y / vec2.y;

	return ret;
}

//2Dベクトルの内積
inline float Vec2Dot(const Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

//2Dベクトルの外積
inline float Vec2Cross(const Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}
