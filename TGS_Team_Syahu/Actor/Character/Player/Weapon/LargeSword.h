#pragma once
#include"../../../../Collision/Line/LineCollision.h"

#define LARGESWORD_ATTACK_TIME	FPS * 0.09		//大剣攻撃の時間
#define LARGESWORD_ANGLE		15.5f			//大剣の振る角度/f
#define LARGRSWORD_LENGTH		100.f			//大剣の長さ
#define LARGESWORD_WEIGHT		0.75f			//大剣の重さ
#define LARGESWORD_DAMAGE		50.f			//大剣のダメージ
#define LARGESWORD_KNOCKBACK	7.f				//大剣のノックバックの量

class CharaBase;
class Player;

class LargeSword :public LineCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度

	bool isShow;			//表示させる？
	bool isHit;				//当たったか？

public:
	//コンストラクタ
	LargeSword();

	//デストラクタ
	~LargeSword();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

public:
	//当たったかどうか取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

};

