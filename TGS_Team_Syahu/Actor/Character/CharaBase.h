#pragma once
#include"../../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//スティックの傾き割合
#define GRAVITY				0.8f		//重力
#define JUMP_POWER			20.f		//ジャンプ力

enum class Weapon
{
	Empty = 0,			//空
	LargeSword,			//大剣
	Dagger,				//ダガー
	Rapier				//レイピア
};

class CharaBase :public BoxCollision
{
protected:
	Vector2D move;				//移動量
	Vector2D direction;			//方向

	Weapon weaponType;			//武器の種類

	int framCount;				//フレーム計測用
	int knockBackCount;			//ノックバック用のカウント

	float hp;					//HP
	float damage;				//ダメージ

	bool isAir;					//空中？
	bool isJump;				//ジャンプしている？
	int alphaBlend;				//画像の透明値

	bool isMove;				//移動している？
	bool isHit;					//当たっている？
	bool isShow;				//表示する？
	bool isAttack;				//攻撃中？
	bool isKnockBack;			//ノックバックする？
	bool imageInversionFlg;		//画像反転フラグ

public:
	//コンストラクタ
	CharaBase();

	//デストラクタ
	~CharaBase();

public:
	//HPを取得
	float GetHp()const { return hp; }

	//HPを設定
	void SetHp(const float hp) { this->hp = hp; }

	//ダメージを取得
	float GetDamage()const { return damage; }

	//当たっているかどうかを取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }

	//表示フラグを設定
	void SetIsShow(const bool flg) { isShow = flg; }

	//攻撃中かどうかを取得
	bool GetIsAttack()const { return isAttack; }

	//攻撃中かどうかを設定
	void SetIsAttack(const bool flg) { isAttack = flg; }

	//ノックバックフラグを取得
	bool GetIsKnockBack()const { return isKnockBack; }

	//ノックバックフラグを設定
	void SetIsKnockBack(const bool flg) { isKnockBack = flg; }

	//移動量の取得
	Vector2D GetMove()const { return move; }

	//移動量の設定
	void SetMove(const Vector2D move) { this->move.x = move.x, this->move.y = move.y; }

	//方向の取得
	Vector2D GetDirection()const { return direction; }

	//武器の種類を取得
	Weapon GetWeaponType()const { return weaponType; }

	//武器の種類を設定
	void SetWeaponType(const Weapon ability) { weaponType = ability; }

protected:
	//ダメージのインターバル処理
	void DamageInterval(const int interval);

	//ノックバック処理
	void KnockBack(const double time);

};