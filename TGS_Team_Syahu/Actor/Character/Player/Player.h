#pragma once
#include"../CharaBase.h"
#include"Weapon/Steal.h"
#include"Weapon/LargeSword.h"
#include"Weapon/Dagger.h"
#include"Weapon/Rapier.h"
#include<vector>

#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_X	31.f			//画像の原点調整用x
#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y	48.f			//画像の原点調整用y
#ifdef DEBUG
#define PLAYER_MOVE_SPEED				5.0f			//移動移動
#define PLAYER_AIR_MOVE_SPEED			1.0f			//空中移動移動
#define PLAYER_MAX_MOVE_SPEED			15.f			//最高速度
#else
#define PLAYER_MOVE_SPEED				1.0f			//移動移動
#define PLAYER_AIR_MOVE_SPEED			0.1f			//空中移動移動
#define PLAYER_MAX_MOVE_SPEED			9.f				//最高速度
#endif // DEBUG
#define PLAYER_MAX_HP					100.f			//最大HP
#define PLAYER_DAMAGE					5.f				//プレイヤーの基礎ダメージ値
#define PLAYER_DAMAGE_INTERVAL			FPS * 1.0		//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_NORMALWEAPON_COOLTIME	FPS * 1.f		//投げるのクールタイム
#define PLAYER_STEAL_COOLTIME			FPS * 1.2f		//奪うのクールタイム
#define PLAYER_LARGESWORD_COOLTIME		FPS * 1.5f		//大剣のクールタイム
#define PLAYER_DAGGER_COOLTIME			FPS * 0.3f		//短剣のクールタイム
#define PLAYER_RAPIER_COOLTIME			FPS * 1.0f		//レイピアのクールタイム
#define PLAYER_KNOCKBACK				5.f				//ノックバックの量
#define PLAYER_KNOCKBACK_TIME			FPS * 0.25		//ノックバックの時間
#define PLAYER_WEAPON_DURABILITY		100				//武器の耐久力
#define PLAYER_MAX_STOCK				5				//最大ストック数
#define PLAYER_MAX_DAGGER				6				//短剣の最大数
#define WEAPON_DISTANCE					10				//プレイヤーから武器を離す距離

enum class Action
{
	None = 0,		//なし
	Steal,			//奪う
	WeaponAttack,	//武器攻撃
	Equipment		//装備
};

class Player :public CharaBase
{
private:
	std::vector<ObjectBase*>weapon;				//武器
	
	Weapon stock[PLAYER_MAX_STOCK];				//ストック
	Action actionState;							//行動状態

	Steal* steal;								//奪う
	LargeSword* largeSword;						//大剣
	Dagger* dagger[PLAYER_MAX_DAGGER];			//短剣
	Rapier* rapier;								//レイピア

	Vector2D jumpEffectLocation;				//ジャンプのエフェクト座標

	short stockCount;							//現在のストックの番号
	short jumpCount;							//ジャンプのカウント

	int weaponDurability[PLAYER_MAX_STOCK];		//武器の耐久値
	int playerAnimFramCount;					//プレイヤーのアニメーションフレームカウント
	int playerAnim;								//プレイヤーのアニメーション番号
	int playerImage[50] = {};					//プレイヤー画像
	int daggerCount[PLAYER_MAX_DAGGER];			//短剣の本数
	int jumpEffectAnimCount;					//ジャンプのエフェクトのアニメーションカウント
	int jumpEffectAnim;							//ジャンプのエフェクトのアニメーション番号
	int equipmentEffectAnimCount;				//装備のエフェクトアニメーションカウント
	int equipmentEffectAnim;					//装備のエフェクトアニメーション番号

	float attackCoolTime;						//攻撃のクールタイム
	float stealCoolTime;						//奪うのクールタイム

	bool isEquipment;							//装備中？
	bool isBackStep;							//バックステップ中？
	bool landingAnimFlg;						//着地アニメーションフラグ
	bool blinkingFlg;							//点滅フラグ
	bool jumpEffectInversionFlg;				//ジャンプのエフェクト反転フラグ
	bool jumpEffectLandFlg;						//ジャンプのエフェクトの地上フラグ
	bool equipmentAnimFlg;						//装備アニメーションフラグ
	bool equipmentEffectFlg;					//装備エフェクトフラグ

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override;

	//着地
	void Landing(const float height)override;

public:
	//ストックを取得
	Weapon GetStock(const int element)const { return stock[element]; }

	//奪うを取得
	Steal* GetSteal()const { return steal; }

	//短剣を取得
	Dagger* GetDagger(const int element)const  { return dagger[element]; }

	//武器を取得
	ObjectBase* GetWeapon(const int element)const { return weapon[element]; }

	//武器の数を取得
	size_t GetWeaponSize()const { return weapon.size(); }

public:
	//ストックの番号を取得
	short GetStockCount()const { return stockCount; }

	//武器の耐久値を取得
	int GetWeaponDurability(const int element)const { return weaponDurability[element]; }

	//短剣の本数を取得
	int GetDaggerCount(const int element)const { return daggerCount[element]; }

	//装備中かどうか取得
	bool GetIsEquipment()const { return isEquipment; }

	//装備のアニメーションフラグを取得
	bool GetEquipmentAnimFlg()const { return equipmentAnimFlg; }

	bool GetIsBackStep()const { return isBackStep; }

private:
	//移動
	void Movement();

	//攻撃
	void Attack();

	//ストックの選択
	void StockSelect();

	//アニメーション
	void Animation();

	//バックステップ
	void BackStep(const float angle, const float speed, const float gravityVelocity);

private:
	//武器の耐久力を取得
	int GetDurability(const Weapon type, const bool useFlg = false);

};
