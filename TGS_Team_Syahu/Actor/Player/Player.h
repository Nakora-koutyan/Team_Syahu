#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"

#define PLAYER_MOVE_SPEED		3.f				//プレイヤーの移動速度
#define PLAYER_MAX_MOVE_SPEED	9.f				//プレイヤーの最高移動速度
#define PLAYER_DAMAGE_INTERVAL	FPS * 1			//ダメージ受けたときに再度ダメージを受けるまでの時間
#define PLAYER_DAMAGE_CUT		1.f - 0.25f		//ガードした時のダメージカット率
#define PLAYER_PARRY_FLAME		10				//パリィの猶予フレーム

class Player :public CharaBase
{
private:
	Ability weaponSlot1;		//武器スロット1
	Ability weaponSlot2;		//武器スロット2
	NormalWeapon* normalWeapon;	//通常攻撃

	int framCount;				//フレームカウント
	int damageFramCount;		//ダメージ用のカウント
	int parryFram;				//パリィ用のカウント

	float damageInterval;		//ダメージのインターバル

	bool isGuard;				//ガードしている？
	bool parryFlg;				//パリィのフラグ

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

	//当たり判定の処理
	void Hit(GameMainScene* object);

private:
	//移動
	void Movement();

	//アクション
	void Action();

};

