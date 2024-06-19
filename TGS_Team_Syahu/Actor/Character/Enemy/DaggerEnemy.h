#pragma once
#include "EnemyBase.h"

#define DAGGER_ENEMY_WALK_SPEED		1.5f
#define DAGGER_ENEMY_KNOCKBACK		1.5f

class DaggerEnemy :public EnemyBase
{
private:

	//かぎづめ攻撃の当たり判定専用のコリジョンボックス
	BoxCollision* clawCollisionBox;

	int daggerEnemyAnimNumber;
	int daggerEnemyAnim[60];

	int enemyAnimInterval;
	
	Dagger* dagger;			//短剣を呼び出す

	bool drawnSword;		//抜刀した？

	float correctLocX;		//画像の位置ずれを修正するための変数(X)
	float correctLocY;		//画像の位置ずれを修正するための変数(Y)

	int animTurnFlg;		//画像の反転処理

	bool animCountDown;		//アニメーションの番号の減算をする？

	int attackEndCount;		//攻撃終了時アニメーション関数で使用するカウンター

	bool canAttack;			//攻撃できる？

	bool didAttack;			//攻撃した？


	bool onlyOnce;			//死亡時アニメーションに一度だけ呼ばれる
	float locYCorrect;		//画像座標修正用変数

public:
	//コンストラクタ
	DaggerEnemy(float x, float y);
	//デストラクタ
	~DaggerEnemy();

	//初期化処理
	void Initialize()override;

	//終了時の消去処理
	void Finalize()override;

	//更新に関する処理
	void Update()override;

	//描画に関する処理
	void Draw()const override;

	//Playerを見つけたか？
	void FindPlayer(const Player* player)override;

	void SuddenApproachToPlayer(const Player* player);

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

	//攻撃準備
	void AttackStandBy() override;

	//攻撃開始
	void AttackStart() override;

	//攻撃終了
	void AttackEnd() override;

	//死亡時
	void Death() override;

	//ダメージを受けた時
	void Damage()override;

protected:
	/* ステータスアニメーション用関数 */
	//パトロールアニメーション
	void PatrolAnim();

	//攻撃準備アニメーション
	void DaggerEnemyAttackStandByAnim();
	void WeaponNoneAttackStandByAnim();

	//攻撃開始アニメーション
	void DaggerAttackStartAnim();
	void WeaponNoneAttackStartAnim();

	//攻撃終了
	void DaggerAttackEndAnim();
	
	//死亡時のアニメーション
	void DaggerEnemyDeathAnim();

	//ダメージを受けた時
	void DaggerEnemyDamageAnim();
};

