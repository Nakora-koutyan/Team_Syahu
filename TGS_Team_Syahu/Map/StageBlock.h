#pragma once
#include "../Collision/Box/BoxCollision.h"
class StageBlock : public BoxCollision
{
private:
	int DrawType;
	bool IsDraw;
public:
	//コンストラクタ
	StageBlock();

	//デストラクタ
	~StageBlock();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

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

