#pragma once
#include"../../../Collision/Line/LineCollision.h"

#define LARGESWORD_ATTACK_TIME	FPS * 2.5		//大剣攻撃の時間

class CharaBase;
class Player;

class LargeSword :public LineCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	LargeSword();

	//デストラクタ
	~LargeSword();

	//更新
	void Update(Player* player);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たった時の処理
	void Hit(CharaBase* enemy, Player* player);

};

