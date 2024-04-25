#pragma once
#include"EnemyBase.h"

#define WALK_SPEED 1.f			//徘徊時のスピード
#define CHASE_SPEED 2.f		//追跡時のスピード
#define ATTACK_SPEED 10.f		//攻撃時のスピード

#define DIRECTION_LEFT 0		//左向き
#define DIRECTION_RIGHT 1		//右向き

class Player;

class NormalEnemy :public EnemyBase
{
private:
	int enemyColor;
	int colorRed;
	int colorGreen;
	int colorBlue;

	int usualColor;	//通常色(確認用)
	int damageColor;	//ダメージを受けた時の色(確認用)
	int attackColor;	//攻撃時の色(確認用)

	int hp;				//自身のHP

	int direction;		//進行方向

	bool isChase;		//追跡

	Vector2D attackRange[2];
	Vector2D attackCenser[2];		//0:左センサー	1:右センサー

	int markStatus;		//符号の状態遷移
	int findMark;		//プレイヤーを発見した際に出現する画像
	int angryMark;		//プレイヤーに攻撃する際の画像

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

	//パトロール関数
	void EnemyPatrol(Player* player) override;

	//攻撃範囲
	void AttackCenser() override;

	//プレイヤーを発見するためのセンサー
	void AttackRange() override;

	//追跡を行うか？
	void AttackStandBy(Player* player) override;

	//攻撃を行うか？
	void AttackStart(Player* player) override;

	void AttackEnd() override;

	void ClashToPlayer(Player* player)override;
};