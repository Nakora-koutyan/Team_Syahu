#pragma once
#include"../CharaBase.h"

#define MAX_ENEMY_SPEED -1.5

class NormalEnemy :public CharaBase
{
private:
	int enemy_color;

	int usual_color;
	int damage_color;
	int attack_color;

public:
	//コンストラクタ
	NormalEnemy();

	//デストラクタ
	~NormalEnemy();

	//初期化関数
	void Initialize();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

	//移動処理
	void Movement();

};

