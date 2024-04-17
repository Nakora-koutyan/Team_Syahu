#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"
#include"Weapon/Steal.h"

#define PLAYER_MOVE_SPEED				3.f				//移動移動
#define PLAYER_MAX_MOVE_SPEED			9.f				//最高速度
#define PLAYER_DAMAGE_INTERVAL			FPS * 1			//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_DAMAGE_CUT				1.f - 0.25f		//ガード中のダメージ
#define PLAYER_PARRY_FLAME				4				//パリィの猶予フレーム
#define PLAYER_PARRY_TIME				FPS * 2			//パリィの効果時間
#define	PLAYER_GUARD_COOLTIME			FPS * 0.4		//ガードのクールタイム
#define PLAYER_NORMALWEAPON_COOLTIME	FPS * 1.f		//通常攻撃のクールタイム
#define PLAYER_STEAL_COOLTIME			FPS * 1.2f		//奪うのクールタイム
#define PLAYER_KNOCKBACK				7.f				//ノックバックの移動距離/f
#define PLAYER_KNOCKBACK_TIME			FPS * 0.25		//ノックバックの時間
#define PLAYER_ABILITY_TIME				FPS * 5			//奪った能力の使用時間

class Player :public CharaBase
{
private:
	NormalWeapon* normalWeapon;		//投げる
	Steal* steal;					//奪う

	short guardCount;				//ガードのカウント	0:していない 1:していた

	int damageFramCount;			//ダメージを受けた時のカウント
	int parryFram;					//パリィの入力フレーム
	int abilityFramCount;			//能力のカウント用

	float guardCoolTime;			//ガードのクールタイム
	float normalWeaponCoolTime;		//通常攻撃のクールタイム
	float stealCoolTime;			//奪うのクールタイム

	bool isGuard;					//ガード中？
	bool stealFlg;					//奪った？
	bool isEquipment;				//装備中？
	bool guardCoolTimeFlg;			//ガードのクールタイムのフラグ
	bool parryFlg;					//パリィフラグ

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update();

	//描画
	void Draw()const;

	//ヒット処理
	void Hit(CharaBase* chara);

public:
	//投げるを取得
	NormalWeapon* GetNormalWeapon()const { return normalWeapon; }

	//奪うを取得
	Steal* GetSteal()const { return steal; }

	//パリィフラグを取得
	bool GetParryFlg()const { return parryFlg; }

	//奪ったかどうかを取得
	bool GetStealFlg()const { return stealFlg; }

	//奪ったかどうかを設定
	void SetStealFlg(const bool flg) { stealFlg = flg; }

private:
	//移動
	void Movement();

	//攻撃
	void Attack();

	//ガード
	void Guard();

	//ダメージ
	void Damage(CharaBase* chara);

};
