#pragma once
#include "../Collision/Box/BoxCollision.h"

class BlockDeta;

class StageBlock : public BoxCollision
{
private:
	BlockDeta* blockdeta;

	int blockImg;
	int DrawType;
	bool IsDraw;
public:
	//コンストラクタ
	StageBlock(float x, float y, int type);

	//デストラクタ
	~StageBlock();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override;

	//画像タイプ取得
	int GetDrawType()
	{
		return DrawType;
	}

	//画面描画されてるか
	int GetIsDraw()
	{
		return IsDraw;
	}
};

