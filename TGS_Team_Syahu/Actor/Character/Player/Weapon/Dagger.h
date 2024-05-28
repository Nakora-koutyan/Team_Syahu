#pragma once
#include"../../../../Collision/Line/LineCollision.h"

#define DAGGER_ATTACK_TIME	FPS * 0.1		//短剣攻撃の時間
#define DAGGER_ANGLE		5.5f			//短剣の振る角度/f
#define DAGGER_LENGTH		75.f			//短剣の長さ
#define DAGGER_SPEED		20.f			//短剣の速さ
#define DAGGER_WEIGHT		0.05f			//ダガーの重さ
#define DAGGER_DAMAGE		40.f			//ダガーのダメージ
#define DAGGER_KNOCKBACK	3.f				//短剣のノックバックの量

class CharaBase;
class Player;

class Dagger :public LineCollision
{
private:
	Vector2D move;			//移動量

	short direction;		//方向

	int framCount;			//フレームカウント

	float imageAngle;		//画像の角度

	bool isHit;				//当たったか？
	bool isAirAttack;		//空中攻撃？
	bool attackEndFlg;		//攻撃終了フラグ

public:
	//コンストラクタ
	Dagger();

	//デストラクタ
	~Dagger();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

	//初期化
	void Init();

public:
	//当たったかどうか取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

};

