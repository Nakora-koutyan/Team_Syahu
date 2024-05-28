#pragma once
#include"EnemyBase.h"

#define NORMAL_WALK_SPEED 0.5f			//徘徊時のスピード
#define ATTACK_SPEED 10.f				//攻撃時のスピード

class Player;

class NormalEnemy :public EnemyBase
{
private:
	int enemyImage[6];	//敵画像
	int enemyNumber;	//画像番号
	int animInterval;	//画像のインターバル
	bool animCountDown;	//画像インターバルのカウントダウン
	bool animTurnFlg;	//アニメーションを左右反転する？(yes：true,no：false)

	int attackTime;		//攻撃時間

	bool once;

public:
	//コンストラクタ
	NormalEnemy();
	//デストラクタ
	~NormalEnemy();

	//初期化処理
	void Initialize();
	//更新処理
	void Update()override;
	//描画更新処理
	void Draw()const override;

public:

	//プレイヤーを見つけた？
	void FindPlayer(const Player* player)override;

	void HitWeapon(ObjectBase* object)override;

private:
	//攻撃範囲関数
	void AttackRange()override;

	//エネミーのアニメーション制御関数
	void EnemyAnimationManager() override;

	//パトロール関数
	void EnemyPatrol() override;

	//追跡を行うか？
	void AttackStandBy() override;

	//攻撃を行うか？
	void AttackStart() override;

	void AttackEnd() override;
};