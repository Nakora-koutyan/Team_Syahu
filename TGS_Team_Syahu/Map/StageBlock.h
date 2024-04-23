#pragma once
#include "../Collision/Box/BoxCollision.h"
class StageBlock : public BoxCollision
{
private:

public:
	//コンストラクタ
	StageBlock();

	//デストラクタ
	~StageBlock();

	//更新
	void Update();

	//描画
	void Draw()const;
};

