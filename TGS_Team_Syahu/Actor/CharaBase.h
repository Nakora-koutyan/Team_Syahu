#pragma once
#include"../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//必要なスティックの傾き割合
#define MAX_SPEED			10.f		//最高速度	
#define GRAVITY				0.8f		//落下速度
#define JUMP_POWER			15.f		//ジャンプ力

enum class Ability
{
	Empty = 0,			//空
	Slashing			//斬撃
};

class GameMainScene;

class CharaBase :public BoxCollision
{
protected:
	Vector2D vector;			//移動量
	Vector2D direction;			//方向

	Ability abilityType;		//能力の種類

	float hp;					//HP
	float damage;				//ダメージ

	bool isAir;					//空中？
	bool isHit;					//当たった？
	bool isShow;				//表示する？
	bool isAttack;				//攻撃判定

public:
	//コンストラクタ
	CharaBase();

	//デストラクタ
	~CharaBase();

	//更新
	virtual void Update(GameMainScene* object) = 0;

	//描画
	virtual void Draw()const = 0;

	//HPを取得
	float GetHp()const { return hp; }

	//ダメージを取得
	float GetDamage()const { return damage; }

	//攻撃判定を取得
	bool GetIsAttack()const { return isAttack; }

	//攻撃判定を設定
	void SetIsAttack(const bool flg) { isAttack = flg; }

	//方向を取得
	Vector2D GetDirection()const { return direction; }

protected:
	//能力の種類を取得
	Ability GetAbilityType() { return abilityType; }
	
};
