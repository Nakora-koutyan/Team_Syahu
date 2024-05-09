#pragma once
#include"../../../Collision/Line/LineCollision.h"

#define LARGESWORD_ATTACK_TIME	FPS * 0.3		//大剣攻撃の時間
#define LARGESWORD_ANGLE		5.5f			//大剣の振る角度/f
#define LARGRSWORD_LENGTH		100.f			//大剣の長さ
#define LARGESWORD_WEIGHT		0.75f			//大剣の重さ
#define LARGESWORD_DAMAGE		5.f				//大剣のダメージ

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
	void Update(CharaBase* chara);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たった時の処理
	void Hit(CharaBase* enemy, const Player* player);

};

