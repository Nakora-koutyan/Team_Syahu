#pragma once
#include"DxLib.h"
#include"../Utility/Vector2D.h"
#include"../Utility/Area.h"

enum class CollisionType
{
	Empty = 0,		//空
	Box,			//四角
	Sphere			//円
};

class BoxCollision;
class SphereCollision;

class CollisionBase
{
protected:
	Vector2D location;			//ワールド座標
	Vector2D screenLocation;	//スクリーン座標

	CollisionType collisionType;			//コリジョンの種類
public:
	//コンストラクタ
	CollisionBase();

	//デストラクタ
	~CollisionBase();

	//当たり判定
	bool HitCheck(const CollisionBase* collision)const;

	//四角と円の当たり判定に必要な斜辺を作成する
	float MakeHypotenuse(const float x1, const float y1, const float x2, const float y2)const;

public:
	//ワールド座標を取得する
	Vector2D GetLocation()const { return location; }

	//ワールド座標を設定
	void SetLocation(const Vector2D location) { this->location = location; }

	//スクリーン座標を取得する
	Vector2D GetScreenLocation()const { return screenLocation; }

	//スクリーン座標を設定
	void SetScreenLocation(const Vector2D location) { this->screenLocation = location; }

	//コリジョンの種類を取得する
	CollisionType GetType()const { return collisionType; }
	
protected:
	//四角との当たり判定
	virtual bool HitBox(const BoxCollision* collision)const = 0;

	//円との当たり判定
	virtual bool HitSphere(const SphereCollision* collision)const = 0;

};

