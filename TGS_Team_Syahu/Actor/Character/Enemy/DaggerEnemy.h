#pragma once
#include "EnemyBase.h"

#define DAGGER_ENEMY_WALK_SPEED		2.5f

class DaggerEnemy :public EnemyBase
{
private:

	Dagger* dagger;			//短剣を呼び出す

	bool drawnSword;		//抜刀した？

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

protected:
	//エネミーのアニメーション制御関数
	void EnemyAnimationManager() override;

	//パトロール関数
	void EnemyPatrol() override;

protected:
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

