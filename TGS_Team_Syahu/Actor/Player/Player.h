#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"
#include"Weapon/Steal.h"

#define PLAYER_MOVE_SPEED				3.f				//移動移動
#define PLAYER_MAX_MOVE_SPEED			9.f				//最高速度
#define PLAYER_DAMAGE_INTERVAL			FPS * 1			//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_DAMAGE_CUT				1.f - 0.25f		//ガード中のダメージ
#define PLAYER_PARRY_FLAME				4				//パリィの猶予フレーム
#define	PLAYER_GUARD_COOLTIME			FPS * 0.4		//ガードのクールタイム
#define PLAYER_NORMALWEAPON_COOLTIME	FPS * 1.f		//通常攻撃のクールタイム
#define PLAYER_STEAL_COOLTIME			FPS * 1.2f		//奪うのクールタイム
#define PLAYER_KNOCKBACK				35.f				//ノックバック

class Player :public CharaBase
{
private:
	NormalWeapon* normalWeapon;		//通常攻撃
	Steal* steal;					//奪う

	short guardCount;				//ガードのカウント	0:していない 1:していた

	int damageFramCount;			//ダメージを受けた時のカウント
	int parryFram;					//パリィの入力フレーム

	float guardCoolTime;			//ガードのクールタイム
	float normalWeaponCoolTime;		//通常攻撃のクールタイム
	float stealCoolTime;			//奪うのクールタイム

	bool isGuard;					//ガード中？
	bool isSteal;					//奪うをした？
	bool guardCoolTimeFlg;			//ガードのクールタイムのフラグ
	bool parryFlg;					//パリィフラグ

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

public:
	//パリィフラグを取得
	bool GetParryFlg()const { return parryFlg; }


private:
	//当たり判定
	void Hit(GameMainScene* object);

	//移動
	void Movement();

	//攻撃
	void Attack();

	//ガード
	void Guard();

	//ダメージ
	void Damage(GameMainScene* object);

};
