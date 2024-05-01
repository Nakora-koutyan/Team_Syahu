#pragma once
#include"EnemyBase.h"

#define NORMAL_WALK_SPEED 1.f			//徘徊時のスピード
#define CHASE_SPEED 2.f					//追跡時のスピード
#define ATTACK_SPEED 10.f				//攻撃時のスピード

#define DIRECTION_LEFT 0				//左向き
#define DIRECTION_RIGHT 1				//右向き

class Player;

class NormalEnemy :public EnemyBase
{
private:
	int enemyImage[6];	//敵画像
	int enemyNumber;	//画像番号
	int animInterval;	//画像のインターバル
	bool animCountDown;	//画像インターバルのカウントダウン
	bool animTurnFlg;	//アニメーションを左右反転する？(yes：true,no：false)

public:
	//コンストラクタ
	NormalEnemy();
	//デストラクタ
	~NormalEnemy();

	//初期化処理
	void Initialize();
	//更新処理
	void Update(Player* player);
	//描画更新処理
	void Draw()const;

private:

	//エネミーのアニメーション制御関数
	void EnemyAnimation() override;

	//パトロール関数
	void EnemyPatrol(Player* player) override;

	//徘徊状態から警戒状態に入る範囲
	void AttackRange()override;

	//攻撃を行う範囲
	void AttackCenser() override;

	//追跡を行うか？
	void AttackStandBy(Player* player) override;

	//攻撃を行うか？
	void AttackStart(Player* player) override;

	void AttackEnd() override;

	void ClashToPlayer(Player* player)override;
};