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
	float weaponKnockBack;	//武器のノックバック量

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	NormalWeapon();

	//デストラクタ
	~NormalWeapon();

	//初期化処理
	void Initialize()override;

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara, const float weight, const float damage,const float x);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }
};

