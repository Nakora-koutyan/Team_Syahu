#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"

#define PLAYER_MOVE_SPEED		3.f				//移動移動
#define PLAYER_MAX_MOVE_SPEED	9.f				//最高速度
#define PLAYER_DAMAGE_INTERVAL	FPS * 1			//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_DAMAGE_CUT		1.f - 0.25f		//ガード中のダメージ
#define PLAYER_PARRY_FLAME		10				//パリィの猶予フレーム
#define	PLAYER_GUARD_COOLTIME	FPS * 0.4		//ガードのクールタイム

class Player :public CharaBase
{
private:
	Ability weaponSlot;			//武器スロット
	NormalWeapon* normalWeapon;	//通常攻撃

	short guardCount;			//ガードのカウント	0:していない 1:していた

	int framCount;				//フレームカウント
	int damageFramCount;		//ダメージを受けた時のカウント
	int parryFram;				//パリィの入力フレーム

	float guardCoolTime;		//ガードのクールタイム

	bool isGuard;				//ガード中？
	bool guardCoolTimeFlg;		//ガードのクールタイムのフラグ
	bool parryFlg;				//パリィフラグ

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

	//ダメージ処理
	void Hit(GameMainScene* object);

private:
	//移動
	void Movement();

	//アクション
	void Action();

};
