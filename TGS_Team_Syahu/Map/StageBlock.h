#pragma once
#include "../Collision/Box/BoxCollision.h"

class StageBlock : public BoxCollision
{
private:
	int stageData[WORLD_BLOCK_X][WORLD_BLOCK_Y];
	int DrawType;
	bool IsDraw;
public:
	//コンストラクタ
	StageBlock(int x, int y, int type, bool show);

	//デストラクタ
	~StageBlock();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override;

	void CopyStageData(int x, int y, int data) {
		stageData[x][y] = data;
	}

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

