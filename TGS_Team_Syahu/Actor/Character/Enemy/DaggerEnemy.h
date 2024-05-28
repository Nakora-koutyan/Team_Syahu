#pragma once
#include "EnemyBase.h"

#define DAGGER_ENEMY_WALK_SPEED		2.5f
#define DAGGER_ENEMY_KNOCKBACK		1.5f

class DaggerEnemy :public EnemyBase
{
private:

	int daggerEnemyAnimNumber;
	int daggerEnemyAnim[60];

	int enemyAnimInterval;
	
	Dagger* dagger;			//短剣を呼び出す

	bool drawnSword;		//抜刀した？

	float correctLocX;		//画像の位置ずれを修正するための変数(X)
	float correctLocY;		//画像の位置ずれを修正するための変数(Y)

	int animTurnFlg;		//画像の反転処理

public:
	//コンストラクタ
	DaggerEnemy();
	//デストラクタ
	~DaggerEnemy();

	//初期化処理
	void Initialize();

	//更新に関する処理
	void Update()override;

	//描画に関する処理
	void Draw()const override;

	//Playerを見つけたか？
	void FindPlayer(const Player* player)override;

public:
	Dagger* GetDagger()const { return dagger; }

	//エネミーのアニメーション制御関数
	void EnemyAnimationManager() override;

	//パトロール関数
	void EnemyPatrol() override;

	void HitWeapon(ObjectBase* object)override;

protected:
	//攻撃範囲関数
	void AttackRange()override;

	//武器ありの場合に呼び出される関数
	//攻撃準備
	void AttackStandBy() override;

	//攻撃開始
	void AttackStart() override;

	//攻撃終了
	void AttackEnd() override;

protected:
	//ステータスアニメーション用関数
	//パトロールアニメーション
	void PatrolAnim();

	//攻撃準備アニメーション
	void DaggerAttackStandByAnim();
	void WeaponNoneAttackStandByAnim();

	//攻撃開始アニメーション
	void DaggerAttackStartAnim();
	void WeaponNoneAttackStartAnim();

	//攻撃終了
	void DaggerAttackEndAnim();
	void WeaponNoneAttackEndAnim();
};

