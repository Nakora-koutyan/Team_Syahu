#pragma once
#include "../Collision/Box/BoxCollision.h"

class StageBlock : public BoxCollision
{
private:
	bool stageBlockData[WORLD_BLOCK_X][WORLD_BLOCK_Y];
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

	void ResetStageBlockData() {
		for (int i = 0; i < WORLD_BLOCK_X; i++) {
			for (int j = 0; j < WORLD_BLOCK_Y; j++) {
				stageBlockData[i][j] = false;
			}
		}
	}
};

