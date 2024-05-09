#pragma once
#include"../../../Collision/Line/LineCollision.h"

#define DAGGER_ATTACK_TIME	FPS * 0.2		//短剣攻撃の時間
#define DAGGER_ANGLE		5.5f			//短剣の振る角度/f
#define DAGGER_LENGTH		75.f			//短剣の長さ
#define DAGGER_WEIGHT		0.05f			//ダガーの重さ
#define DAGGER_DAMAGE		1.5f			//ダガーのダメージ

class CharaBase;
class Player;

class Dagger :public LineCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	Dagger();

	//デストラクタ
	~Dagger();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たった時の処理
	void Hit(CharaBase* enemy, const Player* player);

};

