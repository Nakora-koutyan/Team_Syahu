#pragma once
#include"EnemyBase.h"

#define ENEMY_SPEED 1.5f
#define RUSH_DIAMETER 3.5f

#define ATTACK_FORM_RANGE_X 150
#define ATTACK_FORM_RANGE_Y 50

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1

class Player;

class NormalEnemy :public EnemyBase
{
private:
	int enemyColor;

	int usualColor;	//通常色(確認用)
	int damageColor;	//ダメージを受けた時の色(確認用)
	int attackColor;	//攻撃時の色(確認用)

	int hp;				//自身のHP

	int direction;		//進行方向

	bool isChase;		//追跡

	Vector2D attackRange[2];
	Vector2D chaseCenser[2];		//0:左センサー	1:右センサー

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
	void AttackRange() override;

	//プレイヤーを発見するためのセンサー
	void ChaseRange() override;

	//追跡を行うか？
	void ChaseToPlayer(Player* player) override;

	//攻撃を行うか？
	void AttackToPlayer(Player* player) override;
};