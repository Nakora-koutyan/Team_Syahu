#pragma once
#include "../../../../Collision/Line/LineCollision.h"

#define RAPIER_ATTACK_TIME				FPS * 0.4		//レイピア攻撃の時間
#define RAPIER_CHARGE_TIME				FPS * 0.2		//レイピアの溜め時間
#define RAPIER_MOVE						15.5f			//レイピアの移動量/f
#define RAPIER_AIR_MOVE					12.5f			//レイピアの空中での移動量/f
#define RAPIER_LENGTH					100.f			//レイピアの長さ
#define RAPIER_WEIGHT					0.35f			//レイピアの重さ
#define RAPIER_DAMAGE					50.f			//レイピアのダメージ
#define RAPIER_KNOCKBACK				0.f				//レイピアのノックバックの量
#define RAPIER_AIR_ATTAK_KNOCKBACK		5.f				//レイピアの空中攻撃のノックバックの量

class CharaBase;
class Player;

class Rapier :public LineCollision
{
private:
	Vector2D effectLocation;			//エフェクト座標
	Vector2D airAttackEffectLocation;	//空中攻撃のエフェクトの座標

	short direction;					//方向

	int framCount;						//フレームカウント
	int chargeTime;						//溜める時間
	int effectAnim;						//エフェクトのアニメーション番号
	int effectAnimcount;				//エフェクトのアニメーションカウント
	int airAttackEffectAnim;			//落下攻撃エフェクトのアニメーション番号
	int airAttackEffectAnimcount;		//落下攻撃エフェクトのアニメーションカウント

	float angle;						//角度
	float imageAngle;					//画像の角度
	float dis;							//距離
	float length;						//長さ

	bool isHit;							//当たったか？
	bool isUnable;						//当たり判定ができない？
	bool stepFlg;						//飛ばす？
	bool isAirAttack;					//空中攻撃？
	bool airAttackAnimFlg;				//空中攻撃のアニメーションフラグ

public:
	//コンストラクタ
	Rapier();

	//デストラクタ
	~Rapier();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

public:
	//溜める時間を取得
	int GetChargeTime()const { return chargeTime; }

	//当たったかどうか取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

	//飛ばすかどうかを取得
	bool GetStepFlg()const { return stepFlg; }

	//飛ばすかどうかを設定
	void SetStepFlg(const bool flg) { stepFlg = flg; }

	//空中攻撃かどうかを取得
	bool GetIsAirAttack()const { return isAirAttack; }

};

