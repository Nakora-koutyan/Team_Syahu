#pragma once
#include"DxLib.h"
#include"../Utility/Vector2D.h"
#include"../Utility/Area.h"

enum CollisionType
{
	Empty = 0,		//空
	box				//ボックス
};

class BoxCollision;

class CollisionBase
{
protected:
	Vector2D location;			//座標
	Vector2D screenLocation;	//スクリーン座標

	CollisionType type;			//コリジョンの種類
public:
	//コンストラクタ
	CollisionBase();

	//デストラクタ
	~CollisionBase();

	//当たり判定
	bool HitCheck(const CollisionBase* collision)const;

	//座標を取得する
	Vector2D GetLocation()const { return location; }

	//コリジョンの種類を取得する
	CollisionType GetType()const { return type; }
	
protected:
	//ボックスとの当たり判定
	virtual bool HitBox(const BoxCollision* obb)const = 0;

};

