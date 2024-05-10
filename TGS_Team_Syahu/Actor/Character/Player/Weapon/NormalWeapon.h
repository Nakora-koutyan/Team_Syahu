#pragma once
#include"../../../../Collision/Sphere/SphereCollision.h"

#define NORMAL_WEAPON_ATTACK_TIME	FPS * 5.5f		//通常攻撃の時間
#define NORMAL_WEAPON_SPEED			20.f			//弾の速さ
#define NORMAL_WEAPON_GRAVITY		0.09f			//弾の重力

class CharaBase;
class Player;

class NormalWeapon :public SphereCollision
{
private:
	Vector2D move;			//移動量

	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度
	float gravityVelocity;	//重力速度
	float weaponWeight;		//武器の重さ
	float weaponDamage;		//武器のダメージ

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	NormalWeapon();

	//デストラクタ
	~NormalWeapon();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//出現
	void Appearance(Player* player);

	//攻撃
	void Attack(const Player* player, const float weight, const float damage);

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override;

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }
};

