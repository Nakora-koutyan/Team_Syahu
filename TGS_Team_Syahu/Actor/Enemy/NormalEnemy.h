#pragma once
#include"../CharaBase.h"

class NormalEnemy :public CharaBase
{
private:

public:
	//コンストラクタ
	NormalEnemy();

	//デストラクタ
	~NormalEnemy();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

};

