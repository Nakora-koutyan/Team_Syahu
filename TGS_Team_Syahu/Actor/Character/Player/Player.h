#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"
#include"Weapon/Steal.h"
#include"Weapon/LargeSword.h"
#include"Weapon/Dagger.h"
#include"Weapon/Rapier.h"

#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_X	31.f			//画像の原点調整用x
#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y	48.f			//画像の原点調整用y
#define PLAYER_MOVE_SPEED				1.0f			//移動移動
#define PLAYER_AIR_MOVE_SPEED			0.1f			//空中移動移動
#define PLAYER_MAX_MOVE_SPEED			9.f				//最高速度
#define PLAYER_MAX_HP					100.f			//最大HP
#define PLAYER_DAMAGE_INTERVAL			FPS * 1.0		//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_NORMALWEAPON_COOLTIME	FPS * 1.f		//投げるのクールタイム
#define PLAYER_STEAL_COOLTIME			FPS * 1.2f		//奪うのクールタイム
#define PLAYER_LARGESWORD_COOLTIME		FPS * 1.7f		//大剣のクールタイム
#define PLAYER_DAGGER_COOLTIME			FPS * 0.5f		//短剣のクールタイム
#define PLAYER_RAPIER_COOLTIME			FPS * 1.2f		//短剣のクールタイム
#define PLAYER_KNOCKBACK				5.f				//ノックバックの移動距離/f
#define PLAYER_KNOCKBACK_TIME			FPS * 0.25		//ノックバックの時間
#define PLAYER_WEAPON_TIME				FPS * 30		//武器の使用時間
#define PLAYER_MAX_STOCK				5				//最大ストック数
#define WEAPON_DISTANCE					20				//プレイヤーから武器を離す距離

enum class Action
{
	None = 0,		//なし
	Steal,			//奪う
	WeaponAttack,	//武器攻撃
	Throw,			//投げる
	Equipment		//装備
};

class Player :public CharaBase
{
private:
	Weapon stock[PLAYER_MAX_STOCK];			//ストック
	Action actionState;						//行動状態

	NormalWeapon* normalWeapon;				//投げる
	Steal* steal;							//奪う
	LargeSword* largeSword;					//大剣
	Dagger* dagger;							//短剣
	Rapier* rapier;							//レイピア

	short stockCount;						//現在のストックの番号

	int weaponFramCount[PLAYER_MAX_STOCK];	//武器のフレームカウント
	int playerAnimFramCount;				//プレイヤーのアニメーションフレームカウント
	int playerAnim;							//プレイヤーのアニメーション番号
	int playerImage[50] = {};				//プレイヤー画像

	float attackCoolTime;					//攻撃のクールタイム
	float stealCoolTime;					//奪うのクールタイム

	bool isEquipment;						//装備中？
	bool landingAnimFlg;					//着地アニメーションフラグ
	bool blinkingFlg;						//点滅フラグ

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

	//着地
	void Landing(const float height);

public:
	//ストックを取得
	Weapon GetStock(const int element)const { return stock[element]; }

	//投げるを取得
	NormalWeapon* GetNormalWeapon()const { return normalWeapon; }

	//奪うを取得
	Steal* GetSteal()const { return steal; }

	//大剣を取得
	LargeSword* GetLargeSword()const { return largeSword; }

	//短剣を取得
	Dagger* GetDagger()const { return dagger; }

	//レイピアを取得
	Rapier* GetRapier()const { return rapier; }

public:
	//ストックの番号を取得
	short GetStockCount()const { return stockCount; }

	//装備中かどうか取得
	bool GetIsEquipment()const { return isEquipment; }

private:
	//移動
	void Movement();

	//攻撃
	void Attack();

	//ストックの選択
	void StockSelect();

	//アニメーション
	void Animation();

private:
	//武器の重さを取得
	float GetWeaponWeight(const Weapon type);

	//武器のダメージを取得
	float GetWeaponDamage(const Weapon type);
};
