#pragma once
#include"../../../../Collision/Line/LineCollision.h"

#define LARGESWORD_ATTACK_TIME	FPS * 0.15		//大剣攻撃の時間
#define LARGESWORD_ANGLE		11.5f			//大剣の振る角度/f
#define LARGRSWORD_LENGTH		100.f			//大剣の長さ
#define LARGESWORD_WEIGHT		0.75f			//大剣の重さ
#define LARGESWORD_DAMAGE		100.f			//大剣のダメージ
#define LARGESWORD_FALL_SPEED	15.5f			//大剣の落下速度
#define LARGESWORD_KNOCKBACK	7.f				//大剣のノックバックの量

class CharaBase;
class Player;

class LargeSword :public LineCollision
{
private:
	Vector2D airAttackEffectLocation;	//空中攻撃のエフェクトの座標

	short direction;					//方向

	int framCount;						//フレームカウント
	int effectAnim;						//エフェクトのアニメーション番号
	int effectAnimcount;				//エフェクトのアニメーションカウント
	int airAttackEffectAnim;			//落下攻撃エフェクトのアニメーション番号
	int airAttackEffectAnimcount;		//落下攻撃エフェクトのアニメーションカウント

	float angle;						//角度
	float imageAngle;					//画像の角度

	bool isHit;							//当たったか？
	bool isAirAttack;					//空中攻撃？
	bool airAttackAnimFlg;				//空中攻撃のアニメーションフラグ

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
	void Attack(CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

public:
	//当たったかどうか取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

	//空中攻撃かどうかを取得
	bool GetIsAirAttack()const { return isAirAttack; }

};

