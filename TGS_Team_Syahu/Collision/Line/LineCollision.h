#pragma once
#include"../../Actor/ObjectBase.h"

class LineCollision :public ObjectBase
{
protected:
	Vector2D directionVector;		//方向ベクトル

public:
	//コンストラクタ
	LineCollision();

	//デストラクタ
	~LineCollision();

	//初期化処理
	void Initialize()override {};

	//終了処理
	void Finalize()override {};

	//更新
	void Update()override {};

	//描画
	void Draw()const override {};

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override {};

public:
	//方向ベクトルを取得
	Vector2D GetDirectionVector()const { return directionVector; }

	//方向ベクトルを設定
	void SetDirectionVector(const Vector2D move) { directionVector = move; }

	//方向ベクトルxを設定
	void SetDirectionVectorX(const float x) { directionVector.x = x; }

	//方向ベクトルyを設定
	void SetDirectionVectorY(const float y) { directionVector.y = y; }

	//線分の終点を取得
	Vector2D GetLineEnd()const { return { location.x + directionVector.x,location.y + directionVector.y }; }

public:
	//線の当たり判定
	bool HitLine(const ObjectBase* object)const override;

	//四角の当たり判定
	bool HitBox(const ObjectBase* object)const override;

	//円の当たり判定
	bool HitSphere(const ObjectBase* object)const override;

};

