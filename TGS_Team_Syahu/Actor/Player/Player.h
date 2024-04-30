#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"
#include"Weapon/Steal.h"
#include"Weapon/LargeSword.h"

#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_X	31.f			//画像の原点調整用x
#define PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y	48.f			//画像の原点調整用y
#define PLAYER_MOVE_SPEED				3.f				//移動移動
#define PLAYER_MAX_MOVE_SPEED			9.f				//最高速度
#define PLAYER_DAMAGE_INTERVAL			FPS * 1.0		//プレイヤーが再度ダメージを受けるまでの時間
#define PLAYER_NORMALWEAPON_COOLTIME	FPS * 1.f		//投げるのクールタイム
#define PLAYER_STEAL_COOLTIME			FPS * 1.2f		//奪うのクールタイム
#define PLAYER_LARGESWORD_COOLTIME		FPS * 1.7f		//大剣のクールタイム
#define PLAYER_KNOCKBACK				5.f				//ノックバックの移動距離/f
#define PLAYER_KNOCKBACK_TIME			FPS * 0.25		//ノックバックの時間
#define PLAYER_WEAPON_TIME				FPS * 30		//武器の使用時間
#define PLAYER_MAX_STOCK				5				//最大ストック数
#define STEAL_VALUE						3				//奪うの数
#define STEAL_DISTANCE					25.f			//プレイヤーから奪うを出す距離
#define LARGESWORD_DISTANCE				20				//プレイヤーから大剣を離す距離
#define LARGESWORD_WEIGHT				0.75f			//大剣の重さ
#define LARGESWORD_DAMAGE				5.f				//大剣のダメージ
#define DAGGER_WEIGHT					0.05f			//ダガーの重さ
#define DAGGER_DAMAGE					1.5f			//ダガーのダメージ
#define RAPIER_WEIGHT					0.35f			//レイピアの重さ
#define RAPIER_DAMAGE					3.f				//レイピアのダメージ

class Player :public CharaBase
{
private:
	Weapon stock[PLAYER_MAX_STOCK];			//ストック
	NormalWeapon* normalWeapon;				//投げる
	Steal* steal[STEAL_VALUE];				//奪う
	LargeSword* largeSword;					//大剣

	short stockCount;						//現在のストックの番号
	short actionCount;						//行動のカウント 0:なし 1:奪う 2:武器 3:投げる 4:装備

	int damageFramCount;					//ダメージを受けた時のフレームカウント
	int weaponFramCount[PLAYER_MAX_STOCK];	//武器のフレームカウント
	int playerAnimFramCount;				//プレイヤーのアニメーションフレームカウント
	int playerAnim;							//プレイヤーのアニメーション番号
	int playerImage[50] = {};				//プレイヤー画像

	float attackCoolTime;					//攻撃のクールタイム
	float stealCoolTime;					//奪うのクールタイム

	bool isEquipment;						//装備中？
	bool landingAnimFlg;					//着地アニメーションフラグ

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
	//投げるを取得
	NormalWeapon* GetNormalWeapon()const { return normalWeapon; }

	//奪うを取得
	Steal* GetSteal(const int element)const { return steal[element]; }

	//大剣を取得
	LargeSword* GetLargeSword()const { return largeSword; }

public:
	//行動カウントを取得
	short GetActionCount()const { return actionCount; }

	//行動カウントを設定
	void SetActionCount(const short cnt) { actionCount = cnt; }

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
