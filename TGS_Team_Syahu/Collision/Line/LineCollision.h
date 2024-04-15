#pragma once
#include"../CollisionBase.h"

class LineCollision :public CollisionBase
{
protected:
	Vector2D directionVector;		//方向ベクトル

public:
	//コンストラクタ
	LineCollision();

	//デストラクタ
	~LineCollision();

public:
	//方向ベクトルを取得
	Vector2D GetDirectionVector()const { return directionVector; }

	//方向ベクトルを設定
	void SetDirectionVector(const Vector2D vector) { directionVector = vector; }

	//線分の終点を取得
	Vector2D GetLineEnd()const { return { location.x + directionVector.x,location.y + directionVector.y }; }

public:
	//線の当たり判定
	bool HitLine(const LineCollision* collision)const override;

	//四角の当たり判定
	bool HitBox(const BoxCollision* collision)const override;

	//円の当たり判定
	bool HitSphere(const SphereCollision* collision)const override;

};

