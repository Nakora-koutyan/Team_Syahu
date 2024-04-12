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

	//四角と円の当たり判定に必要な斜辺の作成
	float MakeHypotenuse(const float x1, const float y1, const float x2, const float y2)const;

public:
	//ワールド座標の取得
	Vector2D GetLocation()const { return location; }

	//ワールド座標の設定
	void SetLocation(const Vector2D location) { this->location = location; }

	//スクリーン座標の取得
	Vector2D GetScreenLocation()const { return screenLocation; }

	//スクリーン座標の設定
	void SetScreenLocation(const Vector2D location) { this->screenLocation = location; }

	//コリジョンの種類の取得
	CollisionType GetType()const { return collisionType; }
	
protected:
	//四角の当たり判定
	virtual bool HitBox(const BoxCollision* collision)const = 0;

	//円の当たり判定
	virtual bool HitSphere(const SphereCollision* collision)const = 0;

};

