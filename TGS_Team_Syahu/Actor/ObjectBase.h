#pragma once
#include"DxLib.h"
#include"../Utility/Vector2D.h"
#include"../Utility/Area.h"

enum class CollisionType
{
	None = 0,		//なし
	Box,			//四角
	Sphere,			//円
	Line			//線
};

enum class ObjectType
{
	None = 0,		//なし
	Object,			//物体
	Character		//キャラクター
};

class ObjectBase
{
protected:
	Vector2D location;					//ワールド座標
	Vector2D screenLocation;			//スクリーン座標

	CollisionType collisionType;		//コリジョンの種類
	ObjectType objectType;				//オブジェクトの種類

	float damage;						//ダメージ量

public:
	//コンストラクタ
	ObjectBase();

	//デストラクタ
	~ObjectBase();

	//初期化処理
	virtual void Initialize() = 0;

	//終了処理
	virtual void Finalize() = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw()const = 0;

	//ヒット処理
	virtual void Hit(ObjectBase* object, const float damage) {};

public:
	//当たり判定
	bool CollisionCheck(const ObjectBase* collision)const;

	//四角と円の当たり判定に必要な斜辺の作成
	float MakeHypotenuse(const float x1, const float y1, const float x2, const float y2)const;

public:
	//ワールド座標の取得
	Vector2D GetLocation()const { return location; }

	//ワールド座標の設定
	void SetLocation(const Vector2D location) { this->location = location; }

	//ワールド座標xの設定
	void SetLocationX(const float x) { this->location.x = x; }

	//ワールド座標yの設定
	void SetLocationY(const float y) { this->location.y = y; }

	//スクリーン座標の取得
	Vector2D GetScreenLocation()const { return screenLocation; }

	//スクリーン座標の設定
	void SetScreenLocation(const Vector2D location) { this->screenLocation = location; }

	//コリジョンの種類の取得
	CollisionType GetCollisionType()const { return collisionType; }

	//オブジェクトの種類の取得
	ObjectType GetObjectType()const { return objectType; }

	//ダメージを取得
	float GetDamage()const { return damage; }
	
protected:
	//四角の当たり判定
	virtual bool HitBox(const ObjectBase* object)const { return false; }

	//円の当たり判定
	virtual bool HitSphere(const ObjectBase* object)const { return false; }

	//線の当たり判定
	virtual bool HitLine(const ObjectBase* object)const { return false; }

};

