#pragma once
#include"../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//必要なスティックの傾き割合
#define MAX_SPEED			10.f		//最高速度	
#define GRAVITY				0.8f		//落下速度
#define JUMP_POWER			15.f		//ジャンプ力

class GameMainScene;

class CharaBase :public BoxCollision
{
protected:
	Vector2D vector;			//移動量

	float hp;					//HP

	bool isAir;					//空中？

public:
	//コンストラクタ
	CharaBase();

	//デストラクタ
	~CharaBase();

	//更新
	virtual void Update(GameMainScene* object) = 0;

	//描画
	virtual void Draw()const = 0;
	
};
