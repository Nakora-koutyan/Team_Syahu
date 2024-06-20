#pragma once
#include"../../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//スティックの傾き割合
#define GRAVITY				0.8f		//重力
#define JUMP_POWER			20.f		//ジャンプ力

enum class Weapon
{
	None = 0,			//空
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

	short knockBackDirection;	//ノックバックの方向

	int framCount;				//フレーム計測用
	int knockBackCount;			//ノックバック用のカウント
	int alphaBlend;				//画像の透明値

	float hp;					//HP
	float knockBackMove;		//ノックバックの移動量

	bool isAir;					//空中？
	bool isJump;				//ジャンプしている？
	bool isMove;				//移動している？
	bool isHit;					//当たっている？
	bool isAttack;				//攻撃中？
	bool isKnockBack;			//ノックバックする？
	bool imageInversionFlg;		//画像反転フラグ
	bool deathFlg;				//死亡フラグ
	bool invincibleFlg;			//無敵フラグ
	bool hitBlockFlg;			//ブロックにヒットした？

public:
	//コンストラクタ
	CharaBase();

	//デストラクタ
	~CharaBase();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//着地
	virtual void Landing(const float height);

	//移動の更新処理
	void MovementUpdate();

public:
	//ノックバックカウントを取得
	int GetKnockBackCount()const { return knockBackCount; }

	//ノックバックカウントを設定
	void SetKnockBackCount(const int time) { knockBackCount = time; }

	//HPを取得
	float GetHp()const { return hp; }

	//HPを設定
	void SetHp(const float hp) { this->hp = hp; }

	//ノックバックの移動量を取得
	float GetKnockBackMove()const { return knockBackMove; }

	//ノックバックの移動量を設定
	void SetKnockBackMove(const float x) { knockBackMove = x; }

	//空中かどうかを取得
	bool GetIsAir()const { return isAir; }

	//当たっているかどうかを取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

	//攻撃中かどうかを取得
	bool GetIsAttack()const { return isAttack; }

	//攻撃中かどうかを設定
	void SetIsAttack(const bool flg) { isAttack = flg; }

	//ノックバックフラグを取得
	bool GetIsKnockBack()const { return isKnockBack; }

	//ノックバックフラグを設定
	void SetIsKnockBack(const bool flg) { isKnockBack = flg; }

	//死亡フラグを取得
	bool GetDeathFlg()const { return deathFlg; }

	//無敵フラグを取得
	bool GetInvincibleFlg()const { return invincibleFlg; }

	//無敵フラグを設定
	void SetInvincibleFlg(const bool flg) { invincibleFlg = flg; }

	//ブロックにヒットしたかどうか取得
	bool GetHitBlockFlg()const { return hitBlockFlg; }

	//ブロックにヒットしたかどうか設定
	void SetHitBlockFlg(const bool flg) { hitBlockFlg = flg; }

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
	void DamageInterval(const double interval);

	//ノックバック処理
	void KnockBack(const CharaBase* chara, const double time, const float x);

	//重力処理
	void Gravity();

};