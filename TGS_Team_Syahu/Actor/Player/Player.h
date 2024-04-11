#pragma once
#include"../CharaBase.h"

#define PLAYER_MOVE_SPEED		5.f			//プレイヤーの移動速度
#define PLAYER_MAX_MOVE_SPEED	15.f		//プレイヤーの最高移動速度

class Player :public CharaBase
{
private:

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

private:
	//移動
	void Movement();

	//アクション
	void Action();

};

